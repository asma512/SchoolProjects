#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> splitInput(vector<string>,string,string,int);
void printAnimals(vector<string>);
int randNum();
vector<string> wordsPicked(vector<string>,vector<string>,int,int,int);
int repeatWords(vector<string>,vector<string>,int,int,int);
vector<string> splitGuess(vector<string>,string,string,int);
int wordsMatch(vector<string>,vector<string>, int);
string scrambleWords(vector<string>,string);
void printsMatch(int);
int checkConsecutive(vector<int>,int);
string hideLetters(string ,int ,int ,int ,vector<int>);
int repeatChar(vector<int>,int,int);


int main() {

	srand(time(0));
	vector<string> animals,chosenWords,answers;
	vector<int> consecutiveNum,listIndex;
	string input,word,jumbleWord,guess;
	int index=0,repeat=0,numAnimal=0,match=0,checkNum=-1,sameIndex=0,strikes=1,wordLen=0,shortWord=0;


	cout<<"Enter at least five animal names, e.g., cat, dog, etc..."<<endl;
	getline(cin,input);

	animals=splitInput(animals,input,word,index);
	printAnimals(animals);


do{
	numAnimal= randNum();

    chosenWords=wordsPicked(chosenWords,animals,numAnimal,index,repeat);
    jumbleWord=scrambleWords(chosenWords,jumbleWord);

    random_shuffle(jumbleWord.begin(),jumbleWord.end());

    cout<< "What are the "<< numAnimal<<" animals in "<< "\"" <<jumbleWord <<"\" "<< "? ";


    getline(cin,guess);

    if(guess=="Quit"|| guess=="quit"){
    		  return 0;
    }
    if(guess=="?"){

    	        printAnimals(animals);
    	        cout<<"Enter again : ";
    	        getline(cin,guess);
    	        answers=splitGuess(answers,guess,word,index);
    	        match=wordsMatch(chosenWords,answers,match);
    	        consecutiveNum.push_back(match);
    	        printsMatch(match);
    }

    else{

    		answers=splitGuess(answers,guess,word,index);

    	    if(answers.size()!=chosenWords.size()){

						cout<<"Your number of input is incorrect. Enter again: ";
						getline(cin,guess);
						answers.clear();
						answers=splitGuess(answers,guess,word,index);
						match=wordsMatch(chosenWords,answers,match);
						consecutiveNum.push_back(match);
						printsMatch(match);

    	    }
    	    else{

						match=wordsMatch(chosenWords,answers,match);
						consecutiveNum.push_back(match);
						printsMatch(match);

    	    }

    }

    checkNum=checkConsecutive(consecutiveNum,checkNum);

    answers.clear();
   	chosenWords.clear();
   	jumbleWord="";


}while(checkNum<1);

consecutiveNum.clear();
cout<<"Succeeded two consecutive times, challenge goes up!"<<endl;


do{

    numAnimal= randNum();
	chosenWords=wordsPicked(chosenWords,animals,numAnimal,index,repeat);
    jumbleWord=scrambleWords(chosenWords,jumbleWord);
    wordLen=jumbleWord.length();

    if(strikes>wordLen){

				shortWord=wordLen;
				jumbleWord=hideLetters(jumbleWord,index,shortWord,sameIndex,listIndex);
    }
    else{

    	for(int i=0;i<strikes;i++){

    		do{

					index=rand()% jumbleWord.length();
					sameIndex=repeatChar(listIndex,index,sameIndex);
					listIndex.push_back(index);


    		}while(sameIndex==1);


			   	   jumbleWord[index]='_';

		}

    }


    random_shuffle(jumbleWord.begin(),jumbleWord.end());

    cout<< "What are the "<< numAnimal<<" animals in "<< "\"" <<jumbleWord <<"\" "<< "? ";
    getline(cin,guess);

       if(guess=="Quit"|| guess=="quit"){

              	  return 0;

       }
       if(guess=="?"){

				  printAnimals(animals);
				  cout<<"Enter again : ";
				  getline(cin,guess);
				  answers=splitGuess(answers,guess,word,index);
				  match=wordsMatch(chosenWords,answers,match);
				  consecutiveNum.push_back(match);
				  printsMatch(match);
       }
       else{

       		answers=splitGuess(answers,guess,word,index);

       	    if(answers.size()!=chosenWords.size()){

					cout<<"Your number of input is incorrect. Enter again: ";
					getline(cin,guess);
					answers.clear();
					answers=splitGuess(answers,guess,word,index);
					match=wordsMatch(chosenWords,answers,match);
					consecutiveNum.push_back(match);
					printsMatch(match);

       	    }
       	    else{

					match=wordsMatch(chosenWords,answers,match);
					consecutiveNum.push_back(match);
					printsMatch(match);
       	    }
       }



              checkNum=checkConsecutive(consecutiveNum,checkNum);
              if(checkNum==1){

            	  cout<<"Succeeded two consecutive times, challenge goes up!"<<endl;
            	  ++strikes;
            	  consecutiveNum.clear();

              }
              if(checkNum==0){

            	  cout<<"Missed two consecutive times, challenge goes down!"<<endl;
            	  --strikes;
            	  consecutiveNum.clear();

              }
              if(strikes==0){
            	  return 0;
              }


              answers.clear();
      	      chosenWords.clear();
      	      listIndex.clear();
      	      jumbleWord="";


	}while(guess!="Quit"|| guess!="quit");

}




