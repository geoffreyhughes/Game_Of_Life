
/*
Geoffrey Hughes
002306123
ghughes@chapman.edu
CPSC 350-02
Assignment 2: Game of Life
*/

/*
	input.cpp prompts the user for any information the program will need to run.
	All information is then used to create the first generation of the map, and passes
	all of this to the map using the map(user_input) constructor. Basically, this class
	gathers all information needed for map to print and run each type of simulation.

*/



#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>

#include "input.h"
#include "map.h"


using namespace std;

/*
	Unused base constructor
*/
user_input::user_input() {

}

/*
	Constructor that takes in from game_of_life's main function which type of simulation
	is going to be run, and then gathers all required sequential input.
*/
user_input::user_input(string map_type_in) {

	// Get all user specifications
	map_type = map_type_in;

	if (map_type == "file") {
		input_file_map();
	}

	else {
		input_random_map();
	}

	input_mode_and_output();
}

/* 
	used to hold this code: delete[] gen0_map_matrix; 
	This is no longer necessary, as the dynamic bool** gets copied to map, and deleted with map's destructor.
	Was causing an error, as it tried to delete[] (free) the same memory twice.
*/
user_input::~user_input() {


}


/*
	input_file_map()
	If the user chooses to input the first generation from a file
*/
void user_input::input_file_map() {

	string dir = "";
	string file_name = "";
	string file_line = "";
	int file_rows = -1;
	int file_cols = -1;

	cout << "Please provide the file path: ";
	cin >> dir;


	// Truncate directory path to the file, must be in same location as main executable
	int index = dir.find_last_of("\\/");
	if (string::npos != index) {
		file_name = dir.substr(index + 1);
	}
	else {
		file_name = dir;
	}

	
	// Open file and create stream
	ifstream file_stream_map;
    file_stream_map.open(file_name);

    // Get # of rows
    file_stream_map >> file_line;
    file_rows = stoi(file_line);
    set_rows(file_rows);

    // Get # of columns
    file_stream_map >> file_line;
    file_cols = stoi(file_line);
    set_cols(file_cols);


    // Create Generation 0 map matrix from input file
    gen0_map_matrix = new bool* [get_rows()];
	for (int i = 0; i < get_rows(); ++i) {

		gen0_map_matrix[i] = new bool[get_cols()];
	}

	// Fill with input from file
	for (int i = 0; i < get_rows(); ++i) {

		file_stream_map >> file_line;

		for (int j = 0; j < file_line.size(); ++j) {

			if (file_line[j] == 'x' || file_line[j] == 'X') {
				gen0_map_matrix[i][j] = 1;
			}
			else {
				gen0_map_matrix[i][j] = 0;
			}
		}
	}

} // End of input_file_map()


/*
	input_random_map()
	If the user chooses randomize the map's first generation using parameters
*/
void user_input::input_random_map() {

	int r = -1;
	int c = -1;
	double density = 0.0;

	while (r <= 0) {
		cout << "Please input the number of world rows: ";
		cin >> r;
	}
	set_rows(r);

	while (c <= 0) {
		cout << "Please input the number of world columns: ";
		cin >> c;
	}
	set_cols(c);

	while (density <= 0 || density > 1) {
		cout << "Please input the world population density (0,1]: ";
		cin >> density;
	}
	set_map_density(density);


	// Create Generation 0 map matrix
    gen0_map_matrix = new bool* [get_rows()];
	for (int i = 0; i < get_rows(); ++i) {

		gen0_map_matrix[i] = new bool[get_cols()];
	}

	
	// Fill Generation 0 randomly using dimension and density inputs
	int temp_a = rand();
	double random_double = 0.0;
	for (int i = 0; i < get_rows(); ++i) {
		for (int j = 0; j < get_cols(); ++j) {

			random_double = (double)rand() / RAND_MAX;

			if (random_double <= get_map_density()) {
				gen0_map_matrix[i][j] = 1;
			}
			else {
				gen0_map_matrix[i][j] = 0;
			}
		}
	}

} // End of input_random_map()


/*
	input_mode_and_output()
	Gathers information for the map class, which mode to run in, and how to output each simulation
*/
void user_input::input_mode_and_output() {

	// Input type of boundary mode to operate in
	cout << "What boundary mode would you like to run in?" << endl;
	string temp_answer =  "";

	while (temp_answer != "classic" && temp_answer != "doughnut" && temp_answer != "mirror") {

		cout << "Enter [classic], [doughnut], or [mirror]: ";	
		cin >> temp_answer;
	}
	set_mode(temp_answer);	


	// Input type of output format
	cout << "What format of output would you like?" << endl;
	cout << "A brief pause between generations, press the enter key, or output to a file?" << endl;

	while (temp_answer != "pause" && temp_answer != "enter" && temp_answer != "file") {
		
		cout << "Enter [pause], [enter], or [file]: ";
		cin >> temp_answer;
	}
	set_PEO(temp_answer);

	// Create custom output file if that is the output mode
	if (get_PEO() == "file") {

		cout << "What would you like to name your output file? (____.out): ";
		cin >> temp_answer;

		ofstream FILE_ostream (temp_answer);
		FILE_ostream.close();

		set_output_file(temp_answer);
	}

} // End of input_mode_and_output()



void user_input::set_mode(string m) {
	this->map_mode = m;
}

void user_input::set_PEO(string peo) {
	this->pause_enter_output = peo;
}

void user_input::set_output_file(string out) {
	this->output_file = out;
}

void user_input::set_rows(int r) {
	this->rows = r;
}

void user_input::set_cols(int c) {
	this->cols = c;
}

void user_input::set_map_density(double d) {
	this->map_density = d;
}

void user_input::set_gen0(bool** gen0) {
	this->gen0_map_matrix = gen0;
}




string user_input::get_mode() {
	return map_mode;
}

string user_input::get_PEO() {
	return pause_enter_output;
}

string user_input::get_output_file() {
	return output_file;
}

int user_input::get_rows() {
	return rows;
}

int user_input::get_cols() {
	return cols;
}

double user_input::get_map_density() {
	return map_density;
}

bool** user_input::get_gen0() {
	return gen0_map_matrix;
}



