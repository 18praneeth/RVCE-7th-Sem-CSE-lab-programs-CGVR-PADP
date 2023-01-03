#include<iostream>
#include<fstream>
#include<cstring>
#include<omp.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

int strcmpi(string a,string b){
	
	int len_a=a.length(),len_b= b.length();

	if(len_a!=len_b)
		return -1;
		
	for(int i=0;i<len_a;i++){
		if(tolower(a[i])!=tolower(b[i]))
			return -1;
	}
 	return 0;
}

int main(){
	string filename = "words.txt";
	string word[7] = {"lorem", "ipsum", "dolor", "sit","amet","hi","good"};


	for(int j=1;j<=8;j*=2){
		double st=omp_get_wtime();
		#pragma omp parallel for shared(word) num_threads(j) 
		for(int k=0;k<7;k++){
			int count = 0;
			fstream file;
			string word1;
			file.open(filename);
			while (file >> word1)
			{
				if(strcmpi(word[k],word1)==0)
					count++;
			}
			cout << count << " " << word[k] <<endl;
		}
	cout <<"Time "<<omp_get_wtime()-st<<endl;
	}
	
}