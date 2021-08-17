#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <iostream>
#include <string>

using namespace std;


string generate(const int);
string userDisplay(string &);
int matchString(string &, string &);

const int length = 5;


int main() {

	int totalPoint = 2000;
	int time;
	int offValue;
	int penalty;
	int excessTime;
	string randomString;
	string userRandomString;
	string userInput;


	while (totalPoint > 0 && totalPoint < 5000) {


		randomString = generate(length);
		userRandomString = userDisplay(randomString);


		cout << "Your current points " << totalPoint << " just type -> "
			 << userRandomString << ":";


		auto start = chrono::high_resolution_clock::now();

		getline(cin, userInput);

		auto end = chrono::high_resolution_clock::now();


		time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

		offValue = matchString(userInput, randomString);



		if (time <= 10000) {

			cout << time << " milliseconds,"

				 << " you made it within the interval of 10000..." << endl;


			if (offValue > 0) {

				cout << "String offset is, " << offValue

					 << " your total penalty is " << offValue << "..." << endl;

				totalPoint -= offValue;

			}

			else {

				totalPoint += 500;

			}


		}


		else {

			cout << time << " milliseconds,"

				 << " you *failed* it within the interval of 10000..." << endl;

			excessTime = time % 1000;

			if (offValue > 0) {

				penalty = excessTime + 2 * offValue;


				cout << "String offset is, " << offValue

					 << " your total penalty is " << penalty << "..." << endl;


				totalPoint -= penalty;

			}

			else {

				totalPoint += excessTime;

			}


		}


	}



	cout << "Bye..." << endl;

	return 0;

}



int matchString(string &input, string &randStr) {

	int offSet = 0;


	for (unsigned int i = 0; i < randStr.length(); i++) {


		if (int(input[i]) == 0) {

			input[i] = ' ';

		}

		else if (!isalnum(input[i]) && !isspace(input[i])) {

			input[i] = '*';

		}

		else if (isdigit(input[i])) {

			input[i] = '0';

		}


	}


	for (unsigned int i = 0; i < randStr.length(); i++) {

		offSet += abs((int)input[i] - (int)randStr[i]);

	}


	return offSet;


}

string generate(const int length) {

	srand(time(0));

	char alNumSymbols[] = "0123456789"
						  ",.?!@#$%^&"
						  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
						  "abcdefghijklmnopqrstuvwxyz";

	char randChar;
	string randString;


	for (int i = 0; i < length; i++) {

		randChar = alNumSymbols[rand() % (sizeof(alNumSymbols) - 1)];


		if (isdigit(randChar)) {

			randString += '0';

		}

		else if (!isalnum(randChar)) {

			randString += '*';

		}

		else {

			randString += randChar;

		}


	}


	return randString;


}

string userDisplay(string &randStr) {

	string userString;


	for (unsigned int i = 0; i < randStr.length(); i++) {

		if (isdigit(randStr[i])) {

			userString += "[0-9]";

		}

		else if (!isalnum(randStr[i])) {

			userString += "[%-!]";

		}

		else {

			userString += randStr[i];
		}

	}


	return userString;


}


