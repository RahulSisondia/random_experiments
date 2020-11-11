// Find_char_frequency.cpp : Defines the entry point for the console
// application.
// https://aonecode.com/aplusplus/interviewctrl/getInterview/9113858397382350847
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

int main() {

	unordered_map<char, int> freq;
	int max_freq = 0;
	std::string str("geeksforgeeks");
	for (int i = 0; i < str.size(); i++) {
		freq[str[i]]++;
		if (freq[str[i]] > max_freq)
			max_freq = freq[str[i]];
	}

	vector<list<char>>l(max_freq+1);

	for (auto map_itr : freq) {
		l[map_itr.second].emplace_back(map_itr.first);
	}

	for (int i = max_freq; i> 0; i--) {
		for (char c : l[i]) {
			cout << c << " : " << i<<"\n";
		}
	}

	// your code goes here
	return 0;
}