#include "mktable.hpp"

file OpenFile(string file_name)
{
    file file_handler;
    file_handler.open(file_name, file::in);
    return(file_handler);
}

bool CloseFile(file &file_handler)
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
    file_handler >> line;
    return(line);
}

uint GetColumnCount(string header_line)
{
    uint counter = 0;
    for (char a : header_line)
    {
       if (a == ' ')
           counter++;
    }
    return(counter);
}

vector<string> StringSplit(string str, char delimiter)
{
    string temp("");
    vector<string> split_string;
    for (char c : str)
    {
        if (c != delimiter)
            temp.push_back(c);
        else
        {
            split_string.push_back(temp);
            temp.clear();
        }
    }
    return(split_string);
}

string GenerateHeader(string header_line)
{
    string header("+");
    for (int i = 1; i < COLUMN_SIZE; i++)
        header.append("-");
    header.append("+");
    return(header);
}

string GenerateLine(vector<string> line, uint columns)
{
    string formatted_line("|");
    for (uint i = 0; i < columns; i++)
    {
        formatted_line.append(line[i]);

    }
}