vector<string> splitInput(vector<string>animals,string input ,string word,int index){
	index=0;

	 while (input.compare(word) != 0)

		     {

					index = input.find(" ");

					word = input.substr(0,index);

					if (!word.empty()){

						animals.push_back(word);
		            }

		        input = input.substr(index+1, input.length());

		    }

return animals;

}


void printAnimals(vector<string>animals){

	for (unsigned int i=0;i <animals.size();i++){

			 cout<< i<< ":" <<animals[i] <<endl;

	}

}


int randNum(){

	return (rand() % 3) + 1;

}


vector<string> wordsPicked(vector<string> chosenWords,vector<string> animal,int numAnimal,int index,int repeat){

    index=0,repeat=0;

	for(int i=0;i<numAnimal;i++){

		  do{

		        index=rand()% animal.size();

		        repeat=repeatWords(chosenWords,animal,i,index,repeat);

		    	}while(repeat==1);

		    	chosenWords.push_back(animal[index]);

		    }

return chosenWords;

}


int repeatWords(vector<string> chosenWords, vector<string> animal, int i, int index, int repeat){

    repeat=0;

	for(int j=0; j<i;j++){

		if(animal[index]==chosenWords[j]){

			repeat=1;
			break;

		}

	}

return repeat;

}


vector<string> splitGuess(vector<string> answers,string guess,string word, int index){

	index=0;

	while (guess.compare(word) != 0)

	       {

	           index = guess.find(" ");

	           word = guess.substr(0,index);

	           if (!word.empty()){

    	        	answers.push_back(word);

    	        }

	           guess = guess.substr(index+1, guess.length());

	       }

return answers;

}


int wordsMatch(vector<string>chosenWords,vector<string>answers,int match){

	match=0;

	  sort(chosenWords.begin(), chosenWords.end());
	  sort(answers.begin(), answers.end());
	  if(chosenWords== answers){

		  match=1;

	  }
	  else{

		  match=0;

	  }

return match;

}


string scrambleWords(vector<string> chosenWords,string jumbleWord){

	for(unsigned int i=0; i<chosenWords.size(); i++){

						jumbleWord+=chosenWords[i];

	}

return jumbleWord;

}


int checkConsecutive(vector<int>consecutiveNum,int checkNum){


	    if (consecutiveNum[consecutiveNum.size() - 1]== 1 && consecutiveNum[consecutiveNum.size() - 2] == 1) {

			checkNum = 1;

		} else if (consecutiveNum[consecutiveNum.size() - 1] == 0 && consecutiveNum[consecutiveNum.size() - 2] == 0) {

			checkNum = 0;

		} else {

			checkNum = -1;

		}

return checkNum;

}


void printsMatch(int match){

	if(match==1){
		cout<<"Yes!"<<endl;

	}
	else{

		cout<<"Nope!"<<endl;
	}

}


string hideLetters(string jumbleWord,int index,int shortWord,int sameIndex,vector<int> listIndex){

	index=0;sameIndex=0;

      for(int i=0;i<shortWord;i++){

			do{

					index=rand()% jumbleWord.length();

					sameIndex=repeatChar(listIndex,index,sameIndex);

					listIndex.push_back(index);


			}while(sameIndex==1);


		   jumbleWord[index]='_';

      }

return jumbleWord;

}

int repeatChar(vector<int> listIndex,int index,int sameIndex){

	sameIndex=0;

	for(unsigned int j=0;j<listIndex.size();j++){

		if (listIndex[j]==index){

			sameIndex=1;

		}

	}

return sameIndex;

}


