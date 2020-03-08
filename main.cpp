/*      HW 5
		Alina Kuralova-171044094

		the way I'm testing all functions is one by one.
		I sent some values or char moves to my functions, as an example and showed the results by calling print() function.
		My Global function takes an array of AbstractBoard pointers with defined size 3
		I initialized my example objects to that array and tested is given set of arrays is valid ot not.
		
*/

#include <iostream>
#include <vector>
#include <cstring>
#define SIZE 3			//Defined value used for array of AbstractBoard pointers size

#include "AbstractBoard.h"
#include "BoardVector.h"
#include "BoardArray2D.h"
#include "BoardArray1D.h"

using namespace std;
using namespace NPuzzleSavitch;

//PROTOTYPES
void testVector(int argc, char const *argv[]);
void test2D(int argc, char const *argv[]);
void test1D(int argc, char const *argv[]);

//IMPLEMENTATION OF MY GLOBAL FUNCTION
//In this function ArrayGlobal[n]-means array I have at the moment and ArrayGlobal[i]-means next array, with which I'm making all comparisons

bool IsValidGlobal(AbstractBoard* ArrayGlobal[], int size){
	int i, n=0;
	bool finish=true;
	cout<<"\t\tWELCOME TO GLOBAL FUNCTION"<<endl<<endl;
	for(i=0; i<size; i++){
		ArrayGlobal[i]->print();
			cout<<endl;
	}

	for(i=1; i<size; i++){
		if(*ArrayGlobal[n] == *ArrayGlobal[i]){	//Using my == operator for checking equality ob boards	
			cout<<"GLOBAL functions result is FALSE, because empty space did not make any move:( "<<endl;
			return false;	//Since empty cell did not make a move	
		}
		if( (ArrayGlobal[n]->getHeight() != ArrayGlobal[i]->getHeight()) || (ArrayGlobal[n]->getWidth() !=  ArrayGlobal[i]->getWidth() )){
			cout<<"GLOBAL functions result is FALSE, because boards did not match in size :( "<<endl;
			return false;	//Since, boards are not equal in size at all
		
		}
		//for 1st column checks maded
		if((ArrayGlobal[n]->getColEmptyCell() == 0) && (ArrayGlobal[i]->lastMove() == 'L')){
			cout<<"GLOBAL functions result is FALSE, Unvalid move was maded :( "<<endl;
			return false;
		}
		//For corner checks
		if((ArrayGlobal[n]->getColEmptyCell() == 0) && (ArrayGlobal[n]->getRowEmptyCell() == 0)){
			if(ArrayGlobal[i]->lastMove() == 'U' || ArrayGlobal[i]->lastMove() == 'L'){
				cout<<"GLOBAL functions result is FALSE, Unvalid move was maded :( "<<endl;
				return false;
			}
		}
		if((ArrayGlobal[n]->getColEmptyCell() == 0) && (ArrayGlobal[n]->getRowEmptyCell() == ArrayGlobal[n]->getHeight()-1)){
			if(ArrayGlobal[i]->lastMove() == 'D' || ArrayGlobal[i]->lastMove() == 'L'){
				cout<<"GLOBAL functions result is FALSE, Unvalid move was maded :( "<<endl;
				return false;
			}
		}
		//For last column (all checks)
		if((ArrayGlobal[n]->getColEmptyCell() == ArrayGlobal[n]->getWidth()-1) && (ArrayGlobal[i]->lastMove() == 'R')){
			cout<<"GLOBAL functions result is FALSE, Unvalid move was maded :( "<<endl;
			return false;
		}
		//For corner checks
		if((ArrayGlobal[n]->getColEmptyCell() == ArrayGlobal[n]->getWidth()-1) && (ArrayGlobal[n]->getRowEmptyCell() == 0)){
			if(ArrayGlobal[i]->lastMove() == 'U' || ArrayGlobal[i]->lastMove() == 'R'){
				cout<<"GLOBAL functions result is FALSE, Unvalid move was maded :( "<<endl;
				return false;
			}
		}
		if((ArrayGlobal[n]->getColEmptyCell() == ArrayGlobal[n]->getWidth()-1) && (ArrayGlobal[n]->getRowEmptyCell() == ArrayGlobal[n]->getHeight()-1)){
			if(ArrayGlobal[i]->lastMove() == 'D' || ArrayGlobal[i]->lastMove() == 'R'){
				cout<<"GLOBAL functions result is FALSE, Unvalid move was maded :( "<<endl;
				return false;
			}
		}
		//For Up checks
		if((ArrayGlobal[n]->getRowEmptyCell() == 0) && (ArrayGlobal[i]->lastMove() == 'U')){
			cout<<"GLOBAL functions result is FALSE, Unvalid move was maded :( "<<endl;
			return false;
		}
		//For Down Checks
		if((ArrayGlobal[n]->getRowEmptyCell() == ArrayGlobal[n]->getHeight()-1) && (ArrayGlobal[i]->lastMove() == 'D')){
			cout<<"GLOBAL functions result is FALSE, Unvalid move was maded :( "<<endl;
			return false;
		}	
		n++;
		if(i==size-1){
			finish = ArrayGlobal[i]->isSolved();
			if(finish == false){
				cout<<"LAST Board did not reach to the Solution! Returning FALSE from Global function."<<endl;
			}
		}
	}
	return finish;
}



