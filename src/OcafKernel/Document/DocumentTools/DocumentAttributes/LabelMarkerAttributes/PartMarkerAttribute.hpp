#ifndef PartMarkerAttribute_hpp
#define PartMarkerAttribute_hpp

#include "AbstractMarkerAttribute.hpp"

class PartMarkerAttribute;
DEFINE_STANDARD_HANDLE(PartMarkerAttribute, AbstractMarkerAttribute)

class PartMarkerAttribute : public AbstractMarkerAttribute {
  DEFINE_STANDARD_RTTIEXT(PartMarkerAttribute, AbstractMarkerAttribute)
public:
  PartMarkerAttribute() = default;
  virtual ~PartMarkerAttribute() = default;

  static const Standard_GUID& GetID();
  const Standard_GUID& ID() const override { return GetID(); }

  Handle(TDF_Attribute) NewEmpty() const override {
    return new PartMarkerAttribute();
  }
};

#endif
