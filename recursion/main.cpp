#include "../my_util.h"
#include "game_of_death.h"
#include "permutation_special.h"

int main() {
  test_permutation_with_spaces();
  test_permute_with_case_change();
  test_letter_case_permutation();
  test_game_of_death();
  return 0;
}