/*
	I implemented 3 test functions:
	---> For BoardVector
	---> For BoardArray1D
	---> For BoardArray2D

	And I opened test only for test1D() function in order to reduce printed stuff to the console. 
	We can check others by opening the commented 2 lines below:
*/

int main(int argc, char const *argv[])
{

	//testVector(argc,argv);
	//test2D(argc, argv);
	  test1D(argc, argv);

	return 0;
}

/*
	In order to test my Global Function, I created 3 objects of different derived class types
	And sended these objects to my global function, to check whether it works fine or not.
	ALL FUNCTIONS were tested only according to the BOARD 1 of the first1D object, in order to reduce printed stuff in the console.
	I writed below for which object I tested the function and I tried to provide comments too. Thank you.
*/

void test1D(int argc, char const *argv[]){
	BoardArray2D first1D; 		//Object of Board1D derived class - (BOARD 1)
	BoardVector second1D;		//Object of BOardVector derived class - (BOARD 2)
	BoardArray1D third1D;		//Object of Board2D derived class  - (BOARD 3)
	AbstractBoard* ArrayGlobal[SIZE]={&first1D, &second1D, &third1D};		//I gave DEFIINEd SIZE for my Array of AbstractBoard pointers, and initialize this array with my created objects for testing
	bool check;					//Keeps bool value returned by my global function
	bool flag1;					//Keeps bool value, whether file was opened succsessfully or not.
	bool flag2;
	bool flag3;
	bool isSolvedOrNot;			//Keeps value for isSolved function
	int valueFromOper1;			//For testing my operator() overloaded function

	if(argc==2){
		cout<<"BOARD 1 READED: "<<endl;
		flag1 = first1D.readFromFile(argv[1]);
		first1D.print();

		flag2 = second1D.readFromFile("example.txt");

		flag3 = third1D.readFromFile("example.txt");

		cout<<"BOARD WRITED: (tested ONLY on BOARD 1)"<<endl;
									//Testing writeToFile() function, with the board of the first object, just for testing I choosed first object(in random way)
		if(flag1==true){			//IF file was opened succsessfully, write file of the First2D object.
			first1D.writeToFile("writed.txt");
			first1D.print();
		}
		else
			cout<<"There's nothing to write to the file, because file was not opened."<<endl;
		

		if(flag1 == true && flag2 == true && flag3 == true){	//If files, of all objects were opened succsessfully:
	
			first1D.reset();			//Testing RESET() function
			cout<<"After reset() function BOARD 1 look like: "<<endl;
			first1D.print();
			//second1D.reset();						
										//Testing MOVE() function
			cout<<"After moves applied to BOARD 1. ('U','R','L') BOARD 1 look like: "<<endl;
			first1D.move('U');
			first1D.move('R');
			first1D.move('L');

			first1D.print();
			
									//Testing numOFMoves() function
			cout<<"TOTAL NUMBER OF MOVES MADED on BOARD 1 --> "<< first1D.numOfMoves()<<endl;

									//Testing lastMove() function
			cout<<"LAST STEP MADED on BOARD 1 --> "<<first1D.lastMove()<<endl;

									//Testing isSolved() function
			isSolvedOrNot = first1D.isSolved();
			cout<<"Testing isSolved() function for BOARD 1  "<<endl;
			if(isSolvedOrNot == true)
				cout<<"Your Board is Solved! Congrats!  "<<endl;
			else if(isSolvedOrNot == false)
				cout<<"Your Board is NOT solved yet.   "<<endl;

									//Testing operator() function
			valueFromOper1 = first1D(first1D.getHeight()-1,first1D.getWidth()-1);
			cout<<"I gave last cell's location  for testing, so values returned by Function call operator () are: "<<endl;
			cout<<"For the BOARD 1 ---> "<<valueFromOper1<<endl;

 									//Testing operator == overloaded function
			cout<<"Testing operator ==(). BEFORE COMPARING two boards look like (BOARD 1 and BOARD 2)"<<endl<<endl;
			cout<<"\t Board 1  "<<endl;
			first1D.print();
			cout<<"\t Board 2 "<<endl;
			second1D.print();

			if(second1D == first1D){
				cout<<"TRUE Boards are EQUAL !!!"<<endl;
			}
			else{
				cout<<"FALSE Boards are NOT EQUAL !!!"<<endl;
			}
									//Testing NumberOfBoards() function
			cout<<"Testing NumberOfBoards() function. Number of total created BOARD OBJECTS -> "<<first1D.NumberOfBoards()<<endl;

									//Finally
									//Testing GLOBAL function implemented.

			check = IsValidGlobal(ArrayGlobal, SIZE);
			if(check == true)
				cout<<"GLOBAL function returned TRUE, board reached solution. Congrats!"<<endl;
			else
				cout<<"GLOBAL function returned FALSE. "<<endl;
		} 
	}

	else{
		cout<<"Please, provide name of the file."<<endl;
	}

}

