
/*
Geoffrey Hughes
002306123
ghughes@chapman.edu
CPSC 350-02
Assignment 2: Game of Life
*/

/*
	map.cpp takes in all user input specifications gathered in input.cpp with a constructor
	and uses the generation 0 map to run the simulation() function
	and print out each generation in the correct convention using the print_map() function
	2 maps are active at any time, the bool** map_matrix and the bool** next_matrix
	next_matrix's cells change depending on the configuration of cells in map_matrix
	then map_matrix becomes next_matrix and the process is repeated until no longer necessary
*/




#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "input.h"
#include "map.h"

using namespace std;

/*
	Unused base constructor
*/
map::map() {

}

/*
	Map constructor that takes in user_input my_input so an appropriate map can be created
*/
map::map(user_input my_input) {

	// Establish map of generation 0 from user_input my_input
	map_mode = my_input.get_mode();
	pause_enter_output = my_input.get_PEO();
	output_file = my_input.get_output_file();

	generation = 0;
	rows = my_input.get_rows();
	cols = my_input.get_cols();


	map_matrix = new bool* [rows];
	for (int i = 0; i < rows; ++i) {

		map_matrix[i] = new bool[cols];
	}
	map_matrix = my_input.get_gen0();

	set_keep_going(1);
}

/*
	The map destructor deletes the only dynamically allocated memory, map_matrix
	and also deletes next_matrix, since they point to the same memory when the destructor
	is called
*/

map::~map() {

	delete[] map_matrix;
}

/*
	simulation()
	This is the meat of the program. Depending on user input, the map is changed
	by updating next_matrix depending on the current cells in map_matrix.
	This function does this by counting each cell's neighbors, and updating the cell
	for the next generation.
*/

