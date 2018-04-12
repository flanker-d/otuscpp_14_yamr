#pragma once

#include <reducer/ireducer_alg.h>
#include <map>
#include <set>

namespace reduce
{
  class min_prefix_len : public ireducer_alg
  {
    public:
      void reduce_it(const std::string& str) override;

    private:
      std::map<std::size_t, std::tuple<bool, std::multiset<std::string>>> m_n_gramms;
  };
}
