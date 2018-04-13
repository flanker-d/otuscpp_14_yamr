#pragma once

#include <memory>
#include <thread>
#include <reducer/ireducer_alg.h>
#include <concurrent/queue.h>
#include <atomic>

namespace reduce
{
  class reducer
  {
    public:
      using ref = std::shared_ptr<reducer>;

    public:
      reducer(int num);
      void reduce_it(const std::string& str);
      void join();

    private:
      void run();
      void stop();
      void save_results();

    private:
      ireducer_alg::ref m_alg;
      std::thread m_thread;
      concurrent::queue<std::string> m_queue;
      std::atomic<bool> m_is_run;
      int m_num;
  };
}
