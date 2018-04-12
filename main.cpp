#include <file_splitter/file_splitter.h>
#include <shuffler/shuffler.h>

int main(int argc, char **argv)
{
  int mappers_count = 4;
  int reducers_count = 3;
  std::fstream f("../numbers.txt", std::ios::in);

  file_splitter splitter;
  std::vector<part_of_file_info_t> parts = splitter.split_file_to_parts(f, mappers_count);

  shuffle::ishuffler::ref sh = std::make_shared<shuffle::shuffler>(f, parts, reducers_count);
  sh->init_shuffler();

  return 0;
}