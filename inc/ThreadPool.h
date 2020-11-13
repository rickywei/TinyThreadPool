#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace tiny {

using namespace std;

class ThreadPool {
 public:
  using Task = function<void()>;
  ThreadPool(size_t thread_num = 1);
  ~ThreadPool();
  void ThreadFunc();
  void AddTask(Task &&task);

 private:
  struct Pool {
    mutex mtx;
    condition_variable cv;
    bool isClose;
    queue<Task> tasks;
  };
  shared_ptr<Pool> pool_;
};

}  // namespace tiny

#endif