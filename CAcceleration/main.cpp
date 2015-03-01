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
	MultiD_Wavenet new_wave(2, 19, 1, wava);
	new_wave.outswap();
	Trainer train(new_wave, "C:/Users/Zharov/inp.csv", "C:/Users/Zharov/outp.csv");
	MultiD_Wavenet oldschool = train.multiple_train(60);
	oldschool.outswap();
	getchar();
}