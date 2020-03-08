/*			
			Alina Kuralova - 171044094
			Homework 5 using inheritance.
			This is an implementation file for AbstractBoard.cpp
*/

#include  "AbstractBoard.h"
namespace NPuzzleSavitch
{
	//Assigning zero value to my static at the beginning of the program.
	int AbstractBoard:: createdBoards=0;

	//CONSTRUCTORS
	AbstractBoard::AbstractBoard() : height(3), width(3), counterOfMoves(0), lastStep('S'), row_emptyCell(0), col_emptyCell(0){
		createdBoards++;			//Incrementing static value, to find number of created objects.
	};

	AbstractBoard::AbstractBoard(const int newWidth,const int newHeight) : width(newWidth),height(newHeight){
		createdBoards++;
	};

	int AbstractBoard::find_height(string file_name){
	    ifstream InputStream;               
	    int countHeight=0;
	    string line;

	    InputStream.open(file_name);   
	    if (InputStream.is_open())
	    {
	        while (getline (InputStream,line)){
	            countHeight++;                  //Increase counter, after each readed line, for identifying the HEIGHT of the board.
	        }
	    }
	    else cout << "Unable to open file";
	    InputStream.close();
	    return countHeight;
	}
    int AbstractBoard::find_width(string file_name){   
	    ifstream InputStream;
	    int width=1;
	    int i;
	    string line;

	    InputStream.open(file_name);   
	    if (InputStream.is_open())
	    {
	       getline (InputStream,line);
	       i=0;
	       while(i < line.size()){
	            if(line[i]==' '){       //Increase width value, according to size of the line and spaces inside.
	                width++;
	            }
	            i++;
	       }
	    }
	    else cout << "Unable to open file";
	    InputStream.close();

	    return width;
	}

	void AbstractBoard::setSize(const int NewHeight,const int NewWidth){
		if(NewWidth<3 || NewHeight<3){			//Checking the validity of the user input.
			cout<<"Incorrect size of the board. Aborting the program."<<endl;
			exit(1);
		}
		else{
	      	this->height=NewHeight;   
			this->width=NewWidth;
		}
	}

	int AbstractBoard::NumberOfBoards(){
		return createdBoards;
	}

	char AbstractBoard::lastMove()const{

		if(lastStep!='L' && lastStep!='R' && lastStep!='U' && lastStep!='D'){	//error check
			return 'S';
		}
		else{
			return lastStep;
		}
	}

	bool AbstractBoard::operator ==(const AbstractBoard& RightSide) const{
		int i,j, equal=0;
		if((height!=RightSide.height) || width!=RightSide.width){		//If, sizes are not equal boards can't be equal already.
			return false;
		}
		for(i=0; i<height; i++){
			for(j=0; j<width; j++){
				if((*this)(i,j)==(RightSide)(i,j)){		//Here, I used implemented operator() which helped me to make this function general.
					equal++;
				}
			}
		}
		if(equal==(height*width)){
			return true;
		}
		return false;	
	}

	void AbstractBoard::setEmptyCell(const int rowOfEmpty,const int colOfEmpty){

      	this->row_emptyCell=rowOfEmpty;   
		this->col_emptyCell=colOfEmpty;
	}

}//NPuzzleSavitch


