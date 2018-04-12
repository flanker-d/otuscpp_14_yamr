#pragma once

#include <memory>

namespace reduce
{
  class ireducer_alg
  {
    public:
      using ref = std::shared_ptr<ireducer_alg>;

      virtual void reduce_it(const std::string& str) = 0;
  };

  ireducer_alg::ref create_reduce_alg();
}

