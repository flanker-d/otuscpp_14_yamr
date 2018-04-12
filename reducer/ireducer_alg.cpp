#include <reducer/alg/min_prefix_len.h>

namespace reduce
{
  ireducer_alg::ref create_reduce_alg()
  {
    return std::make_shared<min_prefix_len>();
  }

}
