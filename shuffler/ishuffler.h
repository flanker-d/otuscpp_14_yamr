#pragma once

#include <memory>
namespace shuffle
{
  class ishuffler : public std::enable_shared_from_this<ishuffler>
  {
    public:
      using ref = std::shared_ptr<ishuffler>;
      using weak_ref = std::weak_ptr<ishuffler>;

      virtual void run() = 0;
      virtual void send_data_to_reducer(const std::string& str) = 0;
  };
}
