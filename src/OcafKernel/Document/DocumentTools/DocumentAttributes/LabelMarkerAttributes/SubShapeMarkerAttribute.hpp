#ifndef SubShapeMarkerAttribute_hpp
#define SubShapeMarkerAttribute_hpp

#include "AbstractMarkerAttribute.hpp"

class SubShapeMarkerAttribute;
DEFINE_STANDARD_HANDLE(SubShapeMarkerAttribute, AbstractMarkerAttribute)

class SubShapeMarkerAttribute : public AbstractMarkerAttribute {
  DEFINE_STANDARD_RTTIEXT(SubShapeMarkerAttribute, AbstractMarkerAttribute)
public:
  SubShapeMarkerAttribute() = default;
  virtual ~SubShapeMarkerAttribute() = default;

  static const Standard_GUID& GetID();
  const Standard_GUID& ID() const override { return GetID(); }

  Handle(TDF_Attribute) NewEmpty() const override {
    return new SubShapeMarkerAttribute();
  }
};

#endif
