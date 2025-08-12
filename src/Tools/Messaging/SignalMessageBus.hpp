#ifndef SignalMessageBus_hpp
#define SignalMessageBus_hpp

#include "AbstractMessageBus.hpp"

#include "boost/signals2/signal.hpp"
#include <unordered_map>
#include <vector>
#include <typeindex>

class SignalSubscription : public AbstractSubscription {
public:
    explicit SignalSubscription(boost::signals2::connection connection)
        : mConnection(std::move(connection))
    {}
    ~SignalSubscription(){mConnection.disconnect();}

    bool disconnect() override {
        if (mConnection.connected()) {
            mConnection.disconnect();
            return true;
        }
        return false;
    }
private:
    boost::signals2::connection mConnection;
};

class SignalMessageBus : public AbstractMessageBus{
    std::unique_ptr<AbstractSubscription> subscribeImpl(
        std::type_index type, 
        std::function<void(const std::any&)> handler
    ) override;
    void publishImpl(
        std::type_index type, const std::any& message
    ) const override;

    using AnySignal = boost::signals2::signal<void(const std::any&)>;
    std::unordered_map<std::type_index, AnySignal> mSignals;
};

#endif