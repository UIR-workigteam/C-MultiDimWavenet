// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <iostream>
#include <stdio.h>
#include <Eigen/Dense>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

typedef enum { MHAT, MORLET } WaveletType;

using Eigen::MatrixXd;
using namespace std;
#define etta 0.01

struct network_state{
	MatrixXd Mu, Omega, Hi, T, Lambda;
	float mse = 0.0;
};

MatrixXd operator%(MatrixXd a, MatrixXd b);

MatrixXd operator/(MatrixXd a, MatrixXd b);

// TODO: reference additional headers your program requires here
