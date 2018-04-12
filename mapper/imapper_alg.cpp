#include <mapper/alg/min_prefix_len.h>

namespace map
{
  imapper_alg::ref create_map_alg()
  {
    return std::make_shared<min_prefix_len>();
  }
}
