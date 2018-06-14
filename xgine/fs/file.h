#ifndef FILE_H
#define FILE_H

#include "xgine/base.h"

namespace xgine {

namespace fs {

class File
{
public:
    enum class Mode
    {
        M_TEXT,
        M_BIN
    };

    static std::shared_ptr<File> Create(std::string name, Mode mode);
    static void Destroy(File* file);

    std::string GetName();
    Mode GetMode();
    char* GetData();
    uint32_t GetSize();


private:
    File();
    ~File();

    std::string name;
    Mode mode;
    char* data;
    uint32_t size;

    DISALLOW_COPY_AND_ASSIGN(File);
};

}

}

#endif // FILE_H
