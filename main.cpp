#include <file_splitter/file_splitter.h>
#include <mapper/mapper.h>
#include <reducer/reducer.h>

int main(int argc, char **argv)
{
  int mappers_count = 4;
  std::fstream f("../file.txt", std::ios::in);
  file_splitter splitter;
  std::vector<part_of_file_t> parts = splitter.split_file_to_parts(f, mappers_count);

  return 0;
}