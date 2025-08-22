#ifndef GeometryCore_hpp
#define GeometryCore_hpp

#include <memory>

class GeometryCore {
    public:
    GeometryCore(std::unique_ptr<OcafKernel> aKernel);

    importDocument(std::unique_ptr<PartDocument> aPartDocument);

    std::unique_ptr<CommandStack> commands();
    std::unique_ptr<GeometryView> view();
    std::unique_ptr<GeometryEditor> editor();
    std::unique_ptr<EventsPublisher> events();

    private:
    std::unique_ptr<OcafKernel> mOcafKernel;
};

#endif