#include <file_splitter/file_splitter.h>

std::vector<part_of_file_info_t> file_splitter::split_file_to_parts(std::fstream &f, std::size_t count_of)
{
  f.seekg(0, std::ios_base::end);
  std::size_t size = f.tellg();
  std::size_t piece = (size / count_of);

  std::vector<std::size_t > vect;
  for(std::size_t i = 0; i < count_of; i++)
    vect.push_back(i * piece);

  for(std::size_t i = 1; i < count_of; i++)
    get_eol_pos(f, vect.at(i));

  std::vector<part_of_file_info_t> parts_of_file;
  for(std::size_t i = 1; i < count_of + 1; i++)
  {
    part_of_file_info_t part;
    part.begin_pos = vect.at(i - 1);

    if(i != count_of)
      part.end_pos = vect.at(i);
    else
      part.end_pos = size;

    parts_of_file.push_back(part);
  }
  return  parts_of_file;
}

bool file_splitter::check_eol(std::fstream &f, std::size_t cur_pos)
{
  char ch = 0;
  f.seekg(cur_pos);
  f.get(ch);
  if(ch == '\n')
    return true;
  else
    return false;
}

void file_splitter::get_eol_pos(std::fstream &f, std::size_t &cur_pos)
{
  if(check_eol(f, cur_pos))
    return;

  int offset = 1;
  while (true)
  {
    if(check_eol(f, cur_pos + offset))
    {
      cur_pos = cur_pos + offset + 1;
      return;
    }

    if(check_eol(f, cur_pos - offset))
    {
      cur_pos = cur_pos - offset + 1;
      return;
    }
    offset++;
  }
}
