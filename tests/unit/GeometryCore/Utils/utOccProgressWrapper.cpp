#include "OccProgressScopeWrapper.hpp"
#include <gmock/gmock.h>


class MockProgressScope : public AbstractProgressScope {
public:
    
    MOCK_METHOD(void, launch, (const std::string& aMessage), (override));
    MOCK_METHOD(void, advance, (double aFraction), (override));
    MOCK_METHOD(void, finalize, (), (override));
    MOCK_METHOD(void, newSubScope, (const std::string& aLabel, double aWeight), (override));
};

using NiceMockProgressScope = ::testing::NiceMock<MockProgressScope>

class OccProgressScopeWrapperTest : public ::testing::Test {
protected:
    void SetUp(){
        mockScope = std::make_shared<NiceMockProgressScope>();
        occWrapper = std::make_unique<OccProgressScopeWrapper>(mockScope);
    }
    std::shared_ptr<NiceMockProgressScope> mockScope;
    std::unique_ptr<OccProgressScopeWrapper> occWrapper;
};



TEST_F(OccProgressScopeWrapperTest, ProgressMessageGeneratesFormatsSubTasks) {
    Message_ProgressRange rootRange = progressIndicator.Start();
    Message_ProgressScope rootScope(rootRange, "RootTask", 100, false);
    Message_ProgressRange subRange = rootScope.Next(10);
    Message_ProgressScope subScope(subRange, "SubTask", 50, false);
    Message_ProgressRange subSubRange = subScope.Next(20);
    Message_ProgressScope subSubScope(subSubRange, "SubSubTask", 10, false);     
};
