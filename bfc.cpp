#include <iostream>
#include <string>
#include "bfc_file.hpp"
#include <vector>

int main(int argc, char** argv){

  if(argc < 2){
    std::cout << "Usage: " << argv[0] << " <file.bf>\n";
    return 1;
  }
  std::string code = read_file(argv[1]);
  std::cout << ";" << code << "\n";
  std::string assembly_code;

  // append default nasm code
  assembly_code.append("%define STACK_BASE_REG rsp\n%define RET_REG rax\nglobal _start\nputchar:\nmov ecx, [STACK_BASE_REG+8]\nmov [putchar_db_01], ecx\nlea ecx, [putchar_db_01]\nmov eax, 4\nmov ebx, 1\nmov ecx, putchar_db_01\nmov edx, 1\nint 0x80\nret\ngetchar:\nmov eax, 3\nmov ebx, 0\nlea ecx, [getchar_db_01]\nmov edx, 2\nint 0x80\nmov RET_REG, [getchar_db_01]\nret\nbfmem_getptr:\nmov r14d, memory\nadd r14d, r15d\nret\n_start:\nmov r15d, 0\n");
  
  int next_loop_index = 0;
  int getchar_loop_index = 0;
  std::vector<int> loops;

  int i=0;
  char c;

  code.push_back('%');

  while(i<code.size()){
    c = code.at(i);
    int times=0;
    switch(c){
      case '+':
        times = 0;
        while(c == '+'){
          times++;
          i++;
          c = code.at(i);
        }

        assembly_code += "call bfmem_getptr\n";
        assembly_code += "add byte[r14d], ";
        assembly_code += std::to_string(times);
        assembly_code += "\n";
        i--;

        break;
      case '-':
        times = 0;
        while(c == '-'){
          times++;
          i++;
          c = code.at(i);
        }

        assembly_code += "call bfmem_getptr\n";
        assembly_code += "add byte[r14d], -";
        assembly_code += std::to_string(times);
        assembly_code += "\n";
        i--;

        break;
      case '.':
        assembly_code += "call bfmem_getptr\n";
        assembly_code += "movsx rax, byte[r14d]\n";
        assembly_code += "push rax\n";
        assembly_code += "call putchar\n";
        break;
      case ',':
        getchar_loop_index++;
        assembly_code += "call bfmem_getptr\n";
        assembly_code += "call getchar\n";
        assembly_code += "getchar_cnv_"+std::to_string(getchar_loop_index)+":\n";
        assembly_code += "inc byte[r14d]\n";
        assembly_code += "dec RET_REG\n";
        assembly_code += "test RET_REG, RET_REG\n";
        assembly_code += "jnz getchar_cnv_"+std::to_string(getchar_loop_index)+"\n";
        assembly_code += "getchar_cnv_end_"+std::to_string(getchar_loop_index)+":\n";
        break;
      case '<':
        times = 0;
        while(c == '<'){
          times++;
          i++;
          c = code.at(i);
        }

        assembly_code += "sub r15d, "+std::to_string(times)+"\n";
        i--;
        break;
      case '>':
        times = 0;
        while(c == '>'){
          times++;
          i++;
          c = code.at(i);
        }

        assembly_code += "add r15d, "+std::to_string(times)+"\n";
        i--;
        break;
      case '[':
        next_loop_index += 1;
        loops.push_back(next_loop_index);
        assembly_code += "bf_loop_"+std::to_string(loops.back())+":\n";
        break;
      case ']':
        assembly_code += "call bfmem_getptr\n";
        assembly_code += "mov al, byte[r14d]\n";
        assembly_code += "test al, al\n";
        assembly_code += "jnz bf_loop_"+std::to_string(loops.back())+"\n";
        loops.pop_back();
        break;
    }
    i++;
  }

  // append data section
  assembly_code.append("mov eax, 1\nmov ebx, 0\nint 0x80\nsection .data\nputchar_db_01 db 0\ngetchar_db_01 times 2 db 0\nbf_inst_add_db_01 db 0\nmemory times 30000 db 0");

  std::cout << assembly_code << "\n";

  return 0;
}
