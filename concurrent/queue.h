#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

namespace concurrent
{
  template <typename T>
  class queue
  {
    public:

      queue(std::atomic<bool>& is_run)
        : m_is_run(is_run)
      {
      }

      bool pop(T& item)
      {
        std::unique_lock<std::mutex> mlock(m_mutex);
        m_cond.wait(mlock, [this]{ return (!m_queue.empty() || !(m_is_run));});
        if(!m_queue.empty())
        {
          item = m_queue.front();
          m_queue.pop();
        }
      }

      void push(const T& item)
      {
        std::unique_lock<std::mutex> mlock(m_mutex);
        m_queue.push(item);
        mlock.unlock();
        m_cond.notify_one();
      }

      bool empty()
      {
        std::unique_lock<std::mutex> mlock(m_mutex);
        return m_queue.empty();
      }

      void notify_all()
      {
        m_cond.notify_all();
      }

    private:
      std::queue<T> m_queue;
      std::mutex m_mutex;
      std::condition_variable m_cond;
      std::atomic<bool>& m_is_run;
  };
}
