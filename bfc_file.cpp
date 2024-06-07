#include <iostream>
#include <fstream>
#include <string>

std::string read_file(char* file_name){
  std::ifstream ifs;
  ifs.open(file_name);

  std::string text;
  ifs >> text;

  ifs.close();
  return text;
}
