#include "multi_threads.h"

int main() {
  std::thread client_thr(client_thread_funk);
  std::thread server_thr(server_thread_funk);

  client_thr.join();
  server_thr.join();
}
