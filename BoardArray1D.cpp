#include "BoardArray1D.h"
#include <fstream>

namespace NPuzzleSavitch
{   
    //CONSTRUCTORS
	BoardArray1D::BoardArray1D(): AbstractBoard(), creater_help(0){
		init();					//Function for aloocating memory for my 2D array from the heap.
	}

    BoardArray1D::BoardArray1D (int height, int width): AbstractBoard(height, width), creater_help(0){
    	init();
    }

    void BoardArray1D::init(){
		Array1D = new int[height*width];
    }


   /* This copy constructor is the First member of Big Three
	   - Takes an object as a parameter of the same type as a class
	   - According to the size of taken object, prepares memory place from the heap 
	   - then copies data of taken object to itself */

	BoardArray1D:: BoardArray1D(const BoardArray1D& copy){
		setSize(copy.getHeight(), copy.getWidth());

		Array1D=new int[height*width];

		for (int i = 0; i < height; i++){
			Array1D[i]=copy.Array1D[i];			
		}
	}

	/*** Second member of Big Three
		Assignment operator overloadings implementation */
	BoardArray1D& BoardArray1D::operator=(const BoardArray1D& RightSide){
		if(height!=RightSide.height || width!=RightSide.width)
		{
			delete [] Array1D;
			
			Array1D = new int[RightSide.height*RightSide.width];
		}

		height = RightSide.height;
		width = RightSide.width;
		for (int i = 0; i < height*width; i++)
		{
			Array1D[i] = RightSide.Array1D[i];	
		}
		return *this;
	}

    /** Third member of Big three
    - Implemented for deleting allocated memory space from heap.*/
    BoardArray1D:: ~BoardArray1D(){
		delete [] Array1D;
	}

    void BoardArray1D::print()const{
    	int i,j;
        int empty_cell;                    //Keeps value of empty cell in the board.
        int n = 0;
        empty_cell=-99;

        for(i=0; i < height; i++){         //nested loop for printing board.
        	for(j=0; j < width; j++){

        	    if(Array1D[n]<10){             
                    if(Array1D[n]==empty_cell)  cout<<"bb ";      
                    else   cout<<0<< Array1D[n]<<" ";  
                    n++;              
                }
                else{
                    if(Array1D[n]==empty_cell)     cout<<"bb  ";                                     
                    else  cout<< Array1D[n]<<" ";
                    n++;
                }       
        	}
        	cout<<endl;
        }
    }

