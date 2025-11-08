



class AbstractNamedSelection {
    public:
    

    virtual ShapeType shapeType() const = 0;
    std::vector<TopoDS_Shape> shapes() const = 0;
    std::string name() const = 0;
};

class FaceNamedSelection {
    public:
    virtual ShapeType shapeType() const = 0;
    std::vector<TopoDS_Shape> shapes() const = 0;
    std::string name() const = 0;
};

class FaceNamedSelection {
    public:
    virtual ShapeType shapeType() const = 0;
    std::vector<TopoDS_Shape> shapes() const = 0;
    std::string name() const = 0;
};