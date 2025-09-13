#ifndef OccProgressScopeWrapper_hpp
#define OccProgressScopeWrapper_hpp

#include <Message_ProgressIndicator.hxx>
#include "AbstractProgressScope.hpp"
#include <sstream>

class OccProgressScopeWrapper : public Message_ProgressIndicator {
        
DEFINE_STANDARD_RTTIEXT(OccProgressIndicator, Message_ProgressIndicator);
	public:
	Standard_EXPORT OccProgressIndicator(
        AbstractProgressScope& aScope
    );

	Standard_EXPORT void Show(
		const Message_ProgressScope& aScope, 
		const Standard_Boolean force = Standard_True) Standard_OVERRIDE;

	private:
	
    AbstractProgressScope& mScope;
};



#endif