#pragma once

#include <memory>
#include <functional>

namespace reduce
{
  class ireducer_alg
  {
    public:
      using ref = std::shared_ptr<ireducer_alg>;

      virtual void reduce_it(const std::string& str) = 0;
      virtual void save_results(std::function<void(const std::string&)> save_func) = 0;
  };

  ireducer_alg::ref create_reduce_alg();
}

