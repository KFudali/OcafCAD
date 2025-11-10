#include "RootAssemblyMarkerAttribute.hpp"
#include "PartMarkerAttribute.hpp"
#include "ShapeMarkerAttribute.hpp"
#include "SubShapeMarkerAttribute.hpp"
#include "NamedSelectionTreeMarkerAttribute.hpp"
#include "RefTreeMarkerAttribute.hpp"

// RTTI
IMPLEMENT_STANDARD_RTTIEXT(AbstractMarkerAttribute, TDF_Attribute)
IMPLEMENT_STANDARD_RTTIEXT(RootAssemblyMarkerAttribute, AbstractMarkerAttribute)
IMPLEMENT_STANDARD_RTTIEXT(PartMarkerAttribute, AbstractMarkerAttribute)
IMPLEMENT_STANDARD_RTTIEXT(ShapeMarkerAttribute, AbstractMarkerAttribute)
IMPLEMENT_STANDARD_RTTIEXT(SubShapeMarkerAttribute, AbstractMarkerAttribute)
IMPLEMENT_STANDARD_RTTIEXT(NamedSelectionTreeMarkerAttribute, AbstractMarkerAttribute)
IMPLEMENT_STANDARD_RTTIEXT(RefTreeMarkerAttribute, AbstractMarkerAttribute)

// GUIDs
static const Standard_GUID RootAssemblyGUID("577715ad-9684-413d-bb8c-3d9fedd56f37");
static const Standard_GUID PartGUID("79292cee-d8da-4037-9c96-ceba91332ceb");
static const Standard_GUID ShapeGUID("c6af5c18-eb4c-4f42-b36f-5c0d84ef4398");
static const Standard_GUID SubShapeGUID("ae052a89-6e26-4406-92ae-d3ba04e3f9e3");
static const Standard_GUID NamedSelectionTreeGUID("3b8fcd4a-0358-4fca-8ec1-8b62f10bf165");
static const Standard_GUID ReferenceTreeGUID("14d9da6a-f188-4e38-aa48-1356900041f7");

const Standard_GUID& RootAssemblyMarkerAttribute::GetID() { return RootAssemblyGUID; }
const Standard_GUID& PartMarkerAttribute::GetID() { return PartGUID; }
const Standard_GUID& ShapeMarkerAttribute::GetID() { return ShapeGUID; }
const Standard_GUID& SubShapeMarkerAttribute::GetID() { return SubShapeGUID; }
const Standard_GUID& NamedSelectionTreeMarkerAttribute::GetID() { return NamedSelectionTreeGUID;}
const Standard_GUID& RefTreeMarkerAttribute::GetID() { return ReferenceTreeGUID;}