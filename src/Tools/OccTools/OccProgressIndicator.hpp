#ifndef OccProgressIndicator_hpp
#define OccProgressIndicator_hpp

#include <Message_ProgressIndicator.hxx>
#include "AbstractProgressPublisher.hpp"
#include <sstream>

class OccProgressIndicator : public Message_ProgressIndicator{
        
DEFINE_STANDARD_RTTIEXT(OccProgressIndicator, Message_ProgressIndicator);
	public:
	Standard_EXPORT OccProgressIndicator(
		const AbstractProgressPublisher& aProgressPublisher
	);

	Standard_EXPORT void Show(
		const Message_ProgressScope& aScope, 
		const Standard_Boolean force = Standard_True) Standard_OVERRIDE;

	private:
    static std::unique_ptr<ProgressRange> rangeFromOccScope(
        const Message_ProgressScope& aScope
    );
    static void applyScopeDataToRange(
        const Message_ProgressScope* aScope,
        ProgressRange* aRange
    );
    const AbstractProgressPublisher& mProgressPublisher;
};



#endif