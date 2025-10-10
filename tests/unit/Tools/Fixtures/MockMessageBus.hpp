#ifndef MockPublishMessageBus_hpp
#define MockPublishMessageBus_hpp

#include <gmock/gmock.h>
#include "AbstractMessageBus.hpp"

class MockMessageBus : public AbstractMessageBus {
public:
    MockMessageBus() = default;
    ~MockMessageBus() override = default;

    MOCK_METHOD(std::unique_ptr<AbstractSubscription>, subscribeImpl,
                (std::type_index, std::function<void(const std::any&)>), (override));

    MOCK_METHOD(void, publishImpl, (std::type_index, const std::any&), (const, override));
};

#endif
