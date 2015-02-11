#include "stdafx.h"
#include "Trainer.h"

int main()
{
	Wavelet W;
	MultiD_Wavenet S = MultiD_Wavenet(2, 7, 1, W);
	Trainer A = Trainer(S);

	list<MatrixXd> Q = A.get_set("up1.csv");
	
}