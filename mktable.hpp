#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using file = std::fstream;
using std::vector;

extern const auto COLUMN_SIZE;

string GenerateHeader(string header_line);
string GenerateLine(vector<string> line, uint columns);
string GenerateFooter();

string ReadLineFromFile(file &file_handler);
file OpenFile(string file_name);
bool CloseFile(file &file_handler);

uint GetColumnCount(string header_line);
vector<string> StringSplit(string str, char delimiter);
