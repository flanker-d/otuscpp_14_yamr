#pragma once

#include <mapper/imapper_alg.h>
#include <include/data_types.h>
#include <shuffler/ishuffler.h>
#include <fstream>
#include <thread>
namespace map
{
  class mapper
  {
    public:
      using ref = std::shared_ptr<mapper>;

      mapper(std::fstream &f, part_of_file_info_t &part, shuffle::ishuffler::ref shuffle_ref);
      void join();

    private:
      void run();
      void read_part_of_file();
      void send_data_to_reducers();

    private:
      std::fstream &m_fstream;
      part_of_file_info_t m_part_of_file_info;
      shuffle::ishuffler::weak_ref m_shuffler;
      imapper_alg::ref m_alg;
      std::thread m_thread;
  };
}

