#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<omp.h>

#define SIZE 5

using namespace std;

string fileName = "words.txt";
string words[SIZE] = {"lorem", "ipsum", "dolo", "sit", "amet"};
int counts[SIZE] = { 0 };

int getCount(ifstream& file, string key, bool ignorecase) {
	if(ignorecase)
		transform(key.begin(), key.end(), key.begin(), ::tolower);

	file.clear();
	file.seekg(0, ios::beg);
	string word;

	int count = 0;
	while(file >> word) {
		if(ignorecase)
			transform(word.begin(), word.end(), word.begin(), ::tolower);
		if(key == word)
			count++;
	}
	return count;
}

int main() {
	double t = omp_get_wtime();

	ifstream file(fileName);
	#pragma omp parallel for num_threads(1)
	for(int i = 0; i < SIZE; i++) {
		counts[i] = getCount(file, words[i], true);
	}

	t = omp_get_wtime() - t;
	cout << "TIME = " << t << endl;

	for(int i = 0; i < SIZE; i++) {
		cout << words[i] << " " << counts[i] << endl;
	}
}