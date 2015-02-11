// stdafx.cpp : source file that includes just the standard includes
// CAcceleration.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
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

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
