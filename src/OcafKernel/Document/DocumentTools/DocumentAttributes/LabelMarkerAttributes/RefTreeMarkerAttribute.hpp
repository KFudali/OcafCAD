#ifndef RefTreeMarkerAttribute_hpp
#define RefTreeMarkerAttribute_hpp

#include "AbstractMarkerAttribute.hpp"

class RefTreeMarkerAttribute;
DEFINE_STANDARD_HANDLE(RefTreeMarkerAttribute, AbstractMarkerAttribute)

class RefTreeMarkerAttribute : public AbstractMarkerAttribute {
  DEFINE_STANDARD_RTTIEXT(RefTreeMarkerAttribute, AbstractMarkerAttribute)
public:
  RefTreeMarkerAttribute() = default;
  virtual ~RefTreeMarkerAttribute() = default;

  static const Standard_GUID& GetID();
  const Standard_GUID& ID() const override { return GetID(); }

  Handle(TDF_Attribute) NewEmpty() const override {
    return new RefTreeMarkerAttribute();
  }
};

#endif

