// build_lowest_number_by_removing_k_digits.cpp : This file contains the 'main' function. Program execution begins and ends there.
// https://www.geeksforgeeks.org/build-lowest-number-by-removing-n-digits-from-a-given-number/
//

#include <iostream>
#include <deque>

using namespace std;

void insertInNonDecOrder(deque<char>& dq, char ch)
{
	// if container is empty , insert the current digit 
	if (dq.empty())
		dq.push_back(ch);

	else
	{
		char temp = dq.back();

		// Keep removing digits larger than current digit 
		// from the back side of deque 
		while (temp > ch && !dq.empty())
		{
			dq.pop_back();
			if (!dq.empty())
				temp = dq.back();
		}
		dq.push_back(ch); // insert the current digit 
	}
	return;
}

string buildLowestNumber(string str, int n)
{
	int len = str.length();

	// deleting n digits means we need to print k digits 
	int k = len - n;

	deque<char> dq;
	string res = "";

	// leaving rightmost k-1 digits we need to choose 
	// minimum digit from rest of the string and print it 
	int i;
	for (i = 0; i <= len - k; i++)

		// insert new digit from the back side in 
		// appropriate position and/ keep removing 
		// digits larger than current digit 
		insertInNonDecOrder(dq, str[i]);

	// Now the minimum digit is at front of deque 
	while (i < len)
	{
		// keep the minimum digit in output string 
		res += dq.front();

		// remove minimum digit 
		dq.pop_front();

		// Again insert new digit from the back 
		// side in appropriate position and keep 
		// removing digits larger than current digit 
		insertInNonDecOrder(dq, str[i]);
		i++;
	}

	// Now only one element will be there in the deque 
	res += dq.front();
	dq.pop_front();
	return res;
}

// Driver program to test above function 
int main()
{
	//string str = "765028321";
	string str = "1432219";
	int n = 3;
	cout << buildLowestNumber(str, n) << endl;
	return 0;
}