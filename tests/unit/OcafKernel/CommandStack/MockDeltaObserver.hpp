#ifndef MockDeltaObserver_hpp
#define MockDeltaObserver_hpp

#include <gmock/gmock.h>
#include "AbstractDeltaObserver.hpp"

class MockDeltaObserver : public AbstractDeltaObserver {
public:
    MOCK_METHOD(void, onAddition, (Handle(TDF_DeltaOnAddition) aDelta), (override));
    MOCK_METHOD(void, onRemoval, (Handle(TDF_DeltaOnRemoval) aDelta), (override));
    MOCK_METHOD(void, onForget, (Handle(TDF_DeltaOnForget) aDelta), (override));
    MOCK_METHOD(void, onResume, (Handle(TDF_DeltaOnResume) aDelta), (override));
    MOCK_METHOD(void, onModification, (Handle(TDF_DeltaOnModification) aDelta), (override));
};

#endif
