#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PublisherProgressScope.hpp"

class MockPublisher : public AbstractProgressPublisher {
public:
    MOCK_METHOD(void, scopeLaunched,
        (const ProgressScopeId& aScopeId, const std::string& aMessage),
        (const, override));

    MOCK_METHOD(void, scopeAdvanced,
        (const ProgressScopeId& aScopeId, double fraction),
        (const, override));

    MOCK_METHOD(void, scopeFinalized,
        (const ProgressScopeId& aScopeId),
        (const, override));
};

using StrictMockPublisher = ::testing::StrictMock<MockPublisher>;

class PublisherProgressScopeTest : public ::testing::Test {
protected:
    void SetUp() override {
        publisher = std::make_shared<StrictMockPublisher>();
        scope = std::make_unique<PublisherProgressScope>(id, publisher);
    }
    std::shared_ptr<StrictMockPublisher> publisher;
    std::unique_ptr<AbstractProgressScope> scope;
    const ProgressScopeId id{std::vector<int>{1}};
    const std::string message{"init"};
};

TEST_F(PublisherProgressScopeTest, LaunchingCallsPublisherSetsMessage){
    EXPECT_CALL(*publisher, scopeLaunched(id, testing::StrEq("launch")));
    scope->launch("launch");
    EXPECT_EQ(scope->message(), "launch");
}

TEST_F(PublisherProgressScopeTest, AdvancingCallsPublisherSetsFraction){
    EXPECT_CALL(*publisher, scopeAdvanced(id, testing::DoubleEq(0.5)));
    scope->advance(0.5);
    EXPECT_THAT(scope->progressFraction(), ::testing::DoubleEq(0.5));
}

TEST_F(PublisherProgressScopeTest, AdvancingPastOneFinalizes){
    EXPECT_CALL(*publisher, scopeFinalized(id));
    scope->advance(1.5);
}

TEST_F(PublisherProgressScopeTest, AdvancingSumsUp){
    EXPECT_CALL(*publisher, scopeAdvanced(id, testing::DoubleEq(0.5)));
    EXPECT_CALL(*publisher, scopeAdvanced(id, testing::DoubleEq(0.75)));
    EXPECT_CALL(*publisher, scopeFinalized(id));
    scope->advance(0.5);
    scope->advance(0.25);
    scope->advance(0.3);
}

TEST_F(PublisherProgressScopeTest, FinalizingCallsPublisherSetsFraction){
    EXPECT_CALL(*publisher, scopeFinalized(id));
    scope->finalize();
    EXPECT_THAT(scope->progressFraction(), ::testing::DoubleEq(1.0));
}

TEST_F(PublisherProgressScopeTest, SubScopePointsToParentIsInChildren) {
    EXPECT_CALL(*publisher, scopeLaunched(testing::_, testing::_));
    auto subScope = scope->newSubScope("subScope", 1.0);
    EXPECT_EQ(subScope->parentScope(), scope.get());
    auto children = scope->activeChildren();
    ASSERT_EQ(children.size(), 1);
    EXPECT_EQ(children[0], subScope);
}

TEST_F(PublisherProgressScopeTest, AdvancingSubScopeAdvancesParentByWeight) {
    EXPECT_CALL(*publisher, scopeLaunched(testing::_, testing::_));
    auto subScope = scope->newSubScope("subScope", 0.5);
    EXPECT_CALL(*publisher, scopeAdvanced(subScope->id(), testing::DoubleEq(0.5)));
    EXPECT_CALL(*publisher, scopeAdvanced(id, testing::DoubleEq(0.25)));
    subScope->advance(0.5);
}

TEST_F(PublisherProgressScopeTest, FinalizingChildDestroysItInParent) {
    EXPECT_CALL(*publisher, scopeLaunched(testing::_, testing::_));
    auto subScope = scope->newSubScope("subScope", 0.5);
    EXPECT_CALL(*publisher, scopeFinalized(subScope->id()));
    subScope->advance(1.5);
    auto children = scope->activeChildren();
    EXPECT_EQ(children.size(), 0);
}