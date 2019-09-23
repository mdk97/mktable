#pragme once

#include <iostream>
#include <fstream>
#include <string>

using std::string;

string GenerateHeader(string header_line);
string GenerateLine(string line);
string GenerateFooter();

string ReadLineFromFile(fstream &file_handler);
fstream OpenFile(string file_name);
bool CloseFile(string &file_handler);
