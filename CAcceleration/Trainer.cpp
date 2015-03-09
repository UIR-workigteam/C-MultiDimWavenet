#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator

#include "MultiD_Wavenet.h"
#include "Trainer.h"

#define validation_split 0.75

Trainer::Trainer(string input, string output)
{
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

void Trainer::education_step(MultiD_Wavenet target, int position)
{
	MatrixXd current_result = target.forward(sample_input[position]);
	MatrixXd current_error = sample_target[position] - current_result;
	target.backward(sample_input[position], current_result, sample_target[position]);
}

float Trainer::deviation(MultiD_Wavenet current_wavenet)
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

MultiD_Wavenet Trainer::multiple_train(MultiD_Wavenet target, int epochs, int critical_epochs, int aeras, int critical_aeras)
{
	MultiD_Wavenet current_wavenet = target;
	int sample_len = sample_input.size();
	MatrixXd local_result;
	vector<int> numeration_vector;
	for (int i = 0; i < sample_len; i++)
	{
		numeration_vector.push_back(i);
	}
	for (int k = 0; k < aeras; k++)
	{
		double current_error = numeric_limits<double>::max();
		double tmp_error = 0.0;
		int outgoing_counter = 0;
		for (int i = 0; i < epochs; i++)
		{
			random_shuffle(numeration_vector.begin(), numeration_vector.end());
			for (int j = 0; j < sample_len; j++)
			{
				local_result = current_wavenet.forward(sample_input[numeration_vector[j]]);
				current_wavenet.backward(sample_input[numeration_vector[j]], local_result, sample_target[numeration_vector[j]]);
			}
			tmp_error = deviation(current_wavenet);
			cout << tmp_error;
			if (tmp_error < current_error)
			{
				cout << "  continuation" << endl;
				outgoing_counter = 0;
				current_error = tmp_error;
			}
			else
			{
				cout << "  stagnation  ";
				cout << ++outgoing_counter << endl;
			}
			if (outgoing_counter >= critical_epochs)
				break;
		}
	}
	return current_wavenet;
}

MultiD_Wavenet Trainer::multiple_train_with_exit(int inp, int hid, int out, Wavelet motherfunction, int epochs, int critical_epochs, int aeras)
{
	int sample_len = sample_input.size();
	MatrixXd local_result;
	vector<int> numeration_vector;
	for (int i = 0; i < sample_len; i++)
	{
		numeration_vector.push_back(i);
	}
	MultiD_Wavenet global_minimum_network;
	double global_error = numeric_limits<double>::max();
	for (int k = 0; k < aeras; k++)
	{
		MultiD_Wavenet current_wavenet = MultiD_Wavenet(inp, hid, out, motherfunction);
		double current_error = numeric_limits<double>::max();
		double tmp_error = 0.0;
		int outgoing_counter = 0;
		for (int i = 0; i < epochs; i++)
		{
			random_shuffle(numeration_vector.begin(), numeration_vector.end());
			for (int j = 0; j < sample_len; j++)
			{
				local_result = current_wavenet.forward(sample_input[numeration_vector[j]]);
				current_wavenet.backward(sample_input[numeration_vector[j]], local_result, sample_target[numeration_vector[j]]);
			}
			tmp_error = deviation(current_wavenet);
			cout << tmp_error;
			if (tmp_error < current_error)
			{
				cout << "  continuation" << endl;
				outgoing_counter = 0;
				current_error = tmp_error;
			}
			else
			{
				cout << "  stagnation  ";
				cout << ++outgoing_counter << endl;
			}
			if (outgoing_counter >= critical_epochs)
			{
				if (current_error < global_error)
				{
					global_error = current_error;
					global_minimum_network = current_wavenet;
				}
				break;
			}
		}
		if (current_error < global_error)
		{
			global_error = current_error;
			global_minimum_network = current_wavenet;
		}
	}
	cout << "GE = " << global_error << endl;
	return global_minimum_network;
}