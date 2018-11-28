/* 
mazeio.cpp

Author:Andrew James Valle

Short description of this file: mazeio.cpp contains
definitions of functions which reads text from cin
and stores them into a 2D array as long as every 
character is formatted correctly. Otherwise the function
will return NULL. The other function simply prints out
the dimensions of the maze followed by the maze itself.
*/

#include <iostream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from cin into a dynamically allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * such as integers for the size not found.
 *
 * We also pass in two pointers to integers. Fill 
 * the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(int* rows, int* cols) {
   // FILL THIS IN
   bool fail = false;
   
   cin >> *rows >> *cols;
   fail = cin.fail();
    
   char** maze = new char*[*rows];
 
   for (int i=0; i<*rows; i++)
   {
       maze[i] = new char[*cols];
       
   }

    for (int i = 0; i<*rows; i++)
    {
     for (int j = 0; j<*cols; j++)
     {
      cin >> maze[i][j]; 
         
      if (maze[i][j] != 'S' && maze[i][j] != 'F' &&
          maze[i][j] != '.' && maze[i][j] != '#')
      {
          return NULL;   
      }
     }
    }
    
   if(fail)
       return NULL;
   else
       return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) {
   // FILL THIS IN
    cout << rows <<" " <<cols << endl;
    for (int i = 0; i<rows; i++)
    {   
        for (int j = 0; j< cols; j++)
        {
        cout << maze[i][j]; 
        }
        
        cout << endl;
    }
    
    
}

