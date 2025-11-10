#ifndef ShapeMarkerAttribute_hpp
#define ShapeMarkerAttribute_hpp

#include "AbstractMarkerAttribute.hpp"

class ShapeMarkerAttribute;
DEFINE_STANDARD_HANDLE(ShapeMarkerAttribute, AbstractMarkerAttribute)

class ShapeMarkerAttribute : public AbstractMarkerAttribute {
  DEFINE_STANDARD_RTTIEXT(ShapeMarkerAttribute, AbstractMarkerAttribute)
public:
  ShapeMarkerAttribute() = default;
  virtual ~ShapeMarkerAttribute() = default;

  static const Standard_GUID& GetID();
  const Standard_GUID& ID() const override { return GetID(); }

  Handle(TDF_Attribute) NewEmpty() const override {
    return new ShapeMarkerAttribute();
  }
};

#endif
