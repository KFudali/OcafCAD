#include "GeometryNamedSelectionAttribute.hpp"

GeometryNamedSelectionAttribute::GeometryNamedSelectionAttribute()
: TDataStd_GenericExtString(){}

IMPLEMENT_DERIVED_ATTRIBUTE(GeometryNamedSelectionAttribute, TDataStd_GenericExtString)

static const Standard_GUID GeoNamedSelectionGUID("5ac8b315-5baf-432e-8e66-5fbdbe326e90");

const Standard_GUID& GeometryNamedSelectionAttribute::GetID()
{
  return GeoNamedSelectionGUID;
}

const Standard_GUID& GeometryNamedSelectionAttribute::ID() const
{
  return GetID();
}

void GeometryNamedSelectionAttribute::SetName(const TCollection_ExtendedString& aName)
{
  Set(aName);
}

const TCollection_ExtendedString& GeometryNamedSelectionAttribute::GetName() const
{
  return Get();
}
