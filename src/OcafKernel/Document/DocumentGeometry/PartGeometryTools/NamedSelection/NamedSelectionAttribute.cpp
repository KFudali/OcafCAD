#include "NamedSelectionAttribute.hpp"

NamedSelectionAttribute::NamedSelectionAttribute()
: TDataStd_GenericExtString(){}

IMPLEMENT_DERIVED_ATTRIBUTE(NamedSelectionAttribute, TDataStd_GenericExtString)

static const Standard_GUID GeoNamedSelectionGUID("5ac8b315-5baf-432e-8e66-5fbdbe326e90");

const Standard_GUID& NamedSelectionAttribute::GetID()
{
  return GeoNamedSelectionGUID;
}

const Standard_GUID& NamedSelectionAttribute::ID() const
{
  return GetID();
}

void NamedSelectionAttribute::SetName(const TCollection_ExtendedString& aName)
{
  Set(aName);
}

const TCollection_ExtendedString& NamedSelectionAttribute::GetName() const
{
  return Get();
}