void testVector(int argc, char const *argv[]){
	BoardVector vect1; 
	BoardVector vect2;		//Second object created for testing my ==operator etc.
	BoardVector vect3;
	AbstractBoard* ArrayGlobal[SIZE]={&vect1, &vect2, &vect3};		//I gave DEFIINEd SIZE for my Array of AbstractBoard pointers, and initialize this array with my created objects for testing
	bool check;				//Keeps bool value returned by my global function
	bool flag1;				//Keeps bool value, whether file was opened succsessfully or not.
	bool flag2;
	bool flag3;
	bool isSolvedOrNot;		//Keeps value for isSolved function
	int valueFromOper1;		//For testing my operator() overloaded function


	if(argc==2){
		cout<<"BOARD 1 READED: "<<endl;
		flag1 = vect1.readFromFile(argv[1]);
		vect1.print();

		flag2 = vect2.readFromFile("example.txt");

		flag3 = vect3.readFromFile("example.txt");

		cout<<"BOARD WRITED: (tested ONLY on BOARD 1)"<<endl;
									//Testing writeToFile() function, with the board of the first object, just for testing I choosed first object(in random way)
		if(flag1==true){			//IF file was opened succsessfully, write file of the First2D object.
			vect1.writeToFile("writed.txt");
			vect1.print();
		}
		else
			cout<<"There's nothing to write to the file, because file was not opened."<<endl;
		

		if(flag1 == true && flag2 == true && flag3 == true){	//If files, of all objects were opened succsessfully:
	
			vect1.reset();			//Testing RESET() function
			cout<<"After reset() function BOARD 1 look like: "<<endl;
			vect1.print();
			//vect2.reset();						
										//Testing MOVE() function
			cout<<"After moves applied to BOARD 1. ('U','R','L') BOARD 1 look like: "<<endl;
			vect1.move('U');
			vect1.move('R');
			vect1.move('L');

			vect1.print();
			
									//Testing numOFMoves() function
			cout<<"TOTAL NUMBER OF MOVES MADED on BOARD 1 --> "<< vect1.numOfMoves()<<endl;

									//Testing lastMove() function
			cout<<"LAST STEP MADED on BOARD 1 --> "<<vect1.lastMove()<<endl;

									//Testing isSolved() function
			isSolvedOrNot = vect1.isSolved();
			cout<<"Testing isSolved() function for BOARD 1  "<<endl;
			if(isSolvedOrNot == true)
				cout<<"Your Board is Solved! Congrats!  "<<endl;
			else if(isSolvedOrNot == false)
				cout<<"Your Board is NOT solved yet.   "<<endl;

									//Testing operator() function
			valueFromOper1 = vect1(vect1.getHeight()-1,vect1.getWidth()-1);
			cout<<"I gave last cell's location  for testing, so values returned by Function call operator () are: "<<endl;
			cout<<"For the BOARD 1 ---> "<<valueFromOper1<<endl;

 									//Testing operator == overloaded function
			cout<<"Testing operator ==(). BEFORE COMPARING two boards look like (BOARD 1 and BOARD 2)"<<endl<<endl;
			cout<<"\t Board 1  "<<endl;
			vect1.print();
			cout<<"\t Board 2 "<<endl;
			vect2.print();

			if(vect2 == vect1){
				cout<<"TRUE Boards are EQUAL !!!"<<endl;
			}
			else{
				cout<<"FALSE Boards are NOT EQUAL !!!"<<endl;
			}
									//Testing NumberOfBoards() function
			cout<<"Testing NumberOfBoards() function. Number of total created BOARD OBJECTS -> "<<vect1.NumberOfBoards()<<endl;

									//Finally
									//Testing GLOBAL function implemented.

			check = IsValidGlobal(ArrayGlobal, SIZE);
			if(check == true)
				cout<<"GLOBAL function returned TRUE, board reached solution. Congrats!"<<endl;
			else
				cout<<"GLOBAL function returned FALSE. "<<endl;
		} 
	}

	else{
		cout<<"Please, provide name of the file."<<endl;
	}
}

