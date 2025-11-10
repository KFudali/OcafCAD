#include "NamedRefTreeAttribute.hpp"

NamedRefTreeAttribute::NamedRefTreeAttribute()
: TDataStd_GenericExtString(){}

IMPLEMENT_DERIVED_ATTRIBUTE(NamedRefTreeAttribute, TDataStd_GenericExtString)

static const Standard_GUID GeoNamedSelectionGUID("5ac8b315-5baf-432e-8e66-5fbdbe326e90");

const Standard_GUID& NamedRefTreeAttribute::GetID()
{
  return GeoNamedSelectionGUID;
}

const Standard_GUID& NamedRefTreeAttribute::ID() const
{
  return GetID();
}

void NamedRefTreeAttribute::SetName(const TCollection_ExtendedString& aName)
{
  Set(aName);
}

const TCollection_ExtendedString& NamedRefTreeAttribute::GetName() const
{
  return Get();
}
