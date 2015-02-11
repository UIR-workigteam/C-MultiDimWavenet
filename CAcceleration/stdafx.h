// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Eigen/Dense>

typedef enum { MHAT, MORLET } WaveletType;

using Eigen::MatrixXd;

struct network_state{
	MatrixXd Mu, Omega, Hi, T, Lambda;
	float mse = 0.0;
};

using namespace std;

#define etta 0.01

MatrixXd operator%(MatrixXd a, MatrixXd b)
{
	MatrixXd result = MatrixXd::Zero(a.rows(), a.cols());
	for (int i = 0; i < a.rows(); i++)
	{
		for (int j = 0; j < a.cols(); j++)
		{
			result(i, j) = a(i, j) * b(i, j);
		}
	}
	return result;
}

MatrixXd operator/(MatrixXd a, MatrixXd b)
{
	MatrixXd result = MatrixXd::Zero(a.rows(), a.cols());
	for (int i = 0; i < a.rows(); i++)
	{
		for (int j = 0; j < a.cols(); j++)
		{
			result(i, j) = a(i, j) / b(i, j);
		}
	}
	return result;
}

// TODO: reference additional headers your program requires here
