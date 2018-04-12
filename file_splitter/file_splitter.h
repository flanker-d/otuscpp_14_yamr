#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <include/data_types.h>


class file_splitter
{
  public:
    std::vector<part_of_file_info_t> split_file_to_parts(std::fstream& f, std::size_t count_of);

  private:
    bool check_eol(std::fstream& f, std::size_t cur_pos);
    void get_eol_pos(std::fstream& f, std::size_t &cur_pos);
};
