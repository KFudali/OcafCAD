#ifndef DocLabelUtils_hpp
#define DocLabelUtils_hpp

#include <TDF_Label.hxx>

namespace DocLabelUtils {
    bool isRootAssemblyLabel(TDF_Label aLabel);
    bool canBePartLabel(TDF_Label aLabel);
    bool canBePrototypeLabel(TDF_Label aLabel);
};

#endif