void test2D(int argc, char const *argv[]){
	BoardArray2D first2D; 		
	BoardArray2D second2D;		
	BoardArray2D third2D;
	AbstractBoard* ArrayGlobal[SIZE]={&first2D, &second2D, &third2D};		//I gave DEFIINEd SIZE for my Array of AbstractBoard pointers, and initialize this array with my created objects for testing
	bool check;				//Keeps bool value returned by my global function
	bool flag1;				//Keeps bool value, whether file was opened succsessfully or not.
	bool flag2;
	bool flag3;
	bool isSolvedOrNot;		//Keeps value for isSolved function
	int valueFromOper1;		//For testing my operator() overloaded function

	if(argc==2){
		cout<<"BOARD 1 READED: "<<endl;
		flag1 = first2D.readFromFile(argv[1]);
		first2D.print();

		flag2 = second2D.readFromFile("example.txt");

		flag3 = third2D.readFromFile("example.txt");

		cout<<"BOARD WRITED: (tested ONLY on BOARD 1)"<<endl;
									//Testing writeToFile() function, with the board of the first object, just for testing I choosed first object(in random way)
		if(flag1==true){			//IF file was opened succsessfully, write file of the First2D object.
			first2D.writeToFile("writed.txt");
			first2D.print();
		}
		else
			cout<<"There's nothing to write to the file, because file was not opened."<<endl;
		

		if(flag1 == true && flag2 == true && flag3 == true){	//If files, of all objects were opened succsessfully:
	
			first2D.reset();			//Testing RESET() function
			cout<<"After reset() function BOARD 1 look like: "<<endl;
			first2D.print();
			//second2D.reset();						
										//Testing MOVE() function
			cout<<"After moves applied to BOARD 1. ('U','R','L') BOARD 1 look like: "<<endl;
			first2D.move('U');
			first2D.move('R');
			first2D.move('L');

			first2D.print();
			
									//Testing numOFMoves() function
			cout<<"TOTAL NUMBER OF MOVES MADED on BOARD 1 --> "<< first2D.numOfMoves()<<endl;

									//Testing lastMove() function
			cout<<"LAST STEP MADED on BOARD 1 --> "<<first2D.lastMove()<<endl;

									//Testing isSolved() function
			isSolvedOrNot = first2D.isSolved();
			cout<<"Testing isSolved() function for BOARD 1  "<<endl;
			if(isSolvedOrNot == true)
				cout<<"Your Board is Solved! Congrats!  "<<endl;
			else if(isSolvedOrNot == false)
				cout<<"Your Board is NOT solved yet.   "<<endl;

									//Testing operator() function
			valueFromOper1 = first2D(first2D.getHeight()-1,first2D.getWidth()-1);
			cout<<"I gave last cell's location  for testing, so values returned by Function call operator () are: "<<endl;
			cout<<"For the BOARD 1 ---> "<<valueFromOper1<<endl;

 									//Testing operator == overloaded function
			cout<<"Testing operator ==(). BEFORE COMPARING two boards look like (BOARD 1 and BOARD 2)"<<endl<<endl;
			cout<<"\t Board 1  "<<endl;
			first2D.print();
			cout<<"\t Board 2 "<<endl;
			second2D.print();

			if(second2D == first2D){
				cout<<"TRUE Boards are EQUAL !!!"<<endl;
			}
			else{
				cout<<"FALSE Boards are NOT EQUAL !!!"<<endl;
			}
									//Testing NumberOfBoards() function
			cout<<"Testing NumberOfBoards() function. Number of total created BOARD OBJECTS -> "<<first2D.NumberOfBoards()<<endl;

									//Finally
									//Testing GLOBAL function implemented.

			check = IsValidGlobal(ArrayGlobal, SIZE);
			if(check == true)
				cout<<"GLOBAL function returned TRUE, board reached solution. Congrats!"<<endl;
			else
				cout<<"GLOBAL function returned FALSE. "<<endl;
		} 
	}

	else{
		cout<<"Please, provide name of the file."<<endl;
	}

}





















