#include <iostream>
using namespace std;

int main()
{
	int  transactions[5][4] = { 0 };

	for (int day = 1; day <= 30; day++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 4; j++) {
				transactions[i][j] += rand() % 100;
			}
		}
	}
	cout << "Pro.\\SP\t|";
	for (int i = 1; i <= 4; i++) {
		cout << i<<"_____\t";
	}
	cout << "Total\n";
	int totalS[4] = { 0 };
	int totalP;
	for (int i = 0; i < 5; i++) {
		totalP = 0;
		cout << i+1<<"\t|";
		for (int j = 0; j < 4; j++) {
			totalP += transactions[i][j];
			totalS[j] += transactions[i][j];
			cout << transactions[i][j]<<"\t";
		}
		cout <<totalP<<"\n";
	}
	cout << "Total\t|";
	totalP = 0;
	for (int i = 0; i < 4; i++) {
		cout << totalS[i] << "\t";
		totalP += totalS[i];
	}
	cout << totalP;
}
