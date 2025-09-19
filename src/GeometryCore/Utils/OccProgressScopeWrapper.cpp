#include "OccProgressScopeWrapper.hpp"


void OccProgressScopeWrapper::Show(
    const Message_ProgressScope& aScope, 
    const Standard_Boolean force
) {
    mScope.launch('message');
}