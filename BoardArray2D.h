/*			
			This is a header file for BoardArray2D.h
			It is an interface for the derived class BoardArray2D
*/

#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H
#include "AbstractBoard.h"
#include <vector>

namespace NPuzzleSavitch
{
	class BoardArray2D : public AbstractBoard{
	public:

		BoardArray2D();
		BoardArray2D (int height, int width);
		BoardArray2D(const BoardArray2D& copy); 		        //Copy constructor
		BoardArray2D& operator=(const BoardArray2D& RightSide);	//Overloaded Assignment = operator()
		~BoardArray2D();									    //Destructor

		void print()const;
		bool readFromFile(const string fileRead);
		void writeToFile(const string fileWrite)const;
		void reset();
		void move(char inputMove);
		bool isSolved();	
		const int& operator()(int i, int j)const;

	private:
		int **Array2D;					//Main 2D Array, keeps board.
		int counterOfElem;
		
		//Small helper functions for reset etc
		void init();
		void create_board_from_file(const string input_line, const int row);
		int countElements();
		bool compare_arrays(vector<int> arr_temp);	
		void initMyArray();
	};

}


#endif

