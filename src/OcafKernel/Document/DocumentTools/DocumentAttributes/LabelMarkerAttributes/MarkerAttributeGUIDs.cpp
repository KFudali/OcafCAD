#include "RootAssemblyMarkerAttribute.hpp"
#include "PartMarkerAttribute.hpp"
#include "PrototypeMarkerAttribute.hpp"

// RTTI
IMPLEMENT_STANDARD_RTTIEXT(AbstractMarkerAttribute, TDF_Attribute)
IMPLEMENT_STANDARD_RTTIEXT(RootAssemblyMarkerAttribute, AbstractMarkerAttribute)
IMPLEMENT_STANDARD_RTTIEXT(PartMarkerAttribute, AbstractMarkerAttribute)
IMPLEMENT_STANDARD_RTTIEXT(PrototypeMarkerAttribute, AbstractMarkerAttribute)

// GUIDs
static const Standard_GUID RootAssemblyGUID("577715ad-9684-413d-bb8c-3d9fedd56f37");
static const Standard_GUID PartGUID("79292cee-d8da-4037-9c96-ceba91332ceb");
static const Standard_GUID PrototypeGUID("c6af5c18-eb4c-4f42-b36f-5c0d84ef4398");

const Standard_GUID& RootAssemblyMarkerAttribute::GetID() { return RootAssemblyGUID; }
const Standard_GUID& PartMarkerAttribute::GetID() { return PartGUID; }
const Standard_GUID& PrototypeMarkerAttribute::GetID() { return PrototypeGUID; }
