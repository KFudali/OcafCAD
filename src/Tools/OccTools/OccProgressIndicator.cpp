#include "OccProgressIndicator.hpp"

IMPLEMENT_STANDARD_RTTIEXT(OccProgressIndicator, Message_ProgressIndicator);

OccProgressIndicator::OccProgressIndicator(
    const AbstractProgressPublisher& aProgressPublisher
) : mProgressPublisher(aProgressPublisher){};

void OccProgressIndicator::Show(
    const Message_ProgressScope& aScope,
    const Standard_Boolean force
){
    auto range = rangeFromOccScope(aScope);
    mProgressPublisher.publishRange(*range);
}

std::unique_ptr<ProgressRange> OccProgressIndicator::rangeFromOccScope(
    const Message_ProgressScope& aScope
){
    std::vector<const Message_ProgressScope*> scopes;
    for (const Message_ProgressScope* scope = &aScope; 
        scope; 
        scope = scope->Parent()
    ) {
        scopes.push_back(scope);
    }
    std::reverse(scopes.begin(), scopes.end());

    auto range = std::make_unique<ProgressRange>();
    ProgressRange* current = range.get();
    for (const auto* scope : scopes) {
        applyScopeDataToRange(scope, current);
        if (scope != scopes.back()) {
            current = &current->newChild(Fraction(0.0));
        }
    }

    return range;
}


void OccProgressIndicator::applyScopeDataToRange(
    const Message_ProgressScope* aScope,
    ProgressRange* aRange
) {
    if (!aScope || !aRange) return;

    if (aScope->Name()) {
        aRange->setLabel(aScope->Name());
    }

    Fraction progressFraction(0.0f);

    if (aScope->IsInfinite()) {
        if (Precision::IsInfinite(aScope->Value())) {
            progressFraction = Fraction(1.0f);
        } else {
            progressFraction = Fraction(aScope->Value());
        }
    } else {
        Standard_Real maxVal = aScope->MaxValue();
        if (maxVal > 0.0) {
            progressFraction = Fraction(aScope->Value() / maxVal);
        }
    }
    aRange->setTo(progressFraction);
}
