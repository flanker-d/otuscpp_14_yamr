#include <file_ops/file_splitter.h>
#include <shuffler/shuffler.h>

int main(int argc, char **argv)
{
  if(argc == 4)
  {
    std::string file = argv[1];
    int mappers_count = std::stoi(argv[2]);
    int reducers_count = std::stoi(argv[3]);
    std::fstream f(file, std::ios::in);

    file_ops::file_splitter splitter;
    std::vector<part_of_file_info_t> parts = splitter.split_file_to_parts(f, mappers_count);

    shuffle::ishuffler::ref sh = std::make_shared<shuffle::shuffler>(f, parts, reducers_count);
    sh->run();
  }
  else
    std::cout << "Usage: yamr <src> <mnum> <rnum>" << std::endl;

  return 0;
}