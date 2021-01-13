#include<iostream>
#include<set>
using namespace std;

// Function to check if a given row is valid. It will return: -1 if the row contains an invalid value, 0 if the row contains repeated valuesand 1 is the row is valid.
int valid_row(int row, int suduko[9][9])
{
  set<int> s;
  for(int i=0;i<9;i++)
  {
    //Checking for values outside 0 and 9; 0 is considered valid because it denotes an empty cell.
    if(suduko[row][i]<0 || suduko[row][i]>9)
	{
      cout<<"Invalid value"<<endl;
      return -1;
    }
    else
    { 
      //Checking for repeated values.
      if(suduko[row][i]!=0)
      {
        if(s.insert(suduko[row][i]).second==false)
        {
          return 0;
        }
      }
    }
  }
  return 1;
}
// Function to check if a given column is valid. It will return:-1 if the column contains an invalid value ,0 if the column contains repeated values and 1 is the column is valid.
int valid_col(int col,int suduko[][9])
{
  set<int> s;
  for(int i=0;i<9;i++)
  {
    // Checking for values outside 0 and 9;0 is considered valid because it denotes an empty cell.
    if(suduko[i][col]<0 || suduko[i][col]>9)
    {
      cout<<"Invalid value"<<endl;
      return -1;
    }
    else
    {
       // Checking for repeated values.
      if(suduko[i][col]!=0)
      {
        if(s.insert(suduko[i][col]).second==false)
        {
          return 0;
        }
      }
    }
  }
  return 1;
}
// Function to check if all the subsquares are valid. It will return: -1 if a subsquare contains an invalid value 0 if a subsquare contains repeated values and 1 if the subsquares are valid.
int valid_subsuduko(int suduko[][9])
{
  for(int row=0;row<9;row=row+3)
  {
    for(int col=0;col<9;col=col+3)
	  {
      set<int> s;
      for(int r=row;r<row+3;r++)
      {
        for(int c=col;c<col+3;c++)
        {
          // Checking for values outside 0 and 9; 0 is considered valid because it denotes an empty cell.
          if(suduko[r][c]<0 || suduko[r][c]>9)
          {
            cout<<"Invalid value"<<endl;
              return -1;
          }
          else
          {
            // Checking for repeated values
            if(suduko[r][c]!=0)
            {
            
              if(s.insert(suduko[r][c]).second == false)
              {
                return 0;
              }
            } 
          }
        }
      }    
    }
  }
  return 1;
}

//Function to check if the board invalid.
bool valid_suduko(int suduko [9][9])
{
  for(int i=0;i<9;i++)
  {
    int res1 = valid_row(i,suduko);
    int res2 = valid_col(i,suduko);
    // If a row or a column is invalid, then the board is invalid.
    if(res1<1 || res2<1)
	{
      cout<<"The board is invalid"<<endl;
      return false;
    }
  }
  // if any one the subsquares is invalid, then the board is invalid.
  int res3=valid_subsuduko(suduko);
  if(res3<1)
  {
    return false;
  }
  else
  {
    return true;
  }
}

//Function finds an entry that is still unassigned in Suduko.If found,true is returned.If no unassigned entries remain,false is returned
bool FindUnassignedLocation(int suduko[9][9],int& row,int& col)
{
	for(row=0;row<9;row++)
		for(col=0;col<9;col++)
			if(suduko[row][col] == 0)
				return true;
	return false;
}

// Checks whether it will be right to assign num to the given row and col
bool isSafe(int suduko[9][9],int row,int col,int num)
{
	//check wheteher number is already in row or not
	for (int j=0;j<9;j++)
		if (suduko[row][j]==num)
			return false;
	//check wheteher number is already in column or not
	for (int i=0;i<9;i++)
		if (suduko[i][col]==num)
			return false;
	//check wheteher number is already in submatrix of that particular portion or not
	int smi=row/3*3;
	int smj=col/3*3;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if (suduko[i+smi][j+smj]==num)
				return false;
		}
	}
	return true;
}

//Function to assign value to unassigned places and check for their validation
bool SolveSudoku(int suduko[9][9])
{
	int row,col;

	//If there is no unassigned place,then we have the solution
	if (FindUnassignedLocation(suduko,row,col)==0)
		return true;

	for (int num=1;num<=9;num++) 
	{
		
		// Check if it's safe or not
		if (isSafe(suduko,row,col,num)) 
		{
			
			//put that there and proceed forward
			suduko[row][col]=num;

			if(SolveSudoku(suduko))
				return true;

			//if Fail,backtrack and put that value as 0 i.e; unassign that assigned value
			suduko[row][col]=0;
		}
	}
	return false;
}

//Function to print solution
void printSuduko(int suduko[9][9])
{
	for (int row=0;row<9;row++) 
	{
		for (int col=0;col<9;col++)
			cout<<suduko[row][col]<<" ";
		cout<<endl;
	}
}

int main()
{
	int suduko[9][9];

	//enter 0 for empty space
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			cin>>suduko[i][j];
		}
	}
  
  cout<<endl<<endl<<endl;

	if(valid_suduko(suduko))
  {
    	if (SolveSudoku(suduko)==1)
		    printSuduko(suduko);
	    else
		    cout<<"No solution exists";
  }
  else
    cout<<"invalid suduko";
	return 0;
}
