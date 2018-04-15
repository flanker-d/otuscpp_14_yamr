#include <reducer/reducer.h>
#include <file_ops/file_saver.h>

namespace reduce
{
  reducer::reducer(int num)
    : m_alg(create_reduce_alg())
    , m_queue(m_is_run)
    , m_num(num)
  {
    m_thread = std::thread([this]{ run(); });
  }

  void reducer::reduce_it(const std::string &str)
  {
    m_queue.push(str);
  }

  void reducer::join()
  {
    stop();

    if(m_thread.joinable())
      m_thread.join();
  }

  void reducer::run()
  {
    m_is_run = true;

    std::string str;
    while(m_is_run || !m_queue.empty())
    {
      m_queue.pop(str);
      if(!m_is_run && m_queue.empty())
        break;
      m_alg->reduce_it(str);
    }
    save_results();
  }

  void reducer::stop()
  {
    m_is_run = false;
    m_queue.notify_all();
  }

  void reducer::save_results()
  {
    std::shared_ptr<file_ops::file_saver> saver = std::make_shared<file_ops::file_saver>("reduce_" + std::to_string(m_num));
    m_alg->save_results(std::bind(&file_ops::file_saver::write, saver, std::placeholders::_1));
  }
}
