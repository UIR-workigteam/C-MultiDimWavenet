#include "stdafx.h"
#pragma once

class Wavelet
{
	WaveletType type;

	float mhat_function(float inp);

	float morlet_function(float inp);

	float mhat_derivative(float inp);

	float morlet_derivative(float inp);

public:
	Wavelet();

	Wavelet(WaveletType type_id);

	MatrixXd function(MatrixXd inp, MatrixXd translation, MatrixXd dilation);

	MatrixXd derivative(MatrixXd inp, MatrixXd translation, MatrixXd dilation);
};

