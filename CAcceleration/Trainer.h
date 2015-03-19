#include "MultiD_Wavenet.h"
#include "stdafx.h"
#include <boost/tokenizer.hpp>
using namespace boost;
#pragma once

class Trainer
{
	vector<MatrixXd> sample_input, sample_target, validation_input, validation_target;

	list<MatrixXd> get_set(string adress);
public:
	Trainer::Trainer(string input, string output);
	void example_comparison(MultiD_Wavenet current_wavenet);
	void education_step(MultiD_Wavenet target, int position);
	void chained_example_comparison(MultiD_Wavenet current_wavenet, int chain_count);
	float deviation(MultiD_Wavenet current_wavenet);
	MultiD_Wavenet multiple_train(MultiD_Wavenet target, int epochs, int ciritical_epochs, int aeras, int critical_aeras);
	MultiD_Wavenet multiple_train_with_exit(int inp, int hid, int out, Wavelet motherfunction, int epochs, int ciritical_epochs, int aeras);
	void collect_output(string output, MultiD_Wavenet trainee);
	void collect_output_chained(string output, MultiD_Wavenet trainee, int chain_factor);
};