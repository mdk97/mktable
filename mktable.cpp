#include "mktable.hpp"

file OpenFile(string file_name)
{
    file file_handler;
    file_handler.open(file_name, file::in);
    return(file_handler);
}

bool CloseFile(string &file_handler);
{
    if (file_handler.is_open())
        file_handler.close();
    else
        return(false);
    return(true);
}

string ReadLineFromFile(file &file_handler)
{
    if (not file_handler.is_open())
    {
        throw ("File is not open");
        return("");
    }
    string line;
    line << file_handler;
    return(line);
}

uint ParseFile(string header_line)
{
    uint counter = 0;
    for (char a : header_line)
    {
       if (a == ' ')
           counter++;
    }
    return(counter);
}

string GenerateHeader(string header_line)
{
    string header("+");
    for (int i = 1; i < header_line.length(); i++)
        header.append("-");
    header.append("+");
    return(header);
}

string GenerateLine(string line, uint columns)
{
    string formatted_line("|");
}
