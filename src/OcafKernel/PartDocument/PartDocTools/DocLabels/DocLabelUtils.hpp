#ifndef DocLabelUtils_hpp
#define DocLabelUtils_hpp

#include <TDF_Label.hxx>

namespace DocLabelUtils {
    bool isRootAssemblyLabel(TDF_Label aLabel);
    bool isPartLabel(TDF_Label aLabel);
    bool isPrototypeLabel(TDF_Label aLabel);
};

#endif