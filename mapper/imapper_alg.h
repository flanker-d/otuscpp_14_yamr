#pragma once

#include <string>
#include <memory>
#include <shuffler/ishuffler.h>

namespace map
{
  class imapper_alg
  {
    public:
      using ref = std::shared_ptr<imapper_alg>;

    public:
      virtual void process_input_string(const std::string& a_str) = 0;
      virtual void send_data_to_reducers(shuffle::ishuffler::weak_ref shuffler_weak_ref) = 0;
  };

  imapper_alg::ref create_map_alg();
}