void map::simulation() {

	int neighbors = 0;

	// Create next matrix
	next_matrix = new bool* [rows];
	for (int i = 0; i < rows; ++i) {

		next_matrix[i] = new bool[cols];
	}

	// Fill next matrix with values of current matrix
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			next_matrix[i][j] = map_matrix[i][j];
		}
	}

	// Check for Rene shenanigans
	if (rows <= 1) {
		cout << "Please enter a matrix at least 2x2" << endl;
		exit(0);
	}

		// map and next now have the same values, and different addresses
		// now we just have to change next using map's cells
		// then make map point to next, after checking for if the simulation is over


	// Classic Mode Simulation
	if (get_mode() == "classic") {


		// Mark neighbors for each cell using current matrix, and change next matrix
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {

				neighbors = 0;

				// Top row
				if (i == 0) {

					// Top left cell
					if (j == 0) {

						if (map_matrix[0][1] == 1) {
							++neighbors;
						}

						if (map_matrix[1][0] == 1) {
							++neighbors;
						}

						if (map_matrix[1][1] == 1) {
							++neighbors;
						}

					} // end of top left cell

					// Top right cell
					else if (j == cols - 1) {

						if (map_matrix[0][cols - 2] == 1) {
							++neighbors;
						}

						if (map_matrix[1][cols - 1] == 1) {
							++neighbors;
						}

						if (map_matrix[1][cols - 2] == 1) {
							++neighbors;
						}

					} // end of top right cell

					// Rest of top row
					else {

						if (map_matrix[i][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i][j+1] == 1) {
							++neighbors;
						}

						if (map_matrix[i+1][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i+1][j] == 1) {
							++neighbors;
						}

						if (map_matrix[i+1][j+1] == 1) {
							++neighbors;
						}

					} // end of the rest of top row

				} // end of entire top row


				// Bottom row
				else if (i == rows - 1) {

					// Bottom left cell
					if (j == 0) {

						if (map_matrix[rows-2][0] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-2][1] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][1] == 1) {
							++neighbors;
						}

					} // end of bottom left cell

					// Bottom right cell
					else if (j == cols - 1) {

						if (map_matrix[rows-2][cols-1] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-2][cols-2] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][cols-2] == 1) {
							++neighbors;
						}

					} // end of bottom right cell

					// Rest of bottom row
					else {

						if (map_matrix[i][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i][j+1] == 1) {
							++neighbors;
						}

						if (map_matrix[i-1][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i-1][j] == 1) {
							++neighbors;
						}

						if (map_matrix[i-1][j+1] == 1) {
							++neighbors;
						}

					} // end of the rest of bottom row

				} // end of entire bottom row

				// Left side
				else if (j == 0) {

					if (map_matrix[i-1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j+1] == 1) {
						++neighbors;
					}

				} // end of left side

				// Right side
				else if (j == cols - 1) {

					if (map_matrix[i-1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j-1] == 1) {
						++neighbors;
					}

				} // end of right side

				// Fill in middle
				else {

					if (map_matrix[i-1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j+1] == 1) {
						++neighbors;
					}
					
				} // end of filling middle


				// Make change to the cell, depending on its neighbors counted above
				if (neighbors <= 1) {
					next_matrix[i][j] = 0;
				}

				else if (neighbors == 2) {
					next_matrix[i][j] = map_matrix[i][j];
				}

				else if (neighbors == 3) {
					next_matrix[i][j] = 1;
				}

				else if (neighbors >= 4) {
					next_matrix[i][j] = 0;
				}

			} // end of inner for loop [j]
		} // end of outer for loop [i]

	} // end of map_mode == "classic"


	// Doughnut Mode Simulation
	else if (get_mode() == "doughnut") {

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {

				neighbors = 0;

				// Top row
				if (i == 0) {

					// Top left cell
					if (j == 0) {

						// 3 direct Neighbors 
						if (map_matrix[0][1] == 1) {
							++neighbors;
						}

						if (map_matrix[1][0] == 1) {
							++neighbors;
						}

						if (map_matrix[1][1] == 1) {
							++neighbors;
						}

						// 1 doughnut corner Neighbor
						if (map_matrix[rows-1][cols-1] == 1) {
							++neighbors;
						}

						// 4 doughnut side Neighbor
						if (map_matrix[rows-1][0] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][1] == 1) {
							++neighbors;
						}

						if (map_matrix[0][cols-1] == 1) {
							++neighbors;
						}

						if (map_matrix[1][cols-1] == 1) {
							++neighbors;
						}

					} // end of top left cell

					// Top right cell
					else if (j == cols - 1) {

						// 3 direct Neighbors 
						if (map_matrix[0][cols-2] == 1) {
							++neighbors;
						}

						if (map_matrix[1][cols-2] == 1) {
							++neighbors;
						}

						if (map_matrix[1][cols-1] == 1) {
							++neighbors;
						}

						// 1 doughnut corner Neighbor
						if (map_matrix[rows-1][0] == 1) {
							++neighbors;
						}

						// 4 doughnut side Neighbor
						if (map_matrix[0][0] == 1) {
							++neighbors;
						}

						if (map_matrix[1][0] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][cols-1] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][cols-2] == 1) {
							++neighbors;
						}

					} // end of top right cell

					// Rest of top row
					else {

						if (map_matrix[i][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i][j+1] == 1) {
							++neighbors;
						}

						if (map_matrix[i+1][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i+1][j] == 1) {
							++neighbors;
						}

						if (map_matrix[i+1][j+1] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][j] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][j+1] == 1) {
							++neighbors;
						}

					} // end of rest of top row

				} // end of entire top row



				// Bottom row
				else if (i == rows - 1) {

					// Bottom left cell
					if (j == 0) {

						// 3 direct Neighbors
						if (map_matrix[i-1][0] == 1) {
							++neighbors;
						}

						if (map_matrix[i-1][1] == 1) {
							++neighbors;
						}

						if (map_matrix[i][1] == 1) {
							++neighbors;
						}

						// 1 doughnut corner neighbor
						if (map_matrix[0][cols-1] == 1) {
							++neighbors;
						}

						// 4 side doughnut neighbors
						if (map_matrix[0][0] == 1) {
							++neighbors;
						}

						if (map_matrix[0][1] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][cols-1] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-2][cols-1] == 1) {
							++neighbors;
						}
					} // end of bottom left cell

					// Bottom right cell
					else if (j == cols - 1) {

						// 3 direct Neighbors
						if (map_matrix[rows-1][cols-2] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-2][cols-1] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-2][cols-2] == 1) {
							++neighbors;
						}

						// 1 doughnut corner neighbor
						if (map_matrix[0][0] == 1) {
							++neighbors;
						}

						// 4 doughnut side neighbors
						if (map_matrix[0][cols-1] == 1) {
							++neighbors;
						}

						if (map_matrix[0][cols-2] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-1][0] == 1) {
							++neighbors;
						}

						if (map_matrix[rows-2][0] == 1) {
							++neighbors;
						}

					} // end of bottom right cell

					// Rest of bottom row
					else {

						if (map_matrix[i][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i][j+1] == 1) {
							++neighbors;
						}

						if (map_matrix[i-1][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i-1][j] == 1) {
							++neighbors;
						}

						if (map_matrix[i-1][j+1] == 1) {
							++neighbors;
						}

						if (map_matrix[0][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[0][j] == 1) {
							++neighbors;
						}

						if (map_matrix[0][j+1] == 1) {
							++neighbors;
						}


					} // end of the rest of bottom row

				} // end of entire bottom row

				// Left side
				else if (j == 0) {

					if (map_matrix[i-1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][cols-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][cols-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][cols-1] == 1) {
						++neighbors;
					}
				} // end of left side

				// Right side
				else if (j == cols - 1) {

					if (map_matrix[i-1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][0] == 1) {
						++neighbors;
					}

					if (map_matrix[i][0] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][0] == 1) {
						++neighbors;
					}

				} // end of right side

				// Middle nodes
				else {

					if (map_matrix[i-1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j+1] == 1) {
						++neighbors;
					}

				} // end of filling middle


				// Make change to the cell, depending on its neighbors counted above
				if (neighbors <= 1) {
					next_matrix[i][j] = 0;
				}

				else if (neighbors == 2) {
					next_matrix[i][j] = map_matrix[i][j];
				}

				else if (neighbors == 3) {
					next_matrix[i][j] = 1;
				}

				else if (neighbors >= 4) {
					next_matrix[i][j] = 0;
				}

			} // end of inner loop [j]
		} // end of outer loop [i]

	} // end of map_mode == "doughnut"


	// Mirror Mode Simulation
	else if (get_mode() == "mirror") {

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {

				neighbors = 0;

				// Top row
				if (i == 0) {

					// Top left cell
					if (j == 0) {

						if (map_matrix[i][j] == 1) {
							neighbors += 3;
						}

						if (map_matrix[0][1] == 1) {
							neighbors += 2;
						}

						if (map_matrix[1][0] == 1) {
							neighbors += 2;
						}

						if (map_matrix[1][1] == 1) {
							++neighbors;
						}

					} // end of top left cell

					// Top right cell
					else if (j == cols - 1) {

						if (map_matrix[i][j] == 1) {
							neighbors += 3;
						}

						if (map_matrix[i][j-1] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i+1][j] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i+1][j-1] == 1) {
							++neighbors;
						}

					} // end of top right cell

					// Rest of top
					else {

						if (map_matrix[i][j] == 1) {
							++neighbors;
						}

						if (map_matrix[i][j-1] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i][j+1] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i+1][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i+1][j] == 1) {
							++neighbors;
						}

						if (map_matrix[i+1][j+1] == 1) {
							++neighbors;
						}

					} // end of the rest of top row

				} // end of top row

				// Bottom row
				else if (i == rows - 1) {

					// Bottom left cell
					if (j == 0) {

						if (map_matrix[i][j] == 1) {
							neighbors += 3;
						}

						if (map_matrix[i-1][0] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i][j+1] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i-1][j+1] == 1) {
							++neighbors;
						}
					} // end of bottom left cell

					// Bottom right cell
					else if (j == cols - 1) {

						if (map_matrix[i][j] == 1) {
							neighbors += 3;
						}

						if (map_matrix[i-1][j] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i][j-1] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i-1][j-1] == 1) {
							++neighbors;
						}
					} // end of bottom right cell

					// Rest of bottom row
					else {

						if (map_matrix[i][j] == 1) {
							++neighbors;
						}

						if (map_matrix[i][j-1] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i][j+1] == 1) {
							neighbors += 2;
						}

						if (map_matrix[i-1][j-1] == 1) {
							++neighbors;
						}

						if (map_matrix[i-1][j] == 1) {
							++neighbors;
						}

						if (map_matrix[i-1][j+1] == 1) {
							++neighbors;
						}
					} // end of the rest of bottom row

				} // end of bottom row

				// Fill in left side
				else if (j == 0) {

					if (map_matrix[i][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j] == 1) {
						neighbors += 2;
					}

					if (map_matrix[i+1][j] == 1) {
						neighbors += 2;
					}

					if (map_matrix[i-1][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j+1] == 1) {
						++neighbors;
					}
				} // end of left side

				// Fill in right side
				else if (j == cols - 1) {

					if (map_matrix[i][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j] == 1) {
						neighbors += 2;
					}

					if (map_matrix[i+1][j] == 1) {
						neighbors += 2;
					}

					if (map_matrix[i-1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j-1] == 1) {
						++neighbors;
					}
				} // end of right side

				// Fill in middle
				else {

					if (map_matrix[i-1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i-1][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i][j+1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j-1] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j] == 1) {
						++neighbors;
					}

					if (map_matrix[i+1][j+1] == 1) {
						++neighbors;
					}
				} // end of filling middle

				// Make change to the cell, depending on its neighbors counted above
				if (neighbors <= 1) {
					next_matrix[i][j] = 0;
				}

				else if (neighbors == 2) {
					next_matrix[i][j] = map_matrix[i][j];
				}

				else if (neighbors == 3) {
					next_matrix[i][j] = 1;
				}

				else if (neighbors >= 4) {
					next_matrix[i][j] = 0;
				}



			} // end of inner j loop
		} // end of outer i loop

	} // end of map_mode == "mirror"

	// DONE with changes to next_matrix! ! !


	// Check for a finished simulation. If finished, set keep_going to FALSE (0)
	int check_no_change = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (next_matrix[i][j] == map_matrix[i][j]) {
				++check_no_change;
			}
		}
	}
	if (check_no_change == (rows * cols)) {
		set_keep_going(0);
	}

	// Incriment generation, 
	// and make the current map (map_matrix) point to the next generation (next_matrix)
	map_matrix = next_matrix;
	generation++;

}

