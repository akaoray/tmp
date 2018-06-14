#include "file.h"

namespace xgine {

namespace fs {

File::File()
{
    XDEBUG();
}

File::~File()
{
    XDEBUG();
}

std::shared_ptr<File> File::Create(std::string name, Mode mode)
{
    XDEBUG();

    std::shared_ptr<File> file(new File(), File::Destroy);
    file->name = name;
    file->mode = mode;

    std::ifstream f;
    switch(mode)
    {
    case Mode::M_TEXT:
        f.open(name);
        break;
    case Mode::M_BIN:
        f.open(name, std::ifstream::binary);
        break;
    }

    if(!f)
    {
        XMESSAGE("Invalid open file " + name);
        return nullptr;
    }

    f.seekg(0, f.end);
    file->size = f.tellg();
    f.seekg(0, f.beg);
    file->data = new char[file->size];
    f.read(file->data, file->size);
    f.close();

    return file;
}

void File::Destroy(File* file)
{
    XDEBUG();

    assert(file != nullptr);

    delete [] file->data;
    delete file;
}

std::string File::GetName()
{
    XDEBUG();

    return this->name;
}

File::Mode File::GetMode()
{
    XDEBUG();

    return this->mode;
}

char* File::GetData()
{
    XDEBUG();

    return this->data;
}

uint32_t File::GetSize()
{
    XDEBUG();

    return this->size;
}

}

}

