
#include "BoardArray2D.h"
#include <fstream>

namespace NPuzzleSavitch
{
	BoardArray2D::BoardArray2D(): AbstractBoard(){
		init();					//Function for aloocating memory for my 2D array from the heap.
	}

    BoardArray2D::BoardArray2D (int height, int width): AbstractBoard(height, width){
    	init();
    }

    void BoardArray2D::init(){
    	Array2D = new int*[height];
    	int i,j;
    	for(i=0; i<height; i++){
    		Array2D[i] = new int[width];
    	}
    }

    /* This copy constructor is the First member of Big Three
	   - Takes an object as a parameter of the same type as a class
	   - According to the size of taken object, prepares memory place from the heap 
	   - then copies data of taken object to itself */

	BoardArray2D:: BoardArray2D(const BoardArray2D& copy){
		setSize(copy.getHeight(), copy.getWidth());

		Array2D=new int*[height];
		for (int i = 0; i < height; i++){
			Array2D[i]=new int[width];
		}
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				Array2D[i][j]=copy.Array2D[i][j];
			}
		}
	}
	/*** Second member of Big Three
		Assignment operator overloadings implementation */
	BoardArray2D& BoardArray2D::operator=(const BoardArray2D& RightSide){
		if(height!=RightSide.height || width!=RightSide.width)
		{
			for (int i = 0; i < height; ++i)
			{
				delete[] Array2D[i];
			}
			delete[] Array2D;
			Array2D=new int*[RightSide.height];
			for (int i = 0; i < RightSide.height; i++)
			{
				Array2D[i]= new int[RightSide.width];
			}
		}
		height=RightSide.height;
		width=RightSide.width;
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				Array2D[i][j]=RightSide.Array2D[i][j];
			}
		}
		return *this;
	}
	/** Third member of Big three
		- Implemented for deleting allocated memory space from heap.*/
	BoardArray2D:: ~BoardArray2D(){
		int i;
	
		for (i = 0; i < height; i++)
		{
			delete[] Array2D[i];
		}
		delete[] Array2D;	
	}


    void BoardArray2D::print()const{
    	int i,j;
        int empty_cell;                             //Keeps value of empty cell in the board.
        
        empty_cell=-99;

        for(i=0; i < height; i++){         //nested loop for printing board.
            for (j=0; j < width; j++){

                if(Array2D[i][j]<10){             
                    if(Array2D[i][j]==empty_cell)  cout<<"bb ";      
                    else   cout<<0<< Array2D[i][j]<<" ";                
                }
                else{
                    if(Array2D[i][j]==empty_cell)     cout<<"bb  ";                                     
                    else  cout<< Array2D[i][j]<<" ";
                }       
            }
            cout<<endl;
        }
    }

    bool BoardArray2D::readFromFile(const string fileRead){
    	int row;
        ifstream InputStream;
        string line;
        int h,w,i;
        InputStream.open(fileRead);   
           if (InputStream.is_open()){
                h = find_height(fileRead);
                w = find_width(fileRead);
                if(h != height || w!=width){

					for (i = 0; i < height; i++)
					{
						delete[] Array2D[i];
					}
					delete[] Array2D;
				
                	setSize(h,w);

                	init();
                }
                
                row=0;
                while (getline (InputStream,line)){
                    create_board_from_file(line, row);
                    row++;
                }
               
           }
           else{
                cout << "Unable to open file "<<endl;
                return false;
           }       
           InputStream.close();

           counterOfElem = countElements();
           initMyArray();

         return true;
    }

    void BoardArray2D::create_board_from_file(const string input_line, const int row){
        string line = "";             //assigning null for begining
        int j,m=0, control=1;   
        int value;
        int iterate=input_line.size();

        j=0;
        for(auto n : input_line){       //Since, we have to use auto keyword and etc, I have a ranged loop.
            if((n == ' ') && (control!=width)){        //If it reaches space, make convertions to int and assign values to an array, then assign null again.
                if(line!="bb"){         //Makes one more control for exception as 'bb', if it's not bb make castings and etc.
                    value=stoi(line);

                    line = "";
                    Array2D[row][j]=value;   //Assign casted int value into the array.
                    j++; control++;
                }
                else{                       //If our line is 'bb'
                    value=-99;              //Assign a value -99 for identifying empty space.
                    line = "";              //Then assign null again.
                    setEmptyCell(row,j);    //Update the location of the empty cell
                    Array2D[row][j]=value;
                    j++;  control++;
                }
            }
            else if(m+1==iterate){      //Checks, whether it is the last iteration of the loop or no

                line = line + n;        //If it is the last one, asssigns the last value into the array. I made it because there is no space after the end of the line.
                if(line!="bb"){         //Makes one more control for exception as 'bb', if it's not bb make castings and etc.
                    value=stoi(line);

                    line = "";
                    Array2D[row][j]=value;
                    j++; control++;
                }
                else{                  
              
                    value=-99;         
                    line = "";         
                    setEmptyCell(row,j);
                    Array2D[row][j]=value;
                    j++;  control++;
                }          
            }
            else{
                line = line + n;        //Take second character and keeps going this way.
            }
            m++;
        }   
    }

    void BoardArray2D::writeToFile(const string fileWrite)const{
        ofstream SaveFile;
        string line;
        string converted;
        int size, k,j;

        SaveFile.open(fileWrite);

        for(j=0; j<height; j++){
            for(k=0; k<width; k++){

                if(Array2D[j][k]==0){
                    SaveFile<<"00";
                }
                else if(Array2D[j][k]==-99){
                    SaveFile<<"bb";
                }
                else if(Array2D[j][k]!=0 && Array2D[j][k]<10){
                    SaveFile<<"0"<<Array2D[j][k];
                }
                else{
                    SaveFile<<Array2D[j][k];
                }
                if(k<width-1){
                    SaveFile<<" ";
                }     
            }
            SaveFile<<endl;
        }

        SaveFile.close();
    }

    void BoardArray2D::reset(){
        int i,j, n=0;
        int temp;

        initMyArray();
        n=0;  
      
        //Assigning sorted values, 00's and an empty cell to my final sorted 2D vector temp_solved_Array.                              
         for(i=0; i<height; i++){
            for(j=0; j<width; j++){ 
                if( Array2D[i][j]!=0 ){    
                    Array2D[i][j] = arr_solved[n];
                    n++;
                }
                else if(Array2D[i][j]==0){
                    Array2D[i][j] = 0;
                }        
            }
        }
      
        Array2D[height-1][width-1]=-99;
       	
        setEmptyCell(height-1,width-1);      
    }

    int BoardArray2D::countElements(){
        int i,j;
        int countt = 0;
        for(i=0; i<height; i++){
            for(j=0; j<width; j++){ 
                if(Array2D[i][j]!=0 && Array2D[i][j]!=-99){
                    countt++;                  //counterOfElem, keeps number of values I have in my board. It did't count empty space and 00.
                }
            }
        }
        return countt;
    }

    void BoardArray2D::move(char input_Move){
	    int temp;              
	    int e_column, e_row;    //For keeping location of an empty cell and modifying it.
	    int i, j;       
	    int empty_cell;

	    empty_cell=-99;

	    for(i=0; i<height; i++){    //Search and keep location of my 'empty_cell' cause I need it later.
	        for(j=0; j<width; j++){
	            if(Array2D[i][j]==empty_cell){
	                e_column=j;         //Keep column
	                e_row=i;            //Keep row.
	            }
	        }
	    }

	    if(input_Move=='R'){        //For making a move to the RIGHT
	        if((e_column+1<width) && (Array2D[e_row][e_column+1]!=0)){      //Check firstly is it possible or no, if possible make swap.
	            temp=Array2D[e_row][e_column];       //Making swap
	            Array2D[e_row][e_column]=Array2D[e_row][e_column+1];
	            Array2D[e_row][e_column+1]=temp;
	            e_column=e_column+1;

	            counterOfMoves++;
	            setLastStep('R');
	            setEmptyCell(e_row,e_column);
	        }
	        else{                               //IF it is not possible, warn the user about incorrect input.
	            cout<<"Unfortunately, you can not move to the right. Try again."<<endl;
	        }
	    }

	    else if(input_Move=='L'){               //Statements below for 'L', "U", 'D' follows the same algorithm as eplained above.
	        if((e_column!=0) && (Array2D[e_row][e_column-1]!=0)){
	            temp=Array2D[e_row][e_column];       
	            Array2D[e_row][e_column]=Array2D[e_row][e_column-1];
	            Array2D[e_row][e_column-1]=temp;
	            e_column=e_column-1;

	            counterOfMoves++;
	            setLastStep('L');
	            setEmptyCell(e_row,e_column);
	        }
	        else{
	            cout<<"Unfortunately, you can not move to the left.  Try again."<<endl;
	        }
	    }

	    else if(input_Move=='U'){
	        if((e_row!=0) && (Array2D[e_row-1][e_column]!=0)){ 
	            temp=Array2D[e_row][e_column];       
	            Array2D[e_row][e_column]=Array2D[e_row-1][e_column];
	            Array2D[e_row-1][e_column]=temp;
	            e_row=e_row-1;           //Change location and decrease row, cause it's going to "UP"

	            counterOfMoves++;
	            setLastStep('U');
	            setEmptyCell(e_row,e_column);
	        }
	        else{
	            cout<<"Unfortunately, you can not move to the UP.  Try again."<<endl;
	        }
	    }

	    else if(input_Move=='D'){
	        if((e_row+1<height) && (Array2D[e_row+1][e_column]!=0)){
	            temp=Array2D[e_row][e_column];       
	            Array2D[e_row][e_column]=Array2D[e_row+1][e_column];
	            Array2D[e_row+1][e_column]=temp;
	            e_row=e_row+1;          //Move down and increase row to one.

	            counterOfMoves++;
	            setLastStep('D');
	            setEmptyCell(e_row,e_column);

	        }
	        else{
	            cout<<"Unfortunately, you can not move to the DOWN.  Try again."<<endl;
	        }
	    }    
	}

    bool BoardArray2D::isSolved(){
	    int i=0,j=0;
	    int n=0;
	    bool compare_result;

        vector<int> arr_temp;     //two arrays, so I'm allocating memory as much as values I have inside the board
   
        counterOfElem=countElements();
        for(j=0;j<counterOfElem;j++){
            arr_temp.push_back(0);    
        }
        for(int k = 0; k<getHeight(); k++){
         	for(int m=0; m<getWidth(); m++){
         		 if(Array2D[k][m]!=0 && Array2D[k][m]!=-99){    
                    arr_temp[n]=Array2D[k][m];
                    n++; 
                }
         	}
         	
         }
        //inside of one array we have sorted values and unsorted original values inside another one
        compare_result=compare_arrays(arr_temp);    //result of comparing will let us know whether game is finished or not.
        
        if((compare_result==true) && (Array2D[height-1][width-1]==-99))   return true;    //Since,The solution always places the empty tile at the lower right corner. I added this statemenet to check whether solved or no
        else     return false;
    
    return true;
    }
    
    bool BoardArray2D::compare_arrays(vector<int> arr_temp){
        int i,j;
        int counter=0;
        counterOfElem=countElements();
  
        for(i=0; i<counterOfElem; i++){       //Simple function for comparing values inside of two arrays.
            
            if(arr_temp[i]==arr_solved[i]){
                counter++;
            }   
        }
        if(counter==counterOfElem) return true;

        return false;
    }

    const int& BoardArray2D::operator()(int i, int j)const{
        if((i>=0 && j>=0) && (i<height && j<width)){     //Checks, whether indexes are valid or not.
            return Array2D[i][j];
        }
        exit(1);      
    }

    void BoardArray2D::initMyArray(){
       int i,j, n=0;
        int temp;

        counterOfElem=countElements();  

        if(arr_solved.size() > 0){
        	arr_solved.clear();
        }    

        for(j=0;j<counterOfElem;j++){
            arr_solved.push_back(0);     
        }


        //These nested loops copies all values inside of an array(except 00 and empty cell) to one dimentional array in order to sort it.
        for(i=0; i<height; i++){       
            for(j=0; j<width; j++){ 
                if(Array2D[i][j]!=0 && Array2D[i][j]!=-99){  

                    arr_solved[n]=Array2D[i][j];
                    n++;
                }
            }
        }

        //typical array sorting loops. 
        for(i=0; i<counterOfElem; i++){          
            for(j=i+1; j<counterOfElem; j++){
                if(arr_solved[i]>arr_solved[j]){
                    temp = arr_solved[i];
                    arr_solved[i]=arr_solved[j];
                    arr_solved[j]=temp;
                }
            }
        }    	
    }











}