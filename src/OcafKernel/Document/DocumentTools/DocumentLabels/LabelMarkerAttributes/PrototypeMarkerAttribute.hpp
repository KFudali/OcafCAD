#ifndef PrototypeMarkerAttribute_hpp
#define PrototypeMarkerAttribute_hpp

#include "AbstractMarkerAttribute.hpp"

class PrototypeMarkerAttribute;
DEFINE_STANDARD_HANDLE(PrototypeMarkerAttribute, AbstractMarkerAttribute)

class PrototypeMarkerAttribute : public AbstractMarkerAttribute {
  DEFINE_STANDARD_RTTIEXT(PrototypeMarkerAttribute, AbstractMarkerAttribute)
public:
  PrototypeMarkerAttribute() = default;
  virtual ~PrototypeMarkerAttribute() = default;

  static const Standard_GUID& GetID();
  const Standard_GUID& ID() const override { return GetID(); }

  Handle(TDF_Attribute) NewEmpty() const override {
    return new PrototypeMarkerAttribute();
  }
};

#endif
