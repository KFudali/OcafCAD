#include "SignalMessageBus.hpp"

std::unique_ptr<AbstractSubscription> SignalMessageBus::subscribeImpl(
    std::type_index type, 
    std::function<void(const std::any&)> handler
) {
    auto connection = mSignals[type].connect(std::move(handler));
    return std::make_unique<SignalSubscription>(connection);
};

void SignalMessageBus::publishImpl(
    std::type_index type, const std::any& message
) const {
    auto it = mSignals.find(type);
    if (it != mSignals.end()) {
        it->second(message);
    }
};