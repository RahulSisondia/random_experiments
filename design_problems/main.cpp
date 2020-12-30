#include "../hashing/lru_cache.h"
#include "Singleton.h"
#include "twitter.h"

int main() {
  check_singleton();
  check_twitter();
  test_lru_cache_146();
  return 0;
}