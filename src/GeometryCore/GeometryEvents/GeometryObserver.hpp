#ifndef GeometryObserver_hpp
#define GeometryObserver_hpp

#include "DocLabel.hpp"

class GeometryObserver {
    public:
    virtual void onPartAdded(const DocLabel& aLabel) {};
    virtual void onPartRemoved(const DocLabel& aLabel) {};
    virtual void onPartModified() {}; // To be implemented
    virtual void onComponentAddedToAssembly(const DocLabel& aLabel) {};
    virtual void onComponentRemovedFromAssembly(const DocLabel& aLabel) {};
};

#endif