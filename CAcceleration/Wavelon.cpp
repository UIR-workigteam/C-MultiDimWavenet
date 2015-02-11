#include "Wavelon.h"

float Wavelet::mhat_function(float inp)
{
	return (1.0 - inp * inp) * exp(-inp * inp / 2);
}

float Wavelet::morlet_function(float inp)
{
	return exp(-inp * inp / 2) * cos(5 * inp);
}

float Wavelet::mhat_derivative(float inp)
{
	return ((inp - 3.0) * exp(-inp / 2.0)) / 2.0;
}

float Wavelet::morlet_derivative(float inp)
{
	return -5.0 * exp(-inp*inp / 2.0) * sin(5.0 * inp) - inp*exp(-inp*inp / 2.0)*cos(5.0*inp);
}

Wavelet::Wavelet()
{
	type = MHAT;
}

Wavelet::Wavelet(WaveletType type_id)
{
	type = type_id;
}

MatrixXd Wavelet::function(MatrixXd inp, MatrixXd translation, MatrixXd dilation)
{
	MatrixXd new_matrix = MatrixXd::Zero(inp.rows(), inp.cols());
	switch (type)
	{
	case MHAT:
	{
				 for (int i = 0; i < inp.rows(); i++)
				 {
					 for (int j = 0; j < inp.cols(); j++)
					 {
						 new_matrix(i, j) = mhat_function((inp(i, j) - translation(i, j)) / dilation(i, j));
					 }
				 }
	}
	case MORLET:
	{
				   for (int i = 0; i < inp.rows(); i++)
				   {
					   for (int j = 0; j < inp.cols(); j++)
					   {
						   new_matrix(i, j) = morlet_function((inp(i, j) - translation(i, j)) / dilation(i, j));
					   }
				   }
	}
	}
	return new_matrix;
}

MatrixXd Wavelet::derivative(MatrixXd inp, MatrixXd translation, MatrixXd dilation)
{
	MatrixXd new_matrix = MatrixXd::Zero(inp.rows(), inp.cols());
	switch (type)
	{
	case MHAT:
	{
				 for (int i = 0; i < inp.rows(); i++)
				 {
					 for (int j = 0; j < inp.cols(); j++)
					 {
						 new_matrix(i, j) = mhat_derivative((inp(i, j) - translation(i, j)) / dilation(i, j));
					 }
				 }
	}
	case MORLET:
	{
				   for (int i = 0; i < inp.rows(); i++)
				   {
					   for (int j = 0; j < inp.cols(); j++)
					   {
						   new_matrix(i, j) = morlet_derivative((inp(i, j) - translation(i, j)) / dilation(i, j));
					   }
				   }
	}
	}
	return new_matrix;
}
