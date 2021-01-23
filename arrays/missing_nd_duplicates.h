
#include "../my_util.h"

void getTwoElements(int arr[], int n, int *x, int *y) {
  int xor1;       /* Will hold xor of all elements and numbers from 1 to n */
  int set_bit_no; /* Will have only single set bit of xor1 */
  int i;
  *x = 0;
  *y = 0;

  xor1 = arr[0];

  /* Get the xor of all array elements elements */
  for (i = 1; i < n; i++) xor1 = xor1 ^ arr[i];

  /* XOR the previous result with numbers from 1 to n*/
  for (i = 1; i <= n; i++) xor1 = xor1 ^ i;

  /* Get the rightmost set bit in set_bit_no */
  set_bit_no = xor1 & ~(xor1 - 1);  // xor1 & (2’s complement of xor1)

  /* Now divide elements in two sets by comparing rightmost set
  bit of xor1 with bit at same position in each element. Also, get XORs
  of two sets. The two XORs are the output elements.
  The following two for loops serve the purpose */
  for (i = 0; i < n; i++) {
    if (arr[i] & set_bit_no)
      *x = *x ^ arr[i]; /* arr[i] belongs to first set */
    else
      *y = *y ^ arr[i]; /* arr[i] belongs to second set*/
  }
  for (i = 1; i <= n; i++) {
    if (i & set_bit_no)
      *x = *x ^ i; /* i belongs to first set */
    else
      *y = *y ^ i; /* i belongs to second set*/
  }

  /* Now *x and *y hold the desired output elements */
}

void test_find_duplilcate_missing_elements() {
  int arr[4] = {1, 2, 2, 4};
  pair<int, int> p;
  getTwoElements(arr, 4, &p.first, &p.second);
  CHECK(p, {3, 2});
  PRINT_MSG;
}
/*
Given an unsorted array of size n. Array elements are in the range from 1 to n.
Some numbers from set {1, 2, …n} are missing and some are repeating in the
array. Find these two numbers in order of one space.


Input:[3 1 1 5 3]

Duplicate = 3,1  Missing = 2,4
*/
/*
We could solve the above problem using this swap sort techinique.
The only draw back that it has is that it requires input array to be modified.
*/
pair<vector<int>, vector<int>> find_all_missing_duplicate_elements(
    vector<int> v) {
  int i = 0;
  while (i < v.size()) {
    int j = v[i] - 1;
    if (v[i] != v[j]) {
      swap(v[i], v[j]);
    } else
      i++;
  }
  vector<int> missing;
  vector<int> duplicate;
  for (i = 0; i < v.size(); i++) {
    if (v[i] != i + 1) {
      missing.push_back(i + 1);
      duplicate.push_back(v[i]);
    }
  }
  return {missing, duplicate};
}

void test_find_all_missing_duplicate_elements() {
  vector<int> v = {3, 1, 1, 5, 3};
  auto p = find_all_missing_duplicate_elements(v);
  CHECK(p.first, {2, 4});   // Missing
  CHECK(p.second, {1, 3});  // Duplicate
  PRINT_MSG;
}