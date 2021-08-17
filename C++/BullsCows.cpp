
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

bool linearSearch(vector<int>, int, int, bool);

const int length = 4;

int main() {

	srand(time(NULL));
	vector<int> randomNumber;
	vector<int> userNumber;
	int number;
	int guess;
   	int digit;
	int newNum;
	int bulls;
	int cows;
	int time;
	int minutes;
	int seconds;
	int round = 0;
	bool repeat = false;

    //Randomly generate a 4-digit number
	for (int i = 0; i < length; i++) {
		do {
			number = rand() % 10;
			repeat = linearSearch(randomNumber, i, number, repeat);//checks for repeats
		} while (repeat);

		randomNumber.push_back(number);
	}

	auto start = chrono::high_resolution_clock::now();


    //isolate the individual digits.
	do {

		cout << "Enter a 4 digit digit(unique digits):";
		cin >> guess;

		for (int i = 0; i < length; i++) {

			digit = guess % 10;

			userNumber.insert(userNumber.begin(), digit);
			newNum = guess / 10;

			guess = newNum;


		}

		bulls = 0;
		cows = 0;

		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				if (userNumber[i] == randomNumber[j]) {
					if (i == j) {
						bulls++;
						break;

					}
					cows++;

				}

			}

		}

		cout << "bulls = " << bulls << " and cows = " << cows << endl;
		round++;

	} while (bulls < 4);


	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::seconds>(end - start).count();

	minutes = time / 60;
	seconds = time % 60;


	cout << "You guessed it in " << round << " tries, taking " << minutes

		 << " minutes and " << seconds << " seconds " << endl;


}


bool linearSearch(vector<int> randomNumber, int i, int number, bool repeat) {

	repeat = false;

	for (int j = 0; j < i; j++) {

		if (number == randomNumber[j]) {

			repeat = true;

			break;

		}
	}
	return repeat;
}
