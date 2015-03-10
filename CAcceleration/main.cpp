#include "stdafx.h"
#include "Trainer.h"

int main()
{
	MultiD_Wavenet oldschool(2, 19, 1, Wavelet(MHAT));
	oldschool.dump_to_file("C:/Users/Zharov/test_network");
	oldschool.outswap();

	MultiD_Wavenet newschool("C:/Users/Zharov/test_network");
	newschool.outswap();
	//Wavelet wava(MHAT);
	//Trainer train("C:/Users/Zharov/inp_3.csv", "C:/Users/Zharov/outp_3.csv");
	//MultiD_Wavenet oldschool = train.multiple_train_with_exit(7, 60, 1, wava, 60, 5, 5);
	//oldschool.outswap();
	getchar();
	//for (float x = -4.0; x <= 4.0; x += 1.0)
	//{
	//	for (float y = -4.0; y <= 4.0; y += 1.0)
	//	{
	//		MatrixXd current_input(1, 2);
	//		current_input(0, 0) = x;
	//		current_input(0, 1) = y;
	//		cout << sin(2 * x)* cos(y) << " <> " << oldschool.forward(current_input) << endl;
	//	}
	//}
	//getchar();
}