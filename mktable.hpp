#ifndef MKTABLE_H
#define MKTABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>


using std::wstring;
using file = std::fstream;
using std::vector;
using std::string;
using std::wstring;


wstring GenerateDivision(wstring header_line, uint column_size, char delimiter);
wstring GenerateLine(vector<wstring> line, uint columns, uint column_size);

wstring ReadLineFromFile(file &file_handler);
file OpenFile(string file_name);
void CloseFile(file &file_handler);

uint GetColumnCount(wstring header_line, wchar_t delimiter);
vector<wstring> StringSplit(wstring str, char delimiter);

uint GetLongestStringInFile(file &file_handler, wchar_t delimiter);

string GetFileNameFromArgv(char *argv[]);

void WriteTable(file &file_handler, wchar_t delimiter, uint column_size);

#endif
