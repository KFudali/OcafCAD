#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SignalMessageBus.hpp"

class StubEventA : public AbstractEvent {
    protected:
    int mId;
    public:
    StubEventA(int id) : mId(id) {}
    int id() const {return mId;}
    bool operator==(const StubEventA& aOther) const {return this->mId == aOther.mId;}
    std::string log() const {return "StubEvent, id: " + std::to_string(mId);}
};

class StubEventB : public StubEventA {
    public:
    StubEventB(int id) : StubEventA(id) {}
    bool operator==(const StubEventB& aOther) const {return this->mId == aOther.mId;}
};

class StubEventC : public StubEventA {
    public:
    StubEventC(int id) : StubEventA(id) {}
    bool operator==(const StubEventC& aOther) const {return this->mId == aOther.mId;}
};

struct MockMessageBusSubscriber {
    MOCK_METHOD(int, mockHandleA, (const StubEventA&), ());
    MOCK_METHOD(int, mockHandleB, (const StubEventB&), ());
    MOCK_METHOD(int, mockHandleC, (const StubEventC&), ());
};

class SignalMessageBusTest : public ::testing::Test{
    protected:
    SignalMessageBus testBus;
};

TEST_F(SignalMessageBusTest, BusCallsMethodThatIsSubscribedToEvent){
    auto subscriber = std::make_shared<MockMessageBusSubscriber>();

    auto connectionA = testBus.subscribe<StubEventA>(
        subscriber, &MockMessageBusSubscriber::mockHandleA
    );

    auto connectionB = testBus.subscribe<StubEventB>(
        subscriber, &MockMessageBusSubscriber::mockHandleB
    );

    auto connectionC = testBus.subscribe<StubEventC>(
        subscriber, &MockMessageBusSubscriber::mockHandleC
    );
    
    StubEventA eventA(1);
    StubEventB eventB(2);
    StubEventC eventC(3);
    EXPECT_CALL(*subscriber, mockHandleA(eventA)).Times(1);
    EXPECT_CALL(*subscriber, mockHandleB(eventB)).Times(1);
    EXPECT_CALL(*subscriber, mockHandleC(eventC)).Times(1);
    testBus.publish(eventA);  
    testBus.publish(eventB);   
    testBus.publish(eventC);
}

TEST_F(SignalMessageBusTest, BusDoesNotCallNotSubscribedMethods){
    auto subscriber = std::make_shared<MockMessageBusSubscriber>();

    auto connectionA = testBus.subscribe<StubEventA>(
        subscriber, &MockMessageBusSubscriber::mockHandleA
    );

    auto connectionB = testBus.subscribe<StubEventB>(
        subscriber, &MockMessageBusSubscriber::mockHandleB
    );

    auto connectionC = testBus.subscribe<StubEventC>(
        subscriber, &MockMessageBusSubscriber::mockHandleC
    );
    
    StubEventA eventA(123);
    EXPECT_CALL(*subscriber, mockHandleA(eventA)).Times(1);
    EXPECT_CALL(*subscriber, mockHandleB(testing::_)).Times(0);
    EXPECT_CALL(*subscriber, mockHandleB(testing::_)).Times(0);
    testBus.publish(eventA);    
}

TEST_F(SignalMessageBusTest, BusCallsMethodOnEachPublish){
    auto subscriber = std::make_shared<MockMessageBusSubscriber>();
    auto connectionA = testBus.subscribe<StubEventA>(
        subscriber, &MockMessageBusSubscriber::mockHandleA
    );
    StubEventA eventA(123);
    EXPECT_CALL(*subscriber, mockHandleA(eventA)).Times(3);
    
    testBus.publish(eventA);    
    testBus.publish(eventA);    
    testBus.publish(eventA);    
}

TEST_F(SignalMessageBusTest, BusDoesNotCallMethodIfSubIsDisconnected){
    auto subscriber = std::make_shared<MockMessageBusSubscriber>();
    auto connectionA = testBus.subscribe<StubEventA>(
        subscriber, &MockMessageBusSubscriber::mockHandleA
    );
    StubEventA eventA(123);
    EXPECT_CALL(*subscriber, mockHandleA(::testing::_)).Times(0);
    
    connectionA->disconnect();
    
    testBus.publish(eventA);    
}

TEST_F(SignalMessageBusTest, BusHandlesPublishIfReceiverWasDestroyed) {
    {
        auto subscriber = std::make_shared<MockMessageBusSubscriber>();
        auto connectionA = testBus.subscribe<StubEventA>(
            subscriber, &MockMessageBusSubscriber::mockHandleA
        );
        EXPECT_CALL(*subscriber, mockHandleA(::testing::_)).Times(0);
    }

    StubEventA eventA(123);
    EXPECT_NO_THROW({
        testBus.publish(eventA);
    });
}

TEST_F(SignalMessageBusTest, BusCallsSubscribedLambdas) {
    int callCount = 0;
    int lastValue = 0;

    auto sub = testBus.subscribe<StubEventA>(
        [&](const StubEventA& e) {
            callCount++;
            lastValue = e.id();
        }
    );

    StubEventA eventA(456);
    testBus.publish(eventA);

    EXPECT_EQ(callCount, 1);
    EXPECT_EQ(lastValue, 456);
}
