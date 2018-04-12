#include <reducer/reducer.h>

namespace reduce
{
  reducer::reducer()
    : m_alg(create_reduce_alg())
  {
  }

  void reducer::reduce_it(const std::string &str)
  {
    m_alg->reduce_it(str);
  }
}
