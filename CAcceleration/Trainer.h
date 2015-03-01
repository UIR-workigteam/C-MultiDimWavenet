#include "MultiD_Wavenet.h"
#include "stdafx.h"
#include <boost/tokenizer.hpp>
using namespace boost;

class Trainer
{
	MultiD_Wavenet current_wavenet;
	vector<MatrixXd> sample_input, sample_target, validation_input, validation_target;

	list<MatrixXd> get_set(string adress);
public:
	Trainer::Trainer(MultiD_Wavenet target, string input, string output);
	void education_step(int position);
	float deviation();
	MultiD_Wavenet multiple_train(int epochs);
};