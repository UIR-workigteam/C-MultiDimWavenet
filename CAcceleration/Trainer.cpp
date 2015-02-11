#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator

#include "MultiD_Wavenet.h"
#include "Trainer.h"

list<MatrixXd> Trainer::get_set(string adress)
{
	string data(adress);
	ifstream in(data.c_str());

	typedef tokenizer< escaped_list_separator<char> > Tokenizer;

	vector< string > vec;
	string line;

	list<MatrixXd> return_list;

	while (getline(in, line))
	{
		Tokenizer tok(line);
		vec.assign(tok.begin(), tok.end());

		MatrixXd current_matrix(1, vec.size());
		for (int i = 0; i < vec.size(); i++)
		{
			current_matrix(0, i) = atof(vec[i].c_str());
		}
	}
	return return_list;
}