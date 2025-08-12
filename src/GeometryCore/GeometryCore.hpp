#ifndef GeometryCore_hpp
#define GeometryCore_hpp

class GeometryCore {
    GeometryCore(OcafKernel aKernel);

    importDocument(Handle(TDocStd_Document) aSourceDocument);

    CommandStack commands();
    GeometryView view();
    GeometryEditor editor();

    EventsPublisher events();    
    
};

#endif