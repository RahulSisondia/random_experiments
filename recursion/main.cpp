#include "../my_util.h"
#include "combinations.h"
#include "game_of_death.h"
#include "generate_balanced_parathesis.h"
#include "kth_symbol_779.h"
#include "permutation_special.h"
#include "permute.h"
#include "subset.h"
#include "synthesize_expression.h"

int main() {
  test_permutation_with_spaces();
  test_permute_with_case_change();
  test_letter_case_permutation();
  test_game_of_death();
  test_permutations();
  test_print_subset();
  test_combinations();
  test_kth_symbol();
  test_generate_balanced_parathesis();
  test_print_n_bit_binary();
  test_synthesize_expression();
  return 0;
}