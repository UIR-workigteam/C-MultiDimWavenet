#include "stdafx.h"
#include "Wavelon.h"
#include <boost/tokenizer.hpp>
using namespace boost;
#pragma once

class MultiD_Wavenet
{
	network_state current_state, previous_state;

	list<network_state> history;

	int inp, hid, out;

	Wavelet motherfunction;

	MatrixXd construct_random_matrix(int nrows, int ncols, double min, double maxi);

	MatrixXd diagonalize(MatrixXd row);

	MatrixXd row_multiplier(MatrixXd mat);

	MatrixXd col_summer(MatrixXd mat);

	MatrixXd replace_multiple(MatrixXd from, MatrixXd to);

	MatrixXd make_mu(MatrixXd curmu);

	MatrixXd make_uu(MatrixXd input);

	network_state one_step(network_state previous, network_state current, network_state derivatives);

public:
	MatrixXd forward(MatrixXd input);

	void backward(MatrixXd input, MatrixXd output, MatrixXd target);

	MultiD_Wavenet();

	MultiD_Wavenet(int inpt, int hidi, int outp, Wavelet mtf);

	void outswap(void);

	void dump_to_file(string addr);

	MultiD_Wavenet(string addr);
};