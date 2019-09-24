#include "mktable.hpp"

using std::cout;
using std::endl;

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
    std::getline(file_handler, line);
    return(line);
}

uint GetColumnCount(string header_line)
{
    uint counter = 1;
    for (char a : header_line)
    {
       if (a == ' ')
           counter++;
    }
    return(counter);
}

vector<string> StringSplit(string str, char delimiter)
{
    str.push_back(delimiter);
    string temp("");
    vector<string> split_string;
    for (char c : str)
    {
        if (c != delimiter)
        {
            temp.push_back(c);
        }
        else
        {
            split_string.push_back(temp);
            temp.clear();
        }
    }
    return(split_string);
}

uint GetLongestStringInFile(file &file_handler, char delimiter)
{
    if (not file_handler.is_open())
    {
        throw("Read error: file wasn't open");
        return(0);
    }

    uint longest = 0;
    while (not file_handler.eof())
    {
        string temp;
        temp = ReadLineFromFile(file_handler);
        vector<string> line = StringSplit(temp, delimiter);
        for (string s : line)
        {
            if (s.length() > longest)
                longest = s.length();
        }
    }
    return(longest);
}

string GenerateDivision(string header_line, uint column_size)
{
    string header;
    auto size = (column_size + 1)* GetColumnCount(header_line);
    for (int i = 0; i < size; i++)
    {
        if (i % (column_size + 1) != 0)
            header.push_back('-');
        else
            header.push_back('+');

    }
    header.push_back('+');
    return(header);
}

string GenerateLine(vector<string> line, uint columns, uint column_size)
{
    string formatted_line("|");
    for (uint i = 0; i < columns; i++)
    {
        auto space_length = (((column_size + columns) - line[i].length()) / 2) - 1;
        for (auto j = 0; j < space_length and line[i].length() < column_size; j++)
        {
            formatted_line.push_back(' ');
        }
        formatted_line.append(line[i]);
        for (auto j = space_length + line[i].length(); j < column_size; j++)
        {
            formatted_line.push_back(' ');
        }
        formatted_line.push_back('|');
    }
    return(formatted_line);
}

void WriteTable(file &file_handler, char delimiter, uint column_size)
{
    string line = ReadLineFromFile(file_handler);
    string division = GenerateDivision(line, column_size);
    uint columns = GetColumnCount(line);
    vector<string> split_line = StringSplit(line, delimiter);

    cout << division << endl;
    cout << GenerateLine(split_line, columns, column_size) << endl;

    while (true)
    {
        cout << division << endl;
        line = ReadLineFromFile(file_handler);
        if (file_handler.eof())
            return;
        cout << GenerateLine(StringSplit(line, delimiter), columns, column_size) << endl;
    }
}

string GetFileNameFromArgv(char *argv[])
{
    string r(argv[1]);
    return(r);
}