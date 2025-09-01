#ifndef SignalSubscription_hpp
#define SignalSubscription_hpp

#include "AbstractSubscription.hpp"
#include "boost/signals2/signal.hpp"

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

#endif