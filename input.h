
#ifndef INPUT_H
#define INPUT_H


#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>


using namespace std;

class user_input {

	public:

		user_input();
		user_input(string map_type);
		~user_input();

		void input_file_map();
		void input_random_map();
		void input_mode_and_output();

		void set_mode(string m);
		void set_PEO(string peo);
		void set_output_file(string out);
		void set_rows(int r);
		void set_cols(int c);
		void set_map_density(double d);
		void set_gen0(bool** gen0);

		string get_mode();
		string get_PEO();
		string get_output_file();
		int get_rows();
		int get_cols();
		double get_map_density();
		bool** get_gen0();



	private:

		string map_type;

		string map_mode;
		string pause_enter_output;
		string output_file;

		
		int rows;
		int cols;
		double map_density;

		bool** gen0_map_matrix;

};



//INPUT_H
#endif 
