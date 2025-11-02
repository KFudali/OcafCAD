#include "GeometryObject.hpp"

GeometryObject::GeometryObject(
    const PartLabel& aSourcePartLabel
) : mSourcePart(Part(aSourcePartLabel)),
    mNamedSelectionTool(aSourcePartLabel){}