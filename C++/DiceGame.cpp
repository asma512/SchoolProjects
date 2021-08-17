//============================================================================
// Name        : ASadiaNAO.cpp
// Author      : Asma Sadia
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int humanPlayer(int);
int computerPlayer(int,int);
int dicesRolled();
int numOnesRolled(int,int,int);
int compChoice(int,int,int);


int main() {

	srand(time(0));
    int humanTotalPoint = 0, computerTotalPoint = 0;
	int round=1;

    while(humanTotalPoint < 150 && computerTotalPoint < 150){

        humanTotalPoint = humanPlayer(humanTotalPoint);
        computerTotalPoint = computerPlayer(computerTotalPoint,humanTotalPoint);


        cout << "After round " << round << " human has " << humanTotalPoint << " and computer has "<< computerTotalPoint <<endl;
        cout <<""<<endl;
        cout <<""<<endl;

        round++;
	}


	if(humanTotalPoint == computerTotalPoint){

		cout << "Tie" <<endl;

	}
	else if(humanTotalPoint > computerTotalPoint)
	{

		cout << "Human won" <<endl;

	}
	else
    {
	    cout << "Computer won"<<endl;

	}
}

int dicesRolled(){
	return (rand() % 6) + 1;
}

int numOnesRolled(int dice_1,int dice_2, int dice_3){

    int num_Ones=0;

    if(dice_1== 1){
        num_Ones++;
    }
    if(dice_2 ==1)
    {
        num_Ones++;
    }
    if(dice_3 ==1){
        num_Ones++;
    }
    
    return num_Ones;

}

int humanPlayer(int humanTotalPoint){

    int dice_1,dice_2,dice_3;
	int onesRolled;
	int turnScore;
	char input;


	do{

		dice_1= dicesRolled();
		dice_2= dicesRolled();
		dice_3= dicesRolled();

		cout<<"Rolled " << dice_1 <<" "<< dice_2 << " "<< dice_3<<endl;
		onesRolled=numOnesRolled(dice_1,dice_2,dice_3);

        switch(onesRolled){


            case 1:

                cout<<"Single one, lose turn"<<endl;
                cout<<""<<endl;

                return humanTotalPoint;

            case 2:

                cout<<"Two ones, lose half of holdings, and lose turn"<<endl;
                cout<<""<<endl;

                humanTotalPoint=humanTotalPoint/2;
                return humanTotalPoint;

            case 3:

                cout<<"Three ones, lose all holdings, and lose turn"<<endl;
                cout<<""<<endl;

                return 0;

            default:

                turnScore=dice_1+dice_2+dice_3;

                cout<<"sum = " << turnScore <<endl;
                break;

        }

        do{

            cout<<"Bank(y/n)?";
            cin>> input;

        }while(input != 'y' && input!='n');

        if(input== 'y'){

            humanTotalPoint+=turnScore;
            return humanTotalPoint;
        }


	}while( input == 'n');

	return 0;

}

int computerPlayer(int computerTotalPoint,int humanTotalPoint){

	int dice_1,dice_2,dice_3;
	int onesRolled;
	int turnScore;
	int computerChoice;

    cout<<"Computer's turn"<<endl;

    do{

		dice_1=dicesRolled();
		dice_2=dicesRolled();
		dice_3=dicesRolled();

		cout<<"Rolled " << dice_1 <<" "<< dice_2 << " "<< dice_3<<endl;

		onesRolled=numOnesRolled(dice_1,dice_2,dice_3);

	switch(onesRolled){

	    case 1:

	    	cout<<"Single one, lose turn"<<endl;
	    	cout<<""<<endl;

	    	return computerTotalPoint;

	    case 2:

	    	cout<<"Two ones, lose half of holdings, and lose turn"<<endl;
	    	cout<<""<<endl;

	    	computerTotalPoint=computerTotalPoint/2;
	    	return computerTotalPoint;

        case 3:

	    	cout<<"Three ones, lose all holdings, and lose turn"<<endl;
	    	cout<<""<<endl;

	    	return 0;

        default:

        	turnScore=dice_1+dice_2+dice_3;

        	computerChoice=compChoice(computerTotalPoint,humanTotalPoint,turnScore);

        	if(computerChoice==1){

                cout<<"sum = " << turnScore << " bank " <<endl;

                computerTotalPoint += turnScore;
        	    return computerTotalPoint;
        	}
        	else{

        	    cout<<"sum = " << turnScore << " no bank " <<endl;
        	}
        	break;

	    }
    }while(computerChoice == 0);

	return 0;
}


int compChoice(int computerTotalPoint,int humanTotalPoint, int turnScore){

    int gap=humanTotalPoint-computerTotalPoint;

    if((humanTotalPoint>computerTotalPoint && gap>18) && turnScore <=9){

			return 0; //no bank
	}
	else{

			return 1; //bank
	}

 }