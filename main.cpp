//
//  main.cpp
//  BalayProject
//
//  Created by Denis Genalitskiy on 03.03.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//

#include <iostream>
#include <bitset>
#include <math.h>
#include "FileReader.h"
#include <stdlib.h>
#include <time.h>
#include "MoveToFrontList.h"
#include <memory>
#include "OrderedMoveToFront.h"
#include "Ordered.h"
#include <random>
#include <algorithm>
#include "chiSquare.h"

int MoveToFrontList::cnt = 0;
int Ordered::cnt = 0;

float stats(int wLen, int exp, int cnt, int n) {
	float p = 1 / pow(2, wLen - exp);
	std::cout << p << std::endl;
	auto tmp1 = ((cnt - n*p)*(cnt - n*p)) / (n*p);
	auto tmp2 = ((n - cnt) - n*(1 - p))*((n - cnt) - n*(1 - p)) / (n*(1 - p));
	return tmp1 + tmp2;
}

int main(int argc, const char * argv[]) {
	setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int wSize = 4;
    int exp = 3;
	std::size_t count = 12;

	//std::mt19937_64 gen { std::random_device()() };
	//std::uniform_int_distribution<int> uid(0, count);

	

	//std::vector<int> vector(count);
	//int pos = 0;
	//do {
	//	std::generate(vector.begin(), vector.end(), [&uid, &gen]() -> int { return uid(gen); });
	//	auto it = std::unique(vector.begin() + pos, vector.end());
	//	vector.resize(std::distance(std::begin(vector), it));
	//	pos = vector.size();
	//	std::cout << pos << std::endl;
	//	vector.resize(count);	
	//} while (pos != count);
 //   
    //FileReader f("/Users/Bin/Novosib.txt");
    //std::cout << f.filesize() << std::endl;
//    bool a = false;
    
//    auto var = f.readNext(a);

    //var->test();
//
//    std::cout << (unsigned long)pow(2, 46) << std::endl;
    
//    auto chi = new ChiSquare(8, 4);
    
//    for (int i = 0; i < 10; i++) {
//        auto bs = var->test();
//        chi->search(bs);
//    }
    
//    chi->out();
    
    //----------------------------- THIS IS MOVE TO FRONT -----------------------------
//    auto mtf = new MoveToFrontList(wSize, exp);
//        for (int i = 0; i < 10000000; i++) {
//            auto tmp = new boost::dynamic_bitset<>(wSize, rand());
//            mtf->process(tmp);
//        }
//    std::cout << end - now << std::endl;
//    std::cout << "h2 = " << stats(wSize, exp, MoveToFrontList::cnt, count) << std::endl;
    //-----------------------------------------------------------------------------------------
    //----------------------------- THIS IS ORDERED MOVE TO FRONT -----------------------------
	auto ord = new Ordered(wSize, exp);
	std::cout << "process started" << std::endl;
	//int count = (int)pow(2, exp);
	for (int i = 0; i < 10; i++) {
		//auto tmp = std::shared_ptr(new std::pair<unsigned long, int>(rand()%(unsigned long)pow(2, wSize), 0));
//		auto tmp = std::shared_ptr<std::pair<unsigned long, int>>(new std::pair<unsigned long, int>(rand() % (unsigned long)pow(2, wSize), 0));
		auto tmp = std::shared_ptr<std::pair<unsigned long, int>>(new std::pair<unsigned long, int>(rand() % (unsigned long)pow(2, wSize), 0));
		ord->find(tmp);
	}
		std::cout << "h2 = " << stats(wSize, exp, Ordered::cnt, count) << std::endl;
    //-----------------------------------------------------------------------------------------
	getchar();
    return 0;
}