    bool BoardArray1D::readFromFile(const string fileRead){
    	int row;
        ifstream InputStream;
        string line;
        int h,w,i;
        InputStream.open(fileRead);   
           if (InputStream.is_open()){
                h = find_height(fileRead);
                w = find_width(fileRead);
                if(h != height || w!=width){
					delete[] Array1D;				
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

    void BoardArray1D::create_board_from_file(const string input_line, const int row){
        string line = "";             //assigning null for begining
        int m=0, control=1;   
        int value;
        int iterate=input_line.size();

        for(auto n : input_line){       //Since, we have to use auto keyword and etc, I have a ranged loop.
            if((n == ' ') && (control!=width)){        //If it reaches space, make convertions to int and assign values to an array, then assign null again.
                if(line!="bb"){         //Makes one more control for exception as 'bb', if it's not bb make castings and etc.
                    value=stoi(line);

                    line = "";
                    Array1D[creater_help]=value;   //Assign casted int value into the array.
                    creater_help++; control++;
                }
                else{                   //If our line is 'bb'
                    value=-99;          //Assign a value -99 for identifying empty space.
                    line = "";          //Then assign null again.
                    setEmptyCell(row,creater_help);
                    Array1D[creater_help]=value;
                    creater_help++;  control++;
                }
            }
            else if(m+1==iterate){      //Checks, whether it is the last iteration of the loop or no

                line = line + n;        //If it is the last one, asssigns the last value into the array. I made it because there is no space after the end of the line.
                if(line!="bb"){         //Makes one more control for exception as 'bb', if it's not bb make castings and etc.
                    value=stoi(line); 

                    line = "";
                    Array1D[creater_help]=value;
                    creater_help++; control++;
                }
                else{                   //If our line is 'bb'
              
                    value=-99;          //Assign a value -99 for identifying empty space.
                    line = "";          //Then assign null again.
                    setEmptyCell(row,creater_help);
                    Array1D[creater_help]=value;
                    creater_help++;  control++;
                }           
            }
            else{
                line = line + n;        //Take second character and keeps going this way.
            }
            m++;
        }   
    }


   void BoardArray1D::writeToFile(const string fileWrite)const{
        ofstream SaveFile;
        string line;
        string converted;
        int size, k,j, n=0;

        SaveFile.open(fileWrite);

        for(j=0; j<height; j++){
            for(k=0; k<width; k++){

                if(Array1D[n] == 0){
                    SaveFile<<"00";
                    n++;
                }
                else if(Array1D[n] == -99){
                    SaveFile<<"bb";
                    n++;
                }
                else if(Array1D[n] != 0 && Array1D[n]<10){
                    SaveFile<<"0"<<Array1D[n];
                    n++;
                }
                else{
                    SaveFile<<Array1D[n];
                    n++;
                }
                if(k < width-1){
                    SaveFile<<" ";
                }     
            }
            SaveFile<<endl;
        }

        SaveFile.close();
    }

    //Reset function -> resets the board by bringing it to the final solution.
    //In the reset function arr_solved is 1D vector, with sorted numbers inside. 
    void BoardArray1D::reset(){
        int i,j, n=0;
        int temp;

        initMyArray();
        n=0;  
                                  
         for(i=0; i<height*width; i++){
       
            if( Array1D[i]!=0 ){    
                Array1D[i] = arr_solved[n];
                n++;
            }
            else if(Array1D[i]==0){
                Array1D[i] = 0;
            }                    
        }     
        Array1D[height*width-1]=-99;
       	
        setEmptyCell(height-1,width-1);
        
    }

    int BoardArray1D::countElements(){
        int j;
        int countt = 0;
          
        for(j=0; j<height*width; j++){ 
            if(Array1D[j]!=0 && Array1D[j]!=-99){
                countt++;                  //counterOfElem, keeps number of values I have in my board. It did't count empty space and 00.
            }
        }        
        return countt;
    }


    void BoardArray1D::move(char input_Move){
	    int temp;              
	    int e_column, e_row;    //For keeping location of an empty cell and modifying it.
	    int i, j, k=0;       
	    int empty_cell;			
	    vector<vector<int> > temp_Array(height , vector<int> (width)); 

	    empty_cell=-99;

	    //Since I have 1D array, I created temporary 2D array, for using it in operations below
        for(i=0; i<height; i++){
            temp_Array.push_back(vector<int>());
            for(j=0; j<width; j++){
                temp_Array[i].push_back(j);
            }
        }

        for(i=0; i<height; i++){
            for(j=0; j<width; j++){ 
            	temp_Array[i][j] = Array1D[k];
            	k++;
            }
        }
              						
	    for(i=0; i<height; i++){    //Search and keep location of my 'empty_cell' cause I need it later.
	        for(j=0; j<width; j++){
	            if(temp_Array[i][j]==empty_cell){
	                e_column=j;         //Keep column
	                e_row=i;            //Keep row.
	            }
	        }
	    }

	    if(input_Move=='R'){        //For making a move to the RIGHT
	        if((e_column+1<width) && (temp_Array[e_row][e_column+1]!=0)){      //Check firstly is it possible or no, if possible make swap.
	            temp=temp_Array[e_row][e_column];       //Making swap
	            temp_Array[e_row][e_column]=temp_Array[e_row][e_column+1];
	            temp_Array[e_row][e_column+1]=temp;
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
	        if((e_column!=0) && (temp_Array[e_row][e_column-1]!=0)){
	            temp=temp_Array[e_row][e_column];       
	            temp_Array[e_row][e_column]=temp_Array[e_row][e_column-1];
	            temp_Array[e_row][e_column-1]=temp;
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
	        if((e_row!=0) && (temp_Array[e_row-1][e_column]!=0)){ 
	            temp=temp_Array[e_row][e_column];       
	            temp_Array[e_row][e_column]=temp_Array[e_row-1][e_column];
	            temp_Array[e_row-1][e_column]=temp;
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
	        if((e_row+1<height) && (temp_Array[e_row+1][e_column]!=0)){
	            temp=temp_Array[e_row][e_column];       
	            temp_Array[e_row][e_column]=temp_Array[e_row+1][e_column];
	            temp_Array[e_row+1][e_column]=temp;
	            e_row=e_row+1;          //Move down and increase row to one.

	            counterOfMoves++;
	            setLastStep('D');
	            setEmptyCell(e_row,e_column);

	        }
	        else{
	            cout<<"Unfortunately, you can not move to the DOWN.  Try again."<<endl;
	        }
	    }    
	    k=0;
	    for(i=0; i<height; i++){
            for(j=0; j<width; j++){ 
            	Array1D[k] = temp_Array[i][j];
            	k++;
            }
        }
	}


    bool BoardArray1D::isSolved(){
	    int i=0,j=0;
	    int n=0;
	    bool compare_result;

	    vector<int> arr_temp;     //two arrays, so I'm allocating memory as much as values I have inside the board

	    counterOfElem=countElements();
	    for(j=0;j<counterOfElem;j++){
	        arr_temp.push_back(0);    
	    }
	    for(int k = 0; k<getHeight()*getWidth(); k++){
     		 if(Array1D[k]!= 0 && Array1D[k] != -99){    
                arr_temp[n]=Array1D[k];
                n++; 
            }
	    }
	     	    
	    //inside of one array we have sorted values and unsorted original values inside another one
	    compare_result=compare_arrays(arr_temp);    //result of comparing will let us know whether game is finished or not.
	    
	    if((compare_result==true) && (Array1D[height*width-1]==-99))   return true;    //Since,The solution always places the empty tile at the lower right corner. I added this statemenet to check whether solved or no
	    else     return false;

    return true;
    }

    
    bool BoardArray1D::compare_arrays(vector<int> arr_temp){
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

    const int& BoardArray1D::operator()(int i, int j)const{
        if((i>=0 && j>=0) && (i<height && j<width)){     //Checks, whether indexes are valid or not.
            return Array1D[i*j+j];
        }
        exit(1);      
    }


    void BoardArray1D::initMyArray(){
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
	    for(i=0; i<height*width; i++){       

            if(Array1D[i] != 0 && Array1D[i] != -99){  

                arr_solved[n]=Array1D[i];
                n++;
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


}//NPuzzleSavitch








