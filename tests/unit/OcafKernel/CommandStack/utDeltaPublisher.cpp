#include <gtest/gtest.h>
#include "DeltaPublisher.hpp"
#include "MockDeltaObserver.hpp"
#include "StubDelta.hpp"

using ::testing::_;
using ::testing::Exactly;

class DeltaPublisherTest : public ::testing::Test {
protected:
    DeltaPublisher publisher;
    MockDeltaObserver observer1;
    MockDeltaObserver observer2;
};

TEST_F(DeltaPublisherTest, AppendAndRemoveObservers) {
    EXPECT_TRUE(publisher.appendDeltaObserver(&observer1));
    EXPECT_FALSE(publisher.appendDeltaObserver(&observer1));

    EXPECT_TRUE(publisher.removeDeltaObserver(&observer1));
    EXPECT_FALSE(publisher.removeDeltaObserver(&observer1));
}

TEST_F(DeltaPublisherTest, NotifiesSingleObserverOnAddition) {
    publisher.appendDeltaObserver(&observer1);

    auto delta = StubDeltas::makeAdditionDelta();
    EXPECT_CALL(observer1, onAddition(_)).Times(Exactly(1));

    publisher.processDelta(delta);
}

TEST_F(DeltaPublisherTest, NotifiesMultipleObserversOnAddition) {
    publisher.appendDeltaObserver(&observer1);
    publisher.appendDeltaObserver(&observer2);

    auto delta = StubDeltas::makeAdditionDelta();

    EXPECT_CALL(observer1, onAddition(_)).Times(Exactly(1));
    EXPECT_CALL(observer2, onAddition(_)).Times(Exactly(1));

    publisher.processDelta(delta);
}

TEST_F(DeltaPublisherTest, RemovedObserverDoesNotReceiveNotifications) {
    publisher.appendDeltaObserver(&observer1);
    publisher.appendDeltaObserver(&observer2);

    publisher.removeDeltaObserver(&observer1);

    auto delta = StubDeltas::makeAdditionDelta();

    EXPECT_CALL(observer1, onAddition(_)).Times(0);
    EXPECT_CALL(observer2, onAddition(_)).Times(1);

    publisher.processDelta(delta);
}
