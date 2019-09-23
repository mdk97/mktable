#pragme once

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using file = std::fstream;

string GenerateHeader(string header_line);
string GenerateLine(string line);
string GenerateFooter();

string ReadLineFromFile(file &file_handler);
file OpenFile(string file_name);
bool CloseFile(string &file_handler);

uint ParseFile(string header_line);
