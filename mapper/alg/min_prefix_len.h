#pragma once

#include <mapper/imapper_alg.h>
#include <set>

namespace map
{
  using n_gramms_set_t = std::multiset<std::string>;

  class min_prefix_len : public imapper_alg
  {
    public:
      void process_input_string(const std::string& a_str) override;
      void send_data_to_reducers(shuffle::ishuffler::weak_ref shuffler_weak_ref) override;

    private:
      void add_n_gramm(const std::string& a_n_gramm);

    private:
      n_gramms_set_t m_n_gramms;
  };
}

