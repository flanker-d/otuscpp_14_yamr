#include <fstream>
#include <iostream>
#include <vector>
#include <thread>

struct part_of_file_t
{
  std::size_t begin_pos;
  std::size_t end_pos;
};

bool check_eol(std::fstream& f, std::size_t cur_pos)
{
  char ch = 0;
  f.seekg(cur_pos);
  f.get(ch);
  if(ch == '\n')
    return true;
  else
    return false;
}

void get_eol_pos(std::fstream& f, std::size_t &cur_pos)
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

std::vector<part_of_file_t> split_file_to_parts(std::fstream& f, std::size_t count_of)
{
  f.seekg(0, std::ios_base::end);
  std::size_t size = f.tellg();
  std::size_t piece = (size / count_of);

  std::vector<std::size_t > vect;
  for(std::size_t i = 0; i < count_of; i++)
    vect.push_back(i * piece);

  for(std::size_t i = 1; i < count_of; i++)
    get_eol_pos(f, vect.at(i));

  std::vector<part_of_file_t> parts_of_file;
  for(std::size_t i = 1; i < count_of + 1; i++)
  {
    part_of_file_t part;
    part.begin_pos = vect.at(i - 1);

    if(i != count_of)
      part.end_pos = vect.at(i);
    else
      part.end_pos = size;

    parts_of_file.push_back(part);
  }
  return  parts_of_file;
}

void read_part_of_file(std::fstream& f, part_of_file_t& part)
{
  std::size_t cur_pos = part.begin_pos;
  std::size_t end_pos = part.end_pos;
  f.seekg(cur_pos);
  while(cur_pos != end_pos)
  {
    std::string str;
    std::getline(f, str);
    /*str_vect.emplace_back(str);*/
    cur_pos = cur_pos + str.length() + 1;
  }
}

int main(int argc, char **argv)
{
  int mappers_count = 4;
  std::fstream f("../file.txt", std::ios::in);
  std::vector<part_of_file_t> parts = split_file_to_parts(f, mappers_count);

  std::vector<std::thread> mappers_thread;
  for(int i = 0; i < mappers_count; i++)
  {
    mappers_thread.push_back(std::thread([&f, &parts, i]{
      read_part_of_file(f, parts.at(i));
    }));
  }

  for(auto &thr : mappers_thread)
    thr.join();

  return 0;
}