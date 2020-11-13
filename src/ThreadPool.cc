#include "ThreadPool.h"

using namespace tiny;

ThreadPool::ThreadPool(size_t thread_num)
    : pool_(make_shared<ThreadPool::Pool>()) {
  thread_num = thread_num > 0 ? thread_num : 1;
  for (size_t i = 0; i < thread_num; ++i) {
    thread t(&ThreadPool::ThreadFunc, this);
    if (t.joinable()) {
      t.detach();
    }
  }
}

ThreadPool::~ThreadPool() {
  if (static_cast<bool>(pool_)) {
    {
      lock_guard<mutex> locker(pool_->mtx);
      pool_->isClose = true;
    }
    pool_->cv.notify_all();
  }
}

void ThreadPool::ThreadFunc() {
  unique_lock<mutex> locker(pool_->mtx);
  while (true) {
    if (!pool_->tasks.empty()) {
      Task task = move(pool_->tasks.front());
      pool_->tasks.pop();
      locker.unlock();
      task();
      locker.lock();
    } else if (pool_->isClose) {
      break;
    } else {
      pool_->cv.wait(locker);
    }
  }
}

void ThreadPool::AddTask(Task&& task) {
  {
    lock_guard<mutex> locker(pool_->mtx);
    pool_->tasks.emplace(task);
  }
  pool_->cv.notify_one();
}