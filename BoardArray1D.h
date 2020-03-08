/*			
			This is a header file for BoardArray1D.h
			It is an interface for the derived class BoardArray1D
*/

#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H
#include "AbstractBoard.h"
#include <vector>

namespace NPuzzleSavitch
{
	class BoardArray1D : public AbstractBoard{
	public:

		BoardArray1D();
		BoardArray1D (int height, int width);
		BoardArray1D(const BoardArray1D& copy); 		        //Copy constructor
		BoardArray1D& operator=(const BoardArray1D& RightSide);	//Overloaded Assignment = operator()
		~BoardArray1D();									    //Destructor

		void print()const;
		bool readFromFile(const string fileRead);
		void writeToFile(const string fileWrite)const;
		void reset();
		void move(char inputMove);
		bool isSolved();	
		const int& operator()(int i, int j)const;

	private:		
		int *Array1D;			//main 1D array, keeps board.
		int counterOfElem;
		int creater_help;
		//Small helper functions for reset etc.
		void init();
		void create_board_from_file(const string input_line, const int row);
		int countElements();
		bool compare_arrays(vector<int> arr_temp);	
		void initMyArray();
	};
}

#endif


