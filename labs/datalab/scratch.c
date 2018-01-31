#include <stdio.h>

int main() {
  int x = 0x80000000;
  int y = x<<31;
  std::out << std::hex << y << std::endl;
  int z = y>>31;
  std::out << std::hex << z << std::endl;

  return 0;
}
