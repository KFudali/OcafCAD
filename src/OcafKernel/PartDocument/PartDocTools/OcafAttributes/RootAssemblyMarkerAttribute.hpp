#ifndef RootAssemblyMarkerAttribute_hpp
#define RootAssemblyMarkerAttribute_hpp

#include "AbstractMarkerAttribute.hpp"

class RootAssemblyMarkerAttribute;
DEFINE_STANDARD_HANDLE(RootAssemblyMarkerAttribute, AbstractMarkerAttribute)

class RootAssemblyMarkerAttribute : public AbstractMarkerAttribute {
  DEFINE_STANDARD_RTTIEXT(RootAssemblyMarkerAttribute, AbstractMarkerAttribute)
public:
  RootAssemblyMarkerAttribute() = default;
  virtual ~RootAssemblyMarkerAttribute() = default;

  static const Standard_GUID& GetID();
  const Standard_GUID& ID() const override { return GetID(); }

  Handle(TDF_Attribute) NewEmpty() const override {
    return new RootAssemblyMarkerAttribute();
  }
};

#endif
