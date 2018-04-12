#pragma once

#include <memory>
#include <reducer/ireducer_alg.h>

namespace reduce
{
  class reducer
  {
    public:
      using ref = std::shared_ptr<reducer>;

    public:
      reducer();
      void reduce_it(const std::string& str);

    private:
      ireducer_alg::ref m_alg;
  };
}
