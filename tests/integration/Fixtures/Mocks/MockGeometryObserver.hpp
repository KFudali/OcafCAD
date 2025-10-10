#ifndef MockGeometryObserver_hpp
#define MockGeometryObserver_hpp

#include <gmock/gmock.h>
#include "GeometryObserver.hpp"

class MockGeometryObserver : public GeometryObserver {
public:
    MOCK_METHOD(void, onPartAdded, (const DocLabel& aLabel), (override));
    MOCK_METHOD(void, onPartRemoved, (const DocLabel& aLabel), (override));
    MOCK_METHOD(void, onPartModified, (), (override));
    MOCK_METHOD(void, onComponentAddedToAssembly, (const DocLabel& aLabel), (override));
    MOCK_METHOD(void, onComponentRemovedFromAssembly, (const DocLabel& aLabel), (override));
};

#endif