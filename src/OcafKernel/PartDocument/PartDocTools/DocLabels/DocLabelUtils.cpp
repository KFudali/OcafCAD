#include "DocLabelUtils.hpp"

bool DocLabelUtils::isRootAssemblyLabel(TDF_Label aLabel) {


    return false;
}

bool DocLabelUtils::isPartLabel(TDF_Label aLabel) {
    return true;
}
bool DocLabelUtils::isPrototypeLabel(TDF_Label aLabel) {
    return true;
}