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
        file_handler >> temp;
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
    string header("+");
    for (int i = 1; i < column_size * GetColumnCount(header_line); i++)
    {
        if (i % column_size != 0)
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
        formatted_line.append(line[i]);
        for (auto j = line[i].length(); j < column_size; j++)
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

    cout << division << endl;
    cout << GenerateLine(StringSplit(line, delimiter), columns, column_size);

    while (true)
    {
        cout << division << endl;
        line = ReadLineFromFile(file_handler);
        if (file_handler.eof())
            return;
        cout << GenerateLine(StringSplit(line, delimiter), columns, column_size);
    }
}

string GetFileNameFromArgv(char *argv[])
{
    string r(argv[1]);
    return(r);
}
