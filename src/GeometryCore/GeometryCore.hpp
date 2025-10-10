#ifndef GeometryCore_hpp
#define GeometryCore_hpp

#include <memory>
#include "AbstractImporter.hpp"
#include "OcafKernel.hpp"
#include "GeometryView.hpp"
#include "GeometryEventSource.hpp"

class GeometryCore {
    public:
    GeometryCore(OcafKernel& aOcafKernel);

    void import(
        AbstractImporter& aImporter, 
        AbstractProgressPublisher& aPublisher
    );
    void import(AbstractImporter& aImporter);
   
    void clear() {};

    GeometryView* view() const {return mView.get();}    
    GeometryEventSource* events() const {return mEvents.get();}    

    private:
    DocumentGeometry& mDocumentGeometry;
    std::unique_ptr<GeometryView> mView;
    std::unique_ptr<GeometryEventSource> mEvents;
};

#endif