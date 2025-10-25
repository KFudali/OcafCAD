#ifndef NamedSelectionTreeMarkerAttribute_hpp
#define NamedSelectionTreeMarkerAttribute_hpp

#include "AbstractMarkerAttribute.hpp"

class NamedSelectionTreeMarkerAttribute;
DEFINE_STANDARD_HANDLE(NamedSelectionTreeMarkerAttribute, AbstractMarkerAttribute)

class NamedSelectionTreeMarkerAttribute : public AbstractMarkerAttribute {
  DEFINE_STANDARD_RTTIEXT(NamedSelectionTreeMarkerAttribute, AbstractMarkerAttribute)
public:
  NamedSelectionTreeMarkerAttribute() = default;
  virtual ~NamedSelectionTreeMarkerAttribute() = default;

  static const Standard_GUID& GetID();
  const Standard_GUID& ID() const override { return GetID(); }

  Handle(TDF_Attribute) NewEmpty() const override {
    return new NamedSelectionTreeMarkerAttribute();
  }
};

#endif
