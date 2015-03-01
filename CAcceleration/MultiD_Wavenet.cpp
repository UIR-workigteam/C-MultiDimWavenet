// CAcceleration.cpp : Defines the entry point for the console application.
//
#include "Wavelon.h"
#include "MultiD_Wavenet.h"
#include <time.h>

void current_custom_logger(MatrixXd target)
{
	cout << "Watchdog. Bow-Wow!" << endl;
	cout << target << endl;
}


MatrixXd MultiD_Wavenet::construct_random_matrix(int nrows, int ncols, double min, double maxi)
{

	MatrixXd aux(nrows, ncols);
	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
		{
			aux(i, j) = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxi - min)));
		}
	}
	return aux;
}

MatrixXd MultiD_Wavenet::diagonalize(MatrixXd row)
{
	if (row.rows() == 1)
	{
		int cols = row.cols();
		MatrixXd aux = MatrixXd::Zero(cols, cols);
		for (int i = 0; i < cols; i++)
		{
			aux(i, i) = row(0, i);
		}
		return aux;
	}
}

MatrixXd MultiD_Wavenet::row_multiplier(MatrixXd mat)
{
	MatrixXd aux = MatrixXd::Zero(1, mat.cols());
	for (int i = 0; i < mat.cols(); i++)
	{
		aux(0, i) = mat.col(i).prod();
	}
	return aux;
}

MatrixXd MultiD_Wavenet::col_summer(MatrixXd mat)
{
	MatrixXd aux = MatrixXd::Zero(mat.rows(), 1);
	for (int i = 0; i < mat.rows(); i++)
	{
		aux(i, 0) = mat.row(i).sum();
	}
	return aux;
}

MatrixXd MultiD_Wavenet::replace_multiple(MatrixXd from, MatrixXd to)
{
	MatrixXd aux = MatrixXd::Zero(from.rows(), from.cols());
	MatrixXd result = MatrixXd::Zero(from.rows(), from.cols());
	for (int i = 0; i < from.rows(); i++)
	{
		aux = to;
		aux.row(i) = from.row(i);
		result.row(i) = row_multiplier(aux).row(0);
	}
	return result;
}

MatrixXd MultiD_Wavenet::make_mu(MatrixXd curmu)
{
	MatrixXd result = MatrixXd::Zero(inp, curmu.rows());
	MatrixXd new_mu = col_summer(curmu).transpose();
	for (int i = 0; i < result.rows(); i++)
	{
		result.row(i) = new_mu.row(0);
	}
	return result;
}

MatrixXd MultiD_Wavenet::make_uu(MatrixXd input)
{
	MatrixXd result = MatrixXd::Zero(inp, hid);
	for (int i = 0; i < result.cols(); i++)
	{
		result.col(i) = input.row(0).transpose();
	}
	return result;
}

network_state MultiD_Wavenet::one_step(network_state previous, network_state current, network_state derivatives)
{
	network_state result;
	result.Lambda = current.Lambda + derivatives.Lambda * etta + (current.Lambda - previous.Lambda) * etta;
	//current_custom_logger(current.Lambda + derivatives.Lambda * etta);
	//current_custom_logger(result.Lambda);
	//current_custom_logger((current.Lambda - previous.Lambda) * etta);
	result.Mu = current.Mu + derivatives.Mu * etta + (current.Mu - previous.Mu) * etta;
	result.Omega = current.Omega + derivatives.Omega * etta + (current.Omega - previous.Omega) * etta;
	result.T = current.T + derivatives.T * etta + (current.T - previous.T) * etta;
	result.Hi = current.Hi + derivatives.Hi * etta + (current.Hi - previous.Hi) * etta;
	//current_custom_logger(current.Hi);
	//current_custom_logger(derivatives.Hi * etta);
	return result;
}

MatrixXd MultiD_Wavenet::forward(MatrixXd input)
{
	return row_multiplier(motherfunction.function(diagonalize(input) * current_state.Omega, current_state.T, current_state.Lambda)) * current_state.Mu + current_state.Hi;
}

void MultiD_Wavenet::backward(MatrixXd input, MatrixXd output, MatrixXd target)
{
	network_state derivatives;
	MatrixXd current_coefficient = diagonalize(input) * current_state.Omega;
	MatrixXd Z = motherfunction.function(current_coefficient, current_state.T, current_state.Lambda);
	MatrixXd dZ = motherfunction.derivative(diagonalize(input) * current_state.Omega, current_state.T, current_state.Lambda);
	MatrixXd Err = target - output;
	MatrixXd md = replace_multiple(dZ, Z);
	MatrixXd qm = row_multiplier(Z).transpose();
	MatrixXd mm = make_mu(current_state.Mu * Err.transpose());
	MatrixXd uu = make_uu(input);


	derivatives.Omega = md % mm % uu / current_state.Lambda;
	derivatives.T = -1 * md % mm % current_state.T / current_state.Lambda;
	derivatives.Lambda = -1 * md % mm % (current_coefficient - current_state.T) / current_state.Lambda;
	derivatives.Mu = qm * Err;
	derivatives.Hi = Err;

	network_state new_state = one_step(previous_state, current_state, derivatives);
	previous_state = current_state;
	current_state = new_state;
}

MultiD_Wavenet::MultiD_Wavenet(int inpt, int hidi, int outp, Wavelet mtf)
{
	srand(static_cast <unsigned> (time(0)));
	motherfunction = mtf;
	inp = inpt;
	hid = hidi;
	out = outp;
	current_state.Omega = construct_random_matrix(inp, hid, 0.0, 1.0);
	current_state.T = construct_random_matrix(inp, hid, 0.0, 1.0);
	current_state.Lambda = construct_random_matrix(inp, hid, 0.01, 1.0);
	current_state.Mu = construct_random_matrix(hid, out, 0.0, 1.0);
	current_state.Hi = construct_random_matrix(1, out, 0.0, 1.0);
	previous_state = current_state;
}

void MultiD_Wavenet::outswap(void)
{
	cout << inp << ';' << hid << ';' << out << std::endl;
	cout << current_state.Omega << '\n' << '\n' << current_state.T << '\n' << '\n' << current_state.Lambda << '\n' << '\n' << current_state.Mu << '\n' << '\n' << current_state.Hi << std::endl;
}

MultiD_Wavenet::MultiD_Wavenet()
{
	MultiD_Wavenet(2, 3, 1, Wavelet());
}
