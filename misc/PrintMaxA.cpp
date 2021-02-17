// PrintMaxA.cpp : Defines the entry point for the console application.
// https://www.geeksforgeeks.org/how-to-print-maximum-number-of-a-using-given-four-keys/
#include <vector>

using namespace std;

// this function returns the optimal length string for N keystrokes
int findoptimal(int N) {
  // The optimal string length is N when N is smaller than 7
  if (N <= 6) return N;

  // An array to store result of subproblems
  std::vector<int> screen(N+1, 0);

  // Initializing the optimal lengths array for uptil 6 input strokes.
  int n;
  for (n = 1; n <= 6; n++) screen[n] = n;

  // Solve all subproblems in bottom manner
  for (; n <= N; n++) {
    screen[n] = n;
    // For any keystroke n, we need to loop from n-3 keystrokes
    // back to 1 keystroke to find a breakpoint 'b' after which we
    // will have ctrl-a, ctrl-c and then only ctrl-v all the way.
	// O(n^2)
    for (int b = n- 3; b >= 1 ; b--) {
      // if the breakpoint is at b'th keystroke then
      // the optimal string would have length
      // (n-b-1)*screen[b-1];
      int curr = (n - b - 1) * screen[b];
      if (curr > screen[n]) screen[n] = curr;
    }

	// Optimization in the above logic-
	// Instead of always iterating from N-3 down to 1,
	// we should only consider 4 consecutive Ctrl-V keystrokes
	// to get the maximum number of A's.
	// 4*O(n)
	// ref - http://edusagar.com/questions/dynamic-programming/maximum-number-of-a-using-ctrl-a-ctrl-c-ctrl-v-keys-google-interview-question
	//for (int b = n - 3, k = 1; (b >= 1 && k <= 4); b--, k++) {
	//	// if the breakpoint is at b'th keystroke then
	//	// the optimal string would have length
	//	// (n-b-1)*screen[b-1];
	//	int curr = (n - b - 1) * screen[b];
	//	if (curr > screen[n]) screen[n] = curr;
	//}
  }

  return screen[N];
}

// Driver program
int main() {
  // for the rest of the array we will rely on the previous
  // entries to compute new ones
  for (int N = 1; N <= 20; N++)
    printf("Maximum Number of A's with %d keystrokes is %d\n", N,
           findoptimal(N));
  getchar();
}
