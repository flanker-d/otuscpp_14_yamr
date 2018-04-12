#include <mapper/alg/min_prefix_len.h>
#include <include/data_types.h>

namespace map
{
  void min_prefix_len::process_input_string(const std::string &a_str)
  {
    std::string cur_n_gramm;
    for(auto it = a_str.begin(); it != a_str.end(); it++)
    {
      cur_n_gramm += *it;
      add_n_gramm(cur_n_gramm);
    }
  }

  void min_prefix_len::send_data_to_reducers(shuffle::ishuffler::weak_ref shuffler_weak_ref)
  {
    for(auto& it : m_n_gramms)
    {
      if(auto suffler_ref = shuffler_weak_ref.lock())
        suffler_ref->send_data_to_reducer(it);
    }
  }

  void min_prefix_len::add_n_gramm(const std::string &a_n_gramm)
  {
    m_n_gramms.emplace(a_n_gramm);
  }
}

