#include <shuffler/shuffler.h>
#include <functional>
#include <iostream>

namespace shuffle
{
  shuffler::shuffler(std::fstream &f, std::vector<part_of_file_info_t> &parts, int reducers_count)
    : m_fstream(f)
    , m_parts(parts)
    , m_reducers_count(reducers_count)
  {
  }

  void shuffler::init_shuffler()
  {
    for(int i = 0; i < m_reducers_count; i++)
      m_reducers.push_back(std::make_shared<reduce::reducer>(i));

    int mappers_count = m_parts.size();
    for(int i = 0; i < mappers_count; i++)
      m_mappers.push_back(std::make_shared<map::mapper>(m_fstream, m_parts.at(i), shared_from_this()));

    for(auto &thr : m_mappers)
      thr->join();

    for(auto &thr : m_reducers)
      thr->join();

    return;
  }

  void shuffler::send_data_to_reducer(const std::string &str)
  {
    std::hash<std::string> hash_fn;
    std::string s = std::to_string(str.c_str()[0]);
    std::size_t hash = hash_fn(s);
    int reducer_idx = hash % m_reducers.size();
    m_reducers.at(reducer_idx)->reduce_it(str);
  }
}
