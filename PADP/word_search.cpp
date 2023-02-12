#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<omp.h>

#define SIZE 7

using namespace std;

string fileName = "words.txt";
string words[SIZE] = {"lorem", "ipsum", "dolo", "sit", "amet", "hi", "good"};
int counts[SIZE] = { 0 };

void lower(string &str) {
	for(int i = 0; i < str.size(); i++)
		str[i] = tolower(str[i]);
}

int getCount(string f, string key) {
	lower(key);
	int count = 0;

	ifstream file(f);
	string word;
	while(file >> word) {
		lower(word);
		if(key == word) count++;
	}
	return count;
}

int main() {
	double t = omp_get_wtime();

	#pragma omp parallel for num_threads(1)
	for(int i = 0; i < SIZE; i++) {
		counts[i] = getCount(fileName, words[i]);
	}

	t = omp_get_wtime() - t;
	cout << "TIME = " << t << endl;

	for(int i = 0; i < SIZE; i++) {
		cout << words[i] << " " << counts[i] << endl;
	}
}
