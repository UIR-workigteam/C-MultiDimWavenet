#include "MultiD_Wavenet.h"
#include "stdafx.h"
#include <boost/tokenizer.hpp>
using namespace boost;

class Trainer
{
	MultiD_Wavenet current_wavenet;

public:
	Trainer::Trainer(MultiD_Wavenet target);
	list<MatrixXd> get_set(string adress);

};