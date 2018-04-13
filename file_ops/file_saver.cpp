#include <file_ops/file_saver.h>

namespace file_ops
{
  file_saver::file_saver(const std::string &file_path) : m_fstream(file_path, std::ios_base::app)
  {
  }

  void file_saver::write(const std::string &str)
  {
    m_fstream << str << std::endl;
  }
}

