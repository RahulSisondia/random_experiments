#include "stack.h"

#include "max_histogram_area.h"

int main() {
  test_next_greater_to_right();
  test_next_greater_to_left();
  test_next_smaller_to_left();
  test_next_smaller_to_right();
  test_next_smaller_index_to_left();
  test_next_smaller_index_to_right();
  test_max_histogram_area();
  test_max_rectangle_area_binary_matrix();
  return 0;
}