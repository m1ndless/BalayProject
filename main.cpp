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
#include <cstdlib>
#include <random>
#include <algorithm>
#include "chiSquare.h"

int MoveToFrontList::cnt = 0;
int Ordered::cnt = 0;

float stats(int wLen, int exp, int cnt, int n) {
	float p = 1 / pow(2, wLen - exp);
	std::cout << "wLen is: " << wLen << std::endl;
	std::cout << "exp is: " << exp << std::endl;
	std::cout << "v stack: " << cnt << std::endl;
	std::cout << "n is: " << n << std::endl;
	std::cout << "Prop is: " << p << std::endl;
	
	auto tmp1 = ((cnt - n*p)*(cnt - n*p)) / (n*p);
	auto tmp2 = ((n - cnt) - n*(1 - p))*((n - cnt) - n*(1 - p)) / (n*(1 - p));
	return tmp1 + tmp2;
}

float chiStats(int wLen, int bucketCount, std::vector<int> freq, int count) {
	float result = 0;

	float p = 1 / (float)bucketCount;

	for (auto it = freq.begin(); it != freq.end(); ++it) {
		result += (*it - count * p)*(*it - count * p) / count*p;
	}

	return result;
}

int main(int argc, const char * argv[]) {
	setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int bucketCount = 4;
    int wSize = 4;
    int exp = 3;
	std::size_t count = 178956970;

	std::random_device rd;
	std::mt19937 re(rd());
	std::uniform_int_distribution<unsigned long> ui(0, (unsigned long)pow(2, wSize) - 1);

	const char* path = "/Users/Bin/testing.txt";


//	if (remove(path)) {
//		assert("ne udalilosya :(");
//		getchar();
//		return 0;
//	}

//    std::ofstream file(path);
//
//	for (int i = 0; i < count; i++) {
//		file << ui(rd);
//		file << "\n";
//	}

	//file.close();

	std::ifstream infile(path);

    auto chiSquare = new ChiSquare(wSize, exp, bucketCount);
    int i = 0;
    unsigned long num;
    
    while (infile >> num) {
        i++;
        chiSquare->search(num);
    }
    std::cout << "i: " << i << std::endl;
    chiSquare->out();
    
    //----------------------------- THIS IS MOVE TO FRONT -----------------------------
	//unsigned long num;
	//auto mtf = new MoveToFrontList(wSize, exp); 
	//int i = 0;
 //   while (infile >> num) {
	//	i++;
	//	auto tmp = new boost::dynamic_bitset<>(wSize, num);
	//	
	//	mtf->process(tmp);
	//	if (i % 10000 == 0) std::cout << i << "size is: " << mtf->size() << std::endl;
 //   }
 //   //std::cout << end - now << std::endl;
	//	
 //   std::cout << "h2 = " << stats(wSize, exp, MoveToFrontList::cnt, count) << std::endl;
	//Sleep(1000);
 //   mtf->out();
	//infile.close();
    //-----------------------------------------------------------------------------------------
    //----------------------------- THIS IS ORDERED MOVE TO FRONT -----------------------------
	//infile.open(path);
//	auto ord = new Ordered(wSize, exp);
//	std::cout << "process started" << std::endl;
//	unsigned long num = 0;
//	int i = 0;
//	while (infile >> num) {
//		i++;
//		auto tmp = std::shared_ptr<std::pair<unsigned long, int>>(new std::pair<unsigned long, int>(num, 0));
//		ord->find(tmp);
//        if (i % 100000 == 0) {
//            std::cout << i << "size is: " << ord->hashSet.size() << "\t" << ord->stash.size() << std::endl;
//        }
//	}
//      std::cout << "h2 = " << stats(wSize, exp, Ordered::cnt, count) << std::endl;
//	  infile.close();
    //-----------------------------------------------------------------------------------------
	//getchar();
    return 0;
}
