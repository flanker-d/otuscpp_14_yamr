#pragma once

#include <thread>
#include <vector>
#include <fstream>
#include <include/data_types.h>

class mapper
{
  public:
    void run_mappers(std::fstream &f, std::vector<part_of_file_t> parts)
    {
      std::vector<std::thread> mappers_thread;
      for(int i = 0; i < parts.size(); i++)
      {
        mappers_thread.push_back(std::thread([this, &f, &parts, i]{
          read_part_of_file(f, parts.at(i));
        }));
      }

      for(auto &thr : mappers_thread)
        thr.join();
    }

  private:
    void read_part_of_file(std::fstream& f, part_of_file_t& part)
    {
      std::size_t cur_pos = part.begin_pos;
      std::size_t end_pos = part.end_pos;
      f.seekg(cur_pos);
      while(cur_pos != end_pos)
      {
        std::string str;
        std::getline(f, str);
        /*str_vect.emplace_back(str);*/
        cur_pos = cur_pos + str.length() + 1;
      }
    }
};
