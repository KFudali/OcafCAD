#include "DocLabelUtils.hpp"
#include "RootAssemblyAttribute.hpp"

bool DocLabelUtils::isRootAssemblyLabel(TDF_Label aLabel) {
    return aLabel.IsAttribute(RootAssemblyAttribute::GetID());
}

bool DocLabelUtils::isPartLabel(TDF_Label aLabel) {
    return true;
}
bool DocLabelUtils::isPrototypeLabel(TDF_Label aLabel) {
    return true;
}