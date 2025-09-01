#ifndef IdleOcafKernelObserver_hpp
#define IdleOcafKernelObserver_hpp

#include "AbstractOcafKernelPublisher.hpp"
#include <boost/log/trivial.hpp>

class IdleOcafKernelObserver : public AbstractOcafKernelObserver {
public:
    void onPrototypeAdded(PrototypeLabel aLabel) override {
        BOOST_LOG_TRIVIAL(debug) << "Prototype added" << aLabel.toString();
    }
    void onPrototypeRemoved(PrototypeLabel aLabel) override {
        BOOST_LOG_TRIVIAL(debug) << "Prototype removed" << aLabel.toString();
    }
    void onPartAdded(PartLabel aLabel) override {
        BOOST_LOG_TRIVIAL(debug) << "Part added " << aLabel.toString();
    }
    void onPartRemoved(PartLabel aLabel) override {
        BOOST_LOG_TRIVIAL(debug) << "Part removed " << aLabel.toString();
    }
    void onPartLocationChanged(PartLabel aLabel) override {
        BOOST_LOG_TRIVIAL(debug) << "Part location changed " << aLabel.toString();
    }
    void onPartAttributeChanged(
        PartLabel aLabel, 
        PartAttributeType aAttributeEnum
    ) override {
        BOOST_LOG_TRIVIAL(debug) << "Part attribute changed " << aLabel.toString();
    }
    void onComponentAddedToAssembly(PartLabel aLabel) override {
        BOOST_LOG_TRIVIAL(debug) << "Part added to assembly" << aLabel.toString();
    }
    void onComponentRemovedFromAssembly(PartLabel aLabel) override {
        BOOST_LOG_TRIVIAL(debug) << "Part removed from assembly" << aLabel.toString();
    }
};

#endif