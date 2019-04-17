Geoffrey Hughes
002306123
ghughes@chapman.edu
CPSC 350-02
Assignment 2: Game of Life


Source Files:

game_of_life.cpp
input.cpp
map.cpp


Notes:

I understood the part about a simulation “stabilizing” as no new cells are created - i.e. no change. So infinite simulations include ones that iterate back and forth between two states. I thought this made sense because new cells are created and destroyed in these infinite simulations. All cells have not “stabilized”.

Also I did not write comments for the getter and setter functions, as I feel those are pretty self-explanatory.


References used:

splitting directories:
https://stackoverflow.com/questions/11521914/splitting-a-c-string-with

press enter to continue:
https://www.youtube.com/watch?v=yTk33AlatIw

Understanding exit() function:
http://www.cplusplus.com/reference/cstdlib/exit/

How to make a Makefile:
https://www.youtube.com/watch?v=aw9wHbFTnAQ


Running the Assignment:

1. Unzip submitted compression file
2. Make sure any files you want to use as input are placed in the same directory
3. Navigate to said directory with Makefile, and all source files and header files
4. While in the directory with Makefile, type ‘make’
5. Run the newly made executable GameOfLife

