#include "mktable.hpp"
#include "rainbow/C++/rainbow.hpp"
#include <cmath>

using std::cout;
using std::endl;


std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

file OpenFile(string file_name)
{
    file file_handler;
    file_handler.open(file_name, file::in);
    return(file_handler);
}

void CloseFile(file &file_handler)
{
    if (file_handler.is_open())
        file_handler.close();
}

wstring ReadLineFromFile(file &file_handler)
{
    wstring s;
    if (not file_handler.is_open())
    {
        throw ("File is not open");
        s = converter.from_bytes("");
    }
    string line;
    std::getline(file_handler, line);
    s = converter.from_bytes(line);
    return(s);
}

uint GetColumnCount(wstring header_line, wchar_t delimiter)
{
    uint counter = 1;
    for (wchar_t a : header_line)
    {
       if (a == delimiter)
           counter++;
    }
    return(counter);
}

vector<wstring> StringSplit(wstring str, wchar_t delimiter)
{
    str.push_back(delimiter);
    wstring temp;
    vector<wstring> split_string;
    for (wchar_t c : str)
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

uint GetLongestStringInFile(file &file_handler, wchar_t delimiter)
{
    if (not file_handler.is_open())
    {
        throw("Read error: file wasn't open");
        return(0);
    }

    uint longest = 0;
    while (not file_handler.eof())
    {
        wstring temp;
        temp = ReadLineFromFile(file_handler);
        vector<wstring> line = StringSplit(temp, delimiter);
        for (wstring s : line)
        {
            if (s.length() > longest)
                longest = s.length();
        }
    }
    return(longest);
}

wstring GenerateDivision(wstring header_line, uint column_size, wchar_t delimiter, DivisionCategory c)
{
    // The string that will be used to build the actual header
    wstring header;

    // Calculating the size of the header (width of the table)
    auto size = (column_size + 3) * GetColumnCount(header_line, delimiter);


    for (int i = 0; i < size; i++)
    {
        if (c == HEADER)
        {
            if (i == 0)
                header.append(converter.from_bytes("┌"));
            else if (i % (column_size + 3) == 0)
                header.append(converter.from_bytes("┬"));
            else
                header.append(converter.from_bytes("─"));                
        }
        else if (c == BODY)
        {
            if (i == 0)
                header.append(converter.from_bytes("├"));
            else if (i % (column_size + 3) == 0)
                header.append(converter.from_bytes("┼"));
            else
                header.append(converter.from_bytes("─"));
        }
        else if (c == FOOTER)
        {
            if (i == 0)
                header.append(converter.from_bytes("└"));
            else if (i % (column_size + 3) == 0)
                header.append(converter.from_bytes("┴"));
            else
                header.append(converter.from_bytes("─"));
        }
    }
    if (c == HEADER)
        header.append(converter.from_bytes("┐"));
    else if (c == BODY)
        header.append(converter.from_bytes("┤"));
    else if (c == FOOTER)
        header.append(converter.from_bytes("┘"));
    return(header);
}

wstring GenerateLine(vector<wstring> line, uint columns, uint column_size)
{
    wstring formatted_line = converter.from_bytes("│");
    for (uint i = 0; i < columns; i++)
    {
        auto space_length = (column_size - line[i].length()) + 2;
        auto j = 0;
        for (; j < (uint)floor((double)space_length / 2.0); j++)
        {
            formatted_line.push_back(' ');
        }
        formatted_line.append(line[i]);
        for (j = 0; j < (uint)ceil((double)space_length / 2.0); j++)
        {
            formatted_line.push_back(' ');
        }
        formatted_line.append(converter.from_bytes("│"));
    }
    return(formatted_line);
}

void WriteTable(file &file_handler, wchar_t delimiter, uint column_size)
{
    // Read the header line
    wstring line = ReadLineFromFile(file_handler);

    // Generate the divisions
    wstring header_division = GenerateDivision(line, column_size, delimiter, DivisionCategory::HEADER);
    wstring body_division = GenerateDivision(line, column_size, delimiter, DivisionCategory::BODY);
    wstring footer_division = GenerateDivision(line, column_size, delimiter, DivisionCategory::FOOTER);

    // Get column count
    uint columns = GetColumnCount(line, delimiter);
    vector<wstring> split_line = StringSplit(line, delimiter);

    print_colored(converter.to_bytes(header_division), GREEN, BG_DEFAULT);
    cout << endl;
    print_colored(
        converter.to_bytes(
            GenerateLine(split_line, columns, column_size)
            ), GREEN, BG_DEFAULT);
    cout << endl;

    while (true)
    {
        print_colored(converter.to_bytes(body_division), CYAN, BG_DEFAULT);
        line = ReadLineFromFile(file_handler);
        if (file_handler.eof())
        {
            cout << "\r";
            print_colored(converter.to_bytes(footer_division), CYAN, BG_DEFAULT);
            cout << endl;
            return;
        }
        cout << endl;
        print_colored(
            converter.to_bytes(
                GenerateLine(StringSplit(line, delimiter), columns, column_size)), 
                                CYAN, BG_DEFAULT);
        cout << endl;
    }
}

string GetFileNameFromArgv(char *argv[])
{
    string r(argv[1]);
    return(r);
}