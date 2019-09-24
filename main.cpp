#include "mktable.hpp"

int main(int argc, char *argv[])
{
    file fh;
    string file_name = GetFileNameFromArgv(argv);
    
    try
    {
        fh = OpenFile(file_name);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    uint column_size = GetLongestStringInFile(fh, ' ');
    CloseFile(fh);
    
    try
    {
        fh = OpenFile(file_name);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    WriteTable(fh, ' ', column_size);

    CloseFile(fh);
}
