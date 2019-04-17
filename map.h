
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>


#include "input.h"

using namespace std;

class map {


public:

	map();
	map(user_input my_input);
	map(const map &map_a);
	~map();

	void simulation();
	void print_map();

	void set_mode(string m);
	void set_PEO(string peo);
	void set_output_file(string out);
	void set_gen(int g);
	void set_rows(int r);
	void set_cols(int c);
	void set_map_matrix(bool** m);
	void set_next_matrix(bool** nm);

	void set_keep_going(bool k);

	string get_mode();
	string get_PEO();
	string get_output_file();
	int get_gen();
	int get_rows();
	int get_cols();
	bool** get_map_matrix();	
	bool** get_next_matrix();

	bool get_keep_going();


private:

	string map_mode;
	string pause_enter_output;
	string output_file;

	int generation;
	int rows;
	int cols;

	bool** map_matrix;
	bool** next_matrix;

	bool keep_going;


};




//MAP_H
#endif 