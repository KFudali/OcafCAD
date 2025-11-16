#include "GeometryObject.hpp"

GeometryObject::GeometryObject(
    const PartLabel& aSourcePartLabel
) : mSourcePart(Part(aSourcePartLabel)),
    mSubShapes(aSourcePartLabel),
    mNamedSelectionTool(aSourcePartLabel){}