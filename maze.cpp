/* 
maze.cpp

Author: Andrew Valle

Short description of this file: This program uses
BFS for the purpose of finding the shortest path
from start to finish in a given maze. 
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);
// Prototype for noLava which makes sure that checked
// neighbors in queue are in valid positions
bool noLava(int, int, int, int);

// main function to read, solve maze, and print result
int main() {
   int rows, cols, result;
   char** mymaze;
   
   mymaze = read_maze(&rows, &cols); // FILL THIS IN
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   // when working on Checkpoint 3, you will call maze_search here.
   // here. but for Checkpoint 1, just assume we found the path.
   result = maze_search(mymaze, rows, cols); // TO BE CHANGED

   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);

   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // ADD CODE HERE to delete all memory 
   // that read_maze allocated
    
   for (int i=0; i<rows; i++)
   {
         
           delete [] mymaze[i];
  
   }
    
   delete [] mymaze;
   


   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) {
   int numS = 0; //Keeps track of num of S's (for validation)
   int numF = 0; //Keeps track of num of F's (for validation)
   bool found_Finish = false;
   Location start;
   Location current;
   Location neighbor;
   Queue q(rows*cols);
  
    
    
    for (int i=0; i<rows; i++)
    {
       for (int j=0; j<cols; j++)
       {
           if (maze[i][j] == 'S')
           {
               start.row = i;
               start.col = j;
               numS++;
           }
           
           else if (maze[i][j] == 'F')
           {
               numF++;
           }
           
           else
               continue;
       }
    }
    
    if ((numS == 0 || numS>1) || (numF == 0 || numF>1))
    {
        return -1;   
    }
    
    else
    {
        Location** predecessor = new Location*[rows];
        int** visited = new int*[rows];
        
        for (int i = 0; i<rows; i++) //Dynamically allocate predecessor array
        {                           //and visited array
            predecessor[i] = new Location[cols];
            visited[i] = new int[cols];
        }
    
       for (int i = 0; i<rows; i++)
       {
           for (int j = 0; j<cols; j++)
           {
               predecessor[i][j].row = -1;
               predecessor[i][j].col = -1;
               visited[i][j] = 0;   
           }        
       }
     
       q.add_to_back(start); //Add start to queue
     
     while(!q.is_empty())
     {
         current = q.remove_from_front();
         
         //CHECK NORTH
         if ( noLava(current.row - 1, current.col, rows, cols) && 
             (maze[current.row - 1][current.col] == '.' || 
              maze[current.row - 1][current.col] == 'F') && 
             (!visited[current.row - 1][current.col])  ) 
         {
             
             if ( maze[current.row - 1][current.col] == 'F')
             {
                 found_Finish = true;
                 break;
             }
             
             else
             {
             neighbor.row = current.row - 1;
             neighbor.col = current.col;
             q.add_to_back(neighbor);
             visited[current.row - 1][current.col] = 1;
             predecessor[current.row - 1][current.col].row = current.row;
             predecessor[current.row - 1][current.col].col = current.col;
           
             }
             
             
         }
         
         //CHECK WEST
         if (noLava(current.row, current.col - 1, rows, cols) && 
            (maze[current.row][current.col - 1] == '.' || 
             maze[current.row][current.col - 1] == 'F') && 
             (!visited[current.row][current.col - 1])  ) 
         {
             if(maze[current.row][current.col - 1] == 'F')
             {
                 found_Finish = true;
                 break;
             }
             
             else
             {
             neighbor.row = current.row;
             neighbor.col = current.col - 1;
             q.add_to_back(neighbor);
                 visited[current.row][current.col - 1] = 1;
             predecessor[current.row][current.col - 1].row = current.row;
             predecessor[current.row][current.col - 1].col = current.col;
             
             }
            
         }
         
         
         //CHECK SOUTH
         if ( noLava(current.row + 1, current.col, rows, cols) && 
             (maze[current.row + 1][current.col] == '.' || 
              maze[current.row + 1][current.col] == 'F') && 
             (!visited[current.row + 1][current.col])  ) 
         {
             if(maze[current.row + 1][current.col] == 'F')
             {
                 found_Finish = true;
                 break;
             }
             
             else
             {
                 neighbor.row = current.row + 1;
                 neighbor.col = current.col;
                 q.add_to_back(neighbor);
                 visited[current.row + 1][current.col] = 1;
                 predecessor[current.row + 1][current.col].row = current.row;
                 predecessor[current.row + 1][current.col].col = current.col;
             }
             
         }
         
         
         //CHECK EAST
         if ( noLava(current.row, current.col + 1, rows, cols) && 
             (maze[current.row][current.col + 1] == '.' || 
              maze[current.row][current.col + 1] == 'F') && 
             (!visited[current.row][current.col + 1])  ) 
         {
             if(maze[current.row][current.col + 1] == 'F')
             {
                 found_Finish = true;
                 break;
             }
             
             else
             {
                 neighbor.row = current.row;
                 neighbor.col = current.col + 1;
                 q.add_to_back(neighbor);
                 visited[current.row][current.col + 1] = 1;
                 predecessor[current.row][current.col + 1].row = current.row;
                 predecessor[current.row][current.col + 1].col = current.col;
             }
             
         }
         
         
         
     }
    

        
    //backtrace
    while(visited[current.row][current.col])
    {
        maze[current.row][current.col] = '*';
        Location temp;
        temp.row = current.row;
        temp.col = current.col;
        current.row = predecessor[temp.row][temp.col].row;
        current.col = predecessor[temp.row][temp.col].col; 
    }
    
    //Deallocate Memory
     for (int i = 0; i<rows; i++) 
        {                           
            delete [] predecessor[i];
            delete [] visited[i];
        }
        
     delete [] predecessor;
     delete [] visited;
        
     return found_Finish;
    }
}

bool noLava(int x, int y, int row, int col){
 if (x < row && y < col && x>=0 && y>=0)
 {
     return true;   
 }
    
 else
     return false;
    
}
