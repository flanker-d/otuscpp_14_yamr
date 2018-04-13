#pragma once

#include <fstream>

namespace file_ops
{
  class file_saver
  {
    public:
      file_saver(const std::string& file_path);

      void write(const std::string& str);

    private:
      std::fstream m_fstream;
  };
}
