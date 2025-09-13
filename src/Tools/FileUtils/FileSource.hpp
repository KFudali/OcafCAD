#ifndef FileSource_hpp
#define FileSource_hpp

#include "AbstractInputSource.hpp"
#include <fstream>

class FileSource : AbstractInputSource {
    public:
    FileSource(
        const std::string& aPath
    ) : mFilePath(aPath), mFileStream(aPath){}

    std::istream& stream() override {return mFileStream;} ;
    std::string name() override {return mFilePath;} ;
    private:

    const std::string mFilePath;
    std::ifstream mFileStream;
};

#endif