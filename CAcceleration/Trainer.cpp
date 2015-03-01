#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator

#include "MultiD_Wavenet.h"
#include "Trainer.h"

#define validation_split 0.75

Trainer::Trainer(MultiD_Wavenet trainee, string input, string output)
{
	current_wavenet = trainee;
	list<MatrixXd> tmp_input = get_set(input);
	list<MatrixXd> tmp_target = get_set(output);
	list<MatrixXd> tmp_validation_input, tmp_validation_target;
	int current_size = tmp_input.size();

	list<MatrixXd>::iterator tmp_iterator = tmp_input.begin();
	advance(tmp_iterator, (int)(current_size*validation_split));
	tmp_validation_input.splice(tmp_validation_input.begin(), tmp_input, tmp_iterator, tmp_input.end());

	tmp_iterator = tmp_target.begin();
	advance(tmp_iterator, (int)(current_size*validation_split));
	tmp_validation_target.splice(tmp_validation_target.begin(), tmp_target, tmp_iterator, tmp_target.end());

	sample_input = vector<MatrixXd> { make_move_iterator(begin(tmp_input)), make_move_iterator(end(tmp_input)) };
	sample_target = vector<MatrixXd> { make_move_iterator(begin(tmp_target)), make_move_iterator(end(tmp_target)) };
	validation_input = vector<MatrixXd> { make_move_iterator(begin(tmp_validation_input)), make_move_iterator(end(tmp_validation_input)) };
	validation_target = vector<MatrixXd> { make_move_iterator(begin(tmp_validation_target)), make_move_iterator(end(tmp_validation_target)) };
}

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
		return_list.push_back(current_matrix);
	}
	
	return return_list;
}

void Trainer::education_step(int position)
{
	MatrixXd current_result = current_wavenet.forward(sample_input[position]);
	MatrixXd current_error = sample_target[position] - current_result;
	current_wavenet.backward(sample_input[position], current_result, sample_target[position]);
}

float Trainer::deviation()
{
	float error_sum = 0.0;
	int validation_len = validation_input.size();
	for (int i = 0; i < validation_len; i++)
	{
		MatrixXd current_result = current_wavenet.forward(validation_input[i]);
		error_sum += abs((current_result - validation_target[i]).mean());
		//cout << current_result << endl << validation_target[i] << endl << endl;
	}
	return error_sum / (float)validation_len;
}

MultiD_Wavenet Trainer::multiple_train(int epochs)
{
	int sample_len = sample_input.size();
	MatrixXd local_result;
	vector<int> numeration_vector;
	for (int i = 0; i < sample_len; i++)
	{
		numeration_vector.push_back(i);
	}

	for (int i = 0; i < epochs; i++)
	{
		random_shuffle(numeration_vector.begin(), numeration_vector.end());
		for (int j = 0; j < sample_len; j++)
		{
			local_result = current_wavenet.forward(sample_input[numeration_vector[j]]);
			current_wavenet.backward(sample_input[numeration_vector[j]], local_result, sample_target[numeration_vector[j]]);
		}
		cout << deviation() << endl;
	}
	return current_wavenet;
}