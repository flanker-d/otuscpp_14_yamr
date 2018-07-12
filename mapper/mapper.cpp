#include <mapper/mapper.h>
#include <iostream>

namespace map
{
  using namespace std::chrono_literals;

  mapper::mapper(std::fstream &f, part_of_file_info_t &part, shuffle::ishuffler::ref shuffle_ref, int mapper_number)
    : m_fstream(f)
    , m_part_of_file_info(part)
    , m_shuffler(shuffle_ref)
    , m_number(mapper_number)
    , m_alg(create_map_alg())
  {
    m_thread = std::thread([this]{ run(); });
    std::this_thread::sleep_for(1ms);
  }

  void mapper::join()
  {
    if(m_thread.joinable())
      m_thread.join();
    //std::cout << "mapper " << m_number << " finished" << std::endl;
  }

  void mapper::run()
  {
    read_part_of_file();
    send_data_to_reducers();
  }

  void mapper::read_part_of_file()
  {
    std::size_t cur_pos = m_part_of_file_info.begin_pos;
    std::size_t end_pos = m_part_of_file_info.end_pos;
    //std::cout << "mapper " << m_number << " beg: " << cur_pos << ", end: " << end_pos << std::endl;
    m_fstream.seekg(cur_pos);
    while(cur_pos != end_pos)
    {
      std::string str;
      std::getline(m_fstream, str);
      m_alg->process_input_string(str);
      cur_pos = cur_pos + str.length() + 1;
      //if(cur_pos > end_pos)
        //break;
    }
  }

  void mapper::send_data_to_reducers()
  {
    m_alg->send_data_to_reducers(m_shuffler);
  }
}

