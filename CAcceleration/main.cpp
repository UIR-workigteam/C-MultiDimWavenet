#include "stdafx.h"
#include "Trainer.h"

int main()
{
	//list<int> list1, list2;
	//list<int>::iterator iterato;
	//
	//for (int i = 1; i <= 10; ++i)
	//	list1.push_back(i);

	//iterato = list1.begin();
	//advance(iterato, 6);

	//list2.splice(list2.begin(), list1, iterato, list1.end());

	//std::cout << "mylist1 contains:";
	//for (iterato = list1.begin(); iterato != list1.end(); ++iterato)
	//	std::cout << ' ' << *iterato;
	//std::cout << '\n';

	//std::cout << "mylist2 contains:";
	//for (iterato = list2.begin(); iterato != list2.end(); ++iterato)
	//	std::cout << ' ' << *iterato;
	//std::cout << '\n';
	//getchar();

	Wavelet wava(MHAT);
	Trainer train("C:/Users/Zharov/inp_3.csv", "C:/Users/Zharov/outp_3.csv");
	MultiD_Wavenet oldschool = train.multiple_train_with_exit(7, 60, 1, wava, 60, 5, 5);
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