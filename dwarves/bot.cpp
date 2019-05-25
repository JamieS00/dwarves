

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;


bool isNextToATree(Dwarf & dwarf, int r, int c) 
{
    if (dwarf.look(r+1, c) == PINE_TREE) 
    {
      return true;
    }
    else if (dwarf.look(r-1, c) == PINE_TREE)
    {   
      return true;
    }

    else if (dwarf.look(r, c+1) == PINE_TREE)
    {
       return true;
    }

    else if (dwarf.look(r, c-1) == PINE_TREE)
    {
       return true;
    }

    else 
    {
      return false;
    }

}

/* onStart: 
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do 
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
}

/* onAction: 
A procedure called each time an idle dwarf is choosing 
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) 
{
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();

 
  if(isNextToATree(dwarf,r,c)==true)  // Look if there is a tree on the right from the dwarf
  {
    if (dwarf.look(r, c+1) == PINE_TREE) 
    {
    // If there is a pine , chop it
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(EAST);
      return;
    }

    //up
    else if (dwarf.look(r-1, c) == PINE_TREE)
    {
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(NORTH);
      return;
    }

    //left
    else if (dwarf.look(r, c-1) == PINE_TREE)
    {
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(WEST);
      return;
    }

    //down
    else if (dwarf.look(r+1, c) == PINE_TREE)
    {
      log << "Found a tree -- chop" << endl;
      dwarf.start_chop(SOUTH);
      return;
    }
  }
  else
  {
    bool findNextMove = true;

    while(findNextMove) //while its true
    {
      int rr = rand() % ROWS;
      int cc = rand() % COLS;
      bool hasAdjTrees = (dwarf.look(rr,cc+1) == PINE_TREE) ||(dwarf.look(rr,cc-1) == PINE_TREE ) || (dwarf.look(rr+1,cc) == PINE_TREE ) || (dwarf.look(rr-1,cc) == PINE_TREE );

      if(dwarf.look(rr,cc) == EMPTY && hasAdjTrees) 
      {
        findNextMove = false; //found next move
        log << "Walk to " << rr << " " << cc << endl;
        dwarf.start_walk(rr, cc);
        return;
      }

    }

  }

}

