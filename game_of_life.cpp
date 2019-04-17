
/*
Geoffrey Hughes
002306123
ghughes@chapman.edu
CPSC 350-02
Assignment 2: Game of Life
*/

/*
	This is the source file with the main function. 
	Not much else is done other than constructing user_input and map, and then
	printing and running the simulation until no longer necessary.
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "input.h"
#include "map.h"

using namespace std;


int main(int argc, char** argv) {


	cout << "Would you like to provide a map file, or would you like a random map?" << endl;
	
	string map_mode = "NONE";
	while (map_mode != "file" && map_mode != "random") {

		cout << "Enter [file] or [random]: ";

		cin >> map_mode;
	}

	// Prompt user for correct input depending on mode, and create generation 0 from it
	user_input the_user = user_input(map_mode);
	map the_map = map(the_user);


	// Continue printing map and map simulation with desired specifications as long as cells change (bool keep_going)
	while(the_map.get_keep_going()) {
	the_map.print_map();
	the_map.simulation();
	}

	cout << "Simulation has stabilized, press enter to exit . . . ";
	cin.get();


return 0;

}