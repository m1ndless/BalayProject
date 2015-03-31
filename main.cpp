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

#include "chiSquare.h"

int MoveToFrontList::cnt = 0;
int Ordered::cnt = 0;


struct Govnohasher {
    size_t operator()(const int it) const {
        return 1;
    }
};

float stats(int wLen, int exp, int cnt, int n) {
	float p = 1 / pow(2, wLen - exp);
	std::cout << p << std::endl;
	auto tmp1 = ((cnt - n*p)*(cnt - n*p)) / (n*p);
	auto tmp2 = ((n - cnt) - n*(1 - p))*((n - cnt) - n*(1 - p)) / (n*(1 - p));
	return tmp1 + tmp2;
}

int main(int argc, const char * argv[]) {
    // insert code here...
	setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    
    
    
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
    int wSize = 30; //длина слова - 24 бита
    int exp = 21; //показатель степени двойки
    //auto mtf = new MoveToFrontList(wSize, exp);
    //mtf->out();
    //std::cout << mtf->bookStack.size() << std::endl;
//        time_t now;
//        time(&now);
//        for (int i = 0; i < 10; i++) {
//            std::cout << "iteration #" << i << std::endl;
//            auto tmp = new boost::dynamic_bitset<>(wSize, rand()%8);
//            mtf->process(tmp);
//        }
//        time_t end;
//        time(&end);
//    std::cout << end - now << std::endl;
    
    //for (auto it = mtf->hashSet.begin(); it != mtf->hashSet.end(); ++it) {
    //    mtf->bookStack.erase(*it);
    //}
    
	//        time_t now;
	//        time(&now);
 //   //auto omtf = new OrderedMoveToFront(wSize, exp);

	//for (int i = 0; i < 100000; i++) {
	//	std::cout << i << std::endl;
	//	omtf->find(rand()%(int)pow(2,24));
	//}
	//        time_t end;
	//        time(&end);
	//    std::cout << end - now << std::endl;


	std::cout << "init" << std::endl;
	auto ord = new Ordered(wSize, exp);
	
	std::cout << "process started" << std::endl;
	time_t now;
	time(&now);
	int count = (int)pow(2, exp);
	for (int i = 0; i < count; i++) {
		//testing for wLen == 20; RAND_MAX = 65k
		auto tmp = Ordered::Key(rand() * rand(), 0);
		ord->find(tmp);
	}
	    time_t end;
	    time(&end);
		std::cout << "h2 = " << stats(wSize, exp, Ordered::cnt, count) << std::endl;
    
    //std::unordered_set<int, Govnohasher> test;
    //std::unordered_set<int> test;
    //for (int i = 0; i < 10000; i++) {
    //    auto tmp = rand();
    //    test.insert(i);
    //}
    //
    //for (auto it = test.begin(); it != test.end(); ++it) {
    //    std::cout << *it << std::endl;
    //}
		getchar();
    return 0;
}