/*
	print_map()
	Prints either to cout or to a file,
	depending on what user_input passed to the map constructor.
*/

void map::print_map() {

	// Pause print; waits 1 second between cout
	if (get_PEO() == "pause") {
		sleep(1);
		cout << get_gen() << endl;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {

				if (map_matrix[i][j] == 1) {
					cout << "X";
				}
				else {
				cout << "-";
				}
			}
			cout << endl;
		}
	} // End of [pause] print

	// Enter print; waits for user to press enter for next iteration
	else if (get_PEO() == "enter") {

		cout << get_gen() << endl;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {

				if (map_matrix[i][j] == 1) {
					cout << "X";
				}
				else {
				cout << "-";
				}
			}
			cout << endl;
		}
		if (generation == 0) {
			cin.ignore();
		}
		cin.get();

	} // End of [enter] print

	// File print; creates output file stream to the previously created and named file
	else if (get_PEO() == "file") {

		ofstream map_ostream;
    	map_ostream.open(get_output_file(), ios_base::app);

    	map_ostream << get_gen() << endl;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {

				if (map_matrix[i][j] == 1) {
					map_ostream << "X";
				}
				else {
				map_ostream << "-";
				}
			}
			map_ostream << endl;
		}

		map_ostream.close();


	} // End of [file] print

	else {
		cout << "invalid print mode" << endl;
	}

} // End of print

void map::set_mode(string m) {
	this->map_mode = m;
}

void map::set_PEO(string peo) {
	this->pause_enter_output = peo;
}

void map::set_output_file(string out) {
	this->output_file = out;
}

void map::set_gen(int g) {
	this->generation = g;
}

void map::set_rows(int r) {
	this->rows = r;
}

void map::set_cols(int c) {
	this->cols = c;
}

void map::set_map_matrix(bool** m) {
	this->map_matrix = m;
}

void map::set_next_matrix(bool** nm) {
	this->next_matrix = nm;
}

void map::set_keep_going(bool k) {
	this->keep_going = k;
}


string map::get_mode() {
	return map_mode;
}

string map::get_PEO() {
	return pause_enter_output;
}

string map::get_output_file() {
	return output_file;
}

int map::get_gen() {
	return generation;
}

int map::get_rows() {
	return rows;
}

int map::get_cols() {
	return cols;
}

bool** map::get_map_matrix() {
	return map_matrix;
}

bool** map::get_next_matrix() {
	return next_matrix;
}

bool map::get_keep_going() {
	return keep_going;
}




