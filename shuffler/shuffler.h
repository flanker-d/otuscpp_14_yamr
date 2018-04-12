#pragma once

#include <shuffler/ishuffler.h>
#include <mapper/mapper.h>
#include <reducer/reducer.h>
#include <vector>
#include <thread>

namespace shuffle
{
  class shuffler : public ishuffler
  {
    public:
      shuffler(std::fstream &f, std::vector<part_of_file_info_t> &parts, int reducers_count);
      void init_shuffler() override;
      void send_data_to_reducer(const std::string& str) override;

    private:
      std::fstream &m_fstream;
      std::vector<part_of_file_info_t> &m_parts;
      int m_reducers_count;
      std::vector<map::mapper::ref> m_mappers;
      std::vector<reduce::reducer::ref> m_reducers;
  };

}

