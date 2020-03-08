/*			
			Alina Kuralova - 171044094
			Homework #5 using inheritance.
			This is a header file for AbstractBoard.h
			It is an interface for the class of AbstractBoard.
*/

#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
namespace NPuzzleSavitch
{
	class AbstractBoard{
	    public:
			//Constructors
			AbstractBoard(); 								
			AbstractBoard(const int newWidth,const int newHeight);
			
			//Accessor and Mutator functions
			inline int getHeight()const{return height;};		
			inline int getWidth()const{return width;};	
			inline int getCounterOfMoves()const{return counterOfMoves;};	
			inline int getRowEmptyCell()const{return row_emptyCell;};
			inline int getColEmptyCell()const{return col_emptyCell;};

			inline void setCounterOfMoves(const int totalMoves){counterOfMoves = totalMoves;};
			inline void setLastStep(const char LastStepMaded){lastStep = LastStepMaded;};	
			virtual void setEmptyCell(const int rowOfEmpty,const int colOfEmpty);
			
			//Functions
			virtual void print()const = 0;						//pure function, since it's going to be different for all derived classes
			virtual bool readFromFile(const string fileRead) = 0;
			virtual void writeToFile(const string fileWrite)const = 0;
			virtual void reset() = 0;
			virtual void setSize(const int height,const int width);
			virtual void move(char inputMove) = 0;
			virtual bool isSolved() = 0;

			virtual const int& operator()(int i, int j)const = 0;
			virtual bool operator ==(const AbstractBoard &RightSide) const; 
			static int NumberOfBoards();
			virtual char lastMove()const;	
			virtual int numOfMoves()const{return counterOfMoves;};

		protected:
			int height;				
			int width;	
			char lastStep;
			int counterOfMoves;
			static int createdBoards;
			//Helper member variables, keeps location of Empty cell. Used for Global Function's implementation
			int row_emptyCell;
			int col_emptyCell;
			vector<int> arr_solved;			//1D vector, keeps values of the board in sorted way.

			//HELPERS		
			//I'm using and need these small helper functions only for functions in my base class. 								
			int find_height(string file_name);									//finds height of the board given in the file
			int find_width(string file_name);	
			virtual bool compare_arrays(vector<int> arr_temp) = 0;				//compare 2 given arrays(used for identifying whether game is solved or not)
	};
	
}//NPuzzleSavitch

#endif
