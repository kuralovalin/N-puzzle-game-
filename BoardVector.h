/*			
			This is a header file for BoardVector.h
			It is an interface for the derived class BoardVector
*/

#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H
#include "AbstractBoard.h"
#include <vector>

namespace NPuzzleSavitch
{
	class BoardVector : public AbstractBoard
	{
	public:
		BoardVector(): AbstractBoard(){};
		BoardVector (int height, int width);
		void print()const;
		bool readFromFile(const string fileRead);
		void writeToFile(const string fileWrite)const;
		void reset();
		void move(char inputMove);
		bool isSolved();	
		const int& operator()(int i, int j)const;

	private:
		vector<vector<int> > vectBoard;		
		int counterOfElem;				

		//Small helper functions for reset etc
		void init();					//initializes vect, using push_back in the beginning.
		void create_board_from_file(const string input_line, const int row);
		int countElements();
		bool compare_arrays(vector<int> arr_temp);	
		void initMyArray();

	};
}

#endif
