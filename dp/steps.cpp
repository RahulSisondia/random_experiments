#include <iostream>
#include <vector>

using namespace std;

namespace {
void display(vector<int> p) {
  for (auto i : p)
    std::cout << i << " ";
  std::cout << endl;
}

void find_path(int n, const int k, vector<int> &result) {
  if (n < 0 || k < 0)
    return;

  if (n == 0)
    display(result);

  for (int j = 1; j <= k; j++) {
    result.push_back(j);
    find_path(n - j, k, result);
    result.pop_back();
  }
}

int compute_distanc(int n, int k) {
  vector<int> vect(n + 1, 0);
  vect[0] = 1;
  vect[1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j <= k && j <= i; j++)
      vect[i] += vect[i - j];
  }
  for (int i = 0; i < vect.size(); i++)
    cout << vect[i] << "  ";
  cout << endl << " Paths : " << endl;
  vector<int> res;
  find_path(n, k, res);
  return vect.back();
}
} // namespace

int main() {
  cout << compute_distanc(3, 2) << endl;
  cout << compute_distanc(4, 2) << endl;
  cout << compute_distanc(5, 2) << endl;
  cout << compute_distanc(5, 3) << endl;
  return 0;
}
