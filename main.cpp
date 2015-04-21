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
    int wSize = 4;
    int exp = 3;
	std::size_t count = 1000000;

	std::random_device rd;
	std::mt19937 re(rd());
	std::uniform_int_distribution<unsigned long> ui(0, (unsigned long)pow(2, wSize) - 1);

	const char* path = "C:\\rand.txt";


	if (remove(path)) {
		assert("ne udalilosya :(");
		getchar();
		return 0;
	}

	//std::mt19937_64 gen { std::random_device()() };
	//std::uniform_int_distribution<int> uid(0, count);
    
    std::ofstream file(path);

	for (int i = 0; i < count; i++) {
		file << ui(rd);
		file << "\n";
	}

	file.close();

	std::ifstream infile(path);

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
    
//    auto chi = new ChiSquare(wSize, 2);
//    
//    for (int i = 0; i < count; i++) {
//        //auto bs = var->test();
//		if (i % 10000 == 0) std::cout << i << std::endl;
//        chi->search(ui(re));
//    }
//	std::cout << chiStats(wSize, 4, *chi->frenqInBuckets, count) << std::endl;
    
    //chi->out();
    
    //----------------------------- THIS IS MOVE TO FRONT -----------------------------
   // auto mtf = new MoveToFrontList(wSize, exp);
   //     for (int i = 0; i < count; i++) {
   // auto tmp = new boost::dynamic_bitset<>(wSize, ui(re));
   // mtf->process(tmp);
			//if (i % 10000 == 0) std::cout << i << "size is: " << mtf->size() << std::endl;
   //     }
   // //std::cout << end - now << std::endl;
   // std::cout << "h2 = " << stats(wSize, exp, MoveToFrontList::cnt, count) << std::endl;
    //mtf->out();
    //-----------------------------------------------------------------------------------------
    //----------------------------- THIS IS ORDERED MOVE TO FRONT -----------------------------
	auto ord = new Ordered(wSize, exp);
	std::cout << "process started" << std::endl;
	//int count = (int)pow(2, exp);
    std::vector<int> counts(16);
	//for (int i = 0; i < count; i++) {
	unsigned long num;
	int i = 0;
	while (infile >> num) {
		i++;
		auto tmp = std::shared_ptr<std::pair<unsigned long, int>>(new std::pair<unsigned long, int>(num, 0));
        //file << num;
        //file << "\n";
        auto it = counts.begin() + num;
        (*it)++;
		ord->find(tmp);
		if (i % 100000 == 0) std::cout << i << "size is: " << ord->hashSet.size() << "\t" << ord->minFreq << std::endl;
	}
    ord->outhash();
    for (int i = 0; i < 16; i++) {
        std::cout << i << "\t" << counts[i] << std::endl;
    }
      std::cout << "h2 = " << stats(wSize, exp, Ordered::cnt, count) << std::endl;
    //-----------------------------------------------------------------------------------------
	getchar();
    return 0;
}
