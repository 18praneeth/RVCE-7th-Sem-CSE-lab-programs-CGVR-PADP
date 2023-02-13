#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <omp.h>

#define SIZE 5
#define FILE "words.txt"

using namespace std;

string words[SIZE] = {"lorem", "ipsum", "dolo", "sit", "amet"};
int counts[SIZE] = {};

void lower(string &str) {
	for (int i = 0; i < str.size(); i++)
		str[i] = tolower(str[i]);
}

int getCount(string fileName, string key) {
	lower(key);
	ifstream file(fileName);
	string word;
	int count = 0;
	while (file >> word) {
		lower(word);
		if(key == word) count++;
	}
	return count;
}

int main() {
	double t = omp_get_wtime();

	#pragma omp parallel for // num_threads(1/2/4/8)
	for (int i = 0; i < SIZE; i++) {
		counts[i] = getCount(FILE, words[i]);
	}

	t = omp_get_wtime() - t;
	cout << "Time: " << t << endl;

	for (int i = 0; i < SIZE; i++) {
		cout << words[i] << " " << counts[i] << endl;
	}
}
