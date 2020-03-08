
#include "BoardVector.h"
#include <fstream>

namespace NPuzzleSavitch
{
    BoardVector::BoardVector (int height, int width): AbstractBoard(height, width){
        init();
    }
    void BoardVector::init(){
        int i,j;

        for(i=0; i<height; i++){
            vector<int> temp;
            for(j=0;j<width;j++){
                temp.push_back(0);
            }
            vectBoard.push_back(temp);
            temp.clear();
        }
    }

    bool BoardVector::readFromFile(const string fileRead){
    	int row;
        ifstream InputStream;
        string line;

        InputStream.open(fileRead);   
           if (InputStream.is_open()){
                height = find_height(fileRead);
                width = find_width(fileRead);
                setSize(height,width);
                init();
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


    void BoardVector::create_board_from_file(const string input_line, const int row){
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
                    vectBoard[row][j]=value;   //Assign casted int value into the array.
                    j++; control++;
                }
                else{                   //If our line is 'bb'
                    value=-99;          //Assign a value -99 for identifying empty space.
                    line = "";          //Then assign null again.
                    setEmptyCell(row,j);
                    vectBoard[row][j]=value;
                    j++;  control++;
                }
            }
            else if(m+1==iterate){      //Checks, whether it is the last iteration of the loop or no

                line = line + n;        //If it is the last one, asssigns the last value into the array. I made it because there is no space after the end of the line.
                if(line!="bb"){         //Makes one more control for exception as 'bb', if it's not bb make castings and etc.
                    value=stoi(line);

                    line = "";
                    vectBoard[row][j]=value;
                    j++; control++;
                }
                else{                   //If our line is 'bb'
              
                    value=-99;          //Assign a value -99 for identifying empty space.
                    line = "";          //Then assign null again.
                    setEmptyCell(row,j);
                    vectBoard[row][j]=value;
                    j++;  control++;
                }
                
            }
            else{
                line = line + n;        //Take second character and keeps going this way.
            }
            m++;
        }   
    }

    void BoardVector::writeToFile(const string fileWrite)const{
        ofstream SaveFile;
        string line;
        string converted;
        int size, k,j;

        SaveFile.open(fileWrite);

        for(j=0; j<vectBoard.size(); j++){
            for(k=0; k<vectBoard[k].size(); k++){

                if(vectBoard[j][k]==0){
                    SaveFile<<"00";
                }
                else if(vectBoard[j][k]==-99){
                    SaveFile<<"bb";
                }
                else if(vectBoard[j][k]!=0 && vectBoard[j][k]<10){
                    SaveFile<<"0"<<vectBoard[j][k];
                }
                else{
                    SaveFile<<vectBoard[j][k];
                }
                if(k<width-1){
                    SaveFile<<" ";
                }     
            }
            SaveFile<<endl;
        }

        SaveFile.close();
    }

    void BoardVector::print()const{
    	 int i,j;
        int empty_cell;                             //Keeps value of empty cell in the board.
        
        empty_cell=-99;

        for(i=0; i < vectBoard.size(); i++){         //nested loop for printing board.
            for (j=0; j < vectBoard[i].size(); j++){

                if(vectBoard[i][j]<10){             
                    if(vectBoard[i][j]==empty_cell)  cout<<"bb ";      
                    else   cout<<0<< vectBoard[i][j]<<" ";                
                }
                else{
                    if(vectBoard[i][j]==empty_cell)     cout<<"bb  ";                                     
                    else  cout<< vectBoard[i][j]<<" ";
                }       
            }
            cout<<endl;
        }
    }

    //In the reset function arr_solved is 1D vector, with sorted numbers inside. (Numbers were taken from the original vect of vect)
    //temp_solved_Array is 2D vector which is a sorted version of the original vect of vect board. 
    void BoardVector::reset(){
        int i,j, n=0;
        int temp;
        vector<vector<int> > temp_solved_Array(height , vector<int> (width)); 
      
        //makes push_back for the first initializations of vectors .

        for(i=0; i<height; i++){
            temp_solved_Array.push_back(vector<int>());
            for(j=0; j<width; j++){
                temp_solved_Array[i].push_back(j);
            }
        }
        initMyArray();
        n=0;  
        //Assigning sorted values, 00's and an empty cell to my final sorted 2D vector temp_solved_Array.                              
         for(i=0; i<vectBoard.size(); i++){
            for(j=0; j<vectBoard[i].size(); j++){ 
                if( vectBoard[i][j]!=0 ){    
                    temp_solved_Array[i][j] = arr_solved[n];
                    n++;
                }
                else if(vectBoard[i][j]==0){
                    temp_solved_Array[i][j] = 0;
                }        
            }
        }
        temp_solved_Array[height-1][width-1]=-99;

        //temp_solved_Array keeps sorted array, below I assigned all values of this array to my original one.
        for(i=0; i<vectBoard.size(); i++){         
            for(j=0; j<vectBoard[i].size(); j++){ 
                vectBoard[i][j]=temp_solved_Array[i][j];
                
            }
        }        
        setEmptyCell(height-1,width-1);
    }

    int BoardVector::countElements(){
        int i,j;
        int countt = 0;
        for(i=0; i<vectBoard.size(); i++){
            for(j=0; j<vectBoard[i].size(); j++){ 
                if(vectBoard[i][j]!=0 && vectBoard[i][j]!=-99){
                    countt++;                  //counterOfElem, keeps number of values I have in my board. It did't count empty space and 00.
                }
            }
        }
        return countt;
    }

    void BoardVector::move(char input_Move){
        int temp;              
        int e_column, e_row;    //For keeping location of an empty cell and modifying it.
        int i, j;       
        int empty_cell;

        empty_cell=-99;

        for(i=0; i<height; i++){    //Search and keep location of my 'empty_cell' cause I need it later.
            for(j=0; j<width; j++){
                if(vectBoard[i][j]==empty_cell){
                    e_column=j;         //Keep column
                    e_row=i;            //Keep row.
                }
            }
        }

        if(input_Move=='R'){        //For making a move to the RIGHT
            if((e_column+1<width) && (vectBoard[e_row][e_column+1]!=0)){      //Check firstly is it possible or no, if possible make swap.
                temp=vectBoard[e_row][e_column];       //Making swap
                vectBoard[e_row][e_column]=vectBoard[e_row][e_column+1];
                vectBoard[e_row][e_column+1]=temp;
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
            if((e_column!=0) && (vectBoard[e_row][e_column-1]!=0)){
                temp=vectBoard[e_row][e_column];       
                vectBoard[e_row][e_column]=vectBoard[e_row][e_column-1];
                vectBoard[e_row][e_column-1]=temp;
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
            if((e_row!=0) && (vectBoard[e_row-1][e_column]!=0)){ 
                temp=vectBoard[e_row][e_column];       
                vectBoard[e_row][e_column]=vectBoard[e_row-1][e_column];
                vectBoard[e_row-1][e_column]=temp;
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
            if((e_row+1<height) && (vectBoard[e_row+1][e_column]!=0)){
                temp=vectBoard[e_row][e_column];       
                vectBoard[e_row][e_column]=vectBoard[e_row+1][e_column];
                vectBoard[e_row+1][e_column]=temp;
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

    bool BoardVector::isSolved(){
    int i,j;
    int n=0;
    bool compare_result;

       vector<int> arr_temp;     //two arrays, so I'm allocating memory as much as values I have inside the board

        for(j=0;j<counterOfElem;j++){
            arr_temp.push_back(0);    
        }
        for(i=0; i<height; i++){
            for(j=0; j<width; j++){ 
                if(vectBoard[i][j]!=0 && vectBoard[i][j]!=-99){    
                    arr_temp[n]=vectBoard[i][j];
                    n++; 
                }
            }
        }

        //inside of one array we have sorted values and unsorted original values inside another one
        compare_result=compare_arrays(arr_temp);    //result of comparing will let us know whether game is finished or not.

        if((compare_result==true) && (vectBoard[height-1][width-1]==-99))   return true;    //Since,The solution always places the empty tile at the lower right corner. I added this statemenet to check whether solved or no
        else     return false;
    
    return true;
    }

    bool BoardVector::compare_arrays(vector<int> arr_temp){
        int i,j;
        int counter=0;

        for(i=0; i<counterOfElem; i++){       //Simple function for comparing values inside of two arrays.
            if(arr_temp[i]==arr_solved[i]){
                counter++;
            }   
        }

        if(counter==counterOfElem) return true;

        return false;
    }

    const int& BoardVector::operator()(int i, int j)const{
        if((i>=0 && j>=0) && (i<height && j<width)){     //Checks, whether indexes are valid or not.
            return vectBoard[i][j];
        }
        exit(1);      
    }
    void BoardVector:: initMyArray(){
       int i,j, n=0;
        int temp;

        counterOfElem=countElements();        

        //makes push_back for the first initializations of vectors with zeros.
        for(j=0;j<counterOfElem;j++){
            arr_solved.push_back(0);     
        }

        //These nested loops copies all values inside of an array(except 00 and empty cell) to one dimentional array in order to sort it.
        for(i=0; i<vectBoard.size(); i++){       
            for(j=0; j<vectBoard[i].size(); j++){ 
                if(vectBoard[i][j]!=0 && vectBoard[i][j]!=-99){    
                    arr_solved[n]=vectBoard[i][j];
                    n++;
                }
            }
        }

        //typical array sorting loops. Since, I have to sort my array for future needs.  
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