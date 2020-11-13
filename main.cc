#include <iostream>

#include "ThreadPool.h"

using namespace tiny;

void ThreadFunc(int i) { cout << "Count " << i << endl; }

int main() {
  cout << "Start test threadpool..." << endl;
  ThreadPool pool;
  for (int i = 0; i < 10; ++i) {
    // bind(ThreadFunc, i)();
    pool.AddTask(bind(&ThreadFunc, i));
  }
  this_thread::sleep_for(5s);
  cout << "Finish test threadpool..." << endl;
  return 0;
}