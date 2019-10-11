#ifndef MKTABLE_H
#define MKTABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using file = std::fstream;
using std::vector;

string GenerateDivision(string header_line, uint column_size, char delimiter);
string GenerateLine(vector<string> line, uint columns, uint column_size);

string ReadLineFromFile(file &file_handler);
file OpenFile(string file_name);
void CloseFile(file &file_handler);

uint GetColumnCount(string header_line, char delimiter);
vector<string> StringSplit(string str, char delimiter);

uint GetLongestStringInFile(file &file_handler, char delimiter);

string GetFileNameFromArgv(char *argv[]);

void WriteTable(file &file_handler, char delimiter, uint column_size);

#endif
