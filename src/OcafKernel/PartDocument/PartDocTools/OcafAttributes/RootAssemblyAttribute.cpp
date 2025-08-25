#include "RootAssemblyAttribute.hpp"

IMPLEMENT_STANDARD_RTTIEXT(RootAssemblyAttribute, TDF_Attribute)

static const Standard_GUID RootAssemblyGUID(
  "2ae4362f-ce33-4af9-909e-f009ad8516f3"
);

const Standard_GUID& RootAssemblyAttribute::GetID() {
  return RootAssemblyGUID;
}

const Standard_GUID& RootAssemblyAttribute::ID() const {
  return GetID();
}

Handle(TDF_Attribute) RootAssemblyAttribute::NewEmpty() const {
  return new RootAssemblyAttribute();
}

void RootAssemblyAttribute::Restore(const Handle(TDF_Attribute)& from) {}

void RootAssemblyAttribute::Paste (
    const Handle(TDF_Attribute)& intoAttribute, 
    const Handle(TDF_RelocationTable)& aRelocationTable
) const {};