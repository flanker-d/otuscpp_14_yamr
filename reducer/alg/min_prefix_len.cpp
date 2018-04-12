#include <reducer/alg/min_prefix_len.h>
#include <include/data_types.h>

namespace reduce
{
  void min_prefix_len::reduce_it(const std::string &str)
  {
    std::size_t len = str.length();
    auto found = m_n_gramms.find(len);
    if(found == m_n_gramms.end())
    {
      std::tuple<bool, std::multiset<std::string>> tup;
      bool &is_unique = std::get<0>(tup);
      std::multiset<std::string> &str_vect = std::get<1>(tup);

      is_unique = unique_value;
      str_vect.emplace(str);

      m_n_gramms.emplace(std::make_pair(len, tup));
    }
    else
    {
      auto &tup = found->second;
      bool &is_unique = std::get<0>(tup);
      std::multiset<std::string> &str_set = std::get<1>(tup);

      auto found_set = str_set.find(str);
      if(found_set == str_set.end())
        str_set.emplace(str);
      else
      {
        is_unique = non_unique_value;
        str_set.emplace(str);
      }
    }
  }
}
