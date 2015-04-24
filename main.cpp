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
	std::cout << "v stack: " << cnt << std::endl;
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

int testingFucntion(const char* path, int wSize, int exp, int count, bool type) {
    
    std::random_device rd;
    //std::mt19937 re(rd());
    if (type) {
        std::mt19937 re(rd());
    }
    
    else {
        std::minstd_rand re(rd());
    }
    
    std::uniform_int_distribution<unsigned long> ui(0, (unsigned long)pow(2, wSize) - 1);
    
    for (int c = 0; c < 10; c++) {
        std::cout << "TESTING CYCLE " << c + 1 << std::endl;
        
        std::ofstream file(path);
        for (int i = 0; i < count; i++) {
            file << ui(rd);
            file << "\n";
        }
        file.close();
        
        
        std::ifstream infile(path);
        //----------------------------- THIS IS CHI SQUARE -----------------------------
        {
            auto chiSquare = new ChiSquare(wSize, exp, 4);
            int i = 0;
            unsigned long num;
            while (infile >> num) {
                i++;
                chiSquare->search(num);
            }
            auto tatol = 0;
            for (auto it = chiSquare->frenqInBuckets->begin(); it != chiSquare->frenqInBuckets->end(); ++it) {
                tatol += *it;
            }
            std::cout << "chi" << std::endl;
            std::cout << "h2 = " << stats(wSize, exp, tatol, count) << std::endl;
            std::cout << "******************************" << std::endl;
            infile.close();
        }
        
        //----------------------------- THIS IS MOVE TO FRONT -----------------------------
        {
            infile.open(path);
            unsigned long num;
            auto mtf = new MoveToFrontList(wSize, exp);
            int i = 0;
            while (infile >> num) {
                i++;
                auto tmp = new boost::dynamic_bitset<>(wSize, num);
                mtf->process(tmp);
                //if (i % 100000 == 0) std::cout << i << "size is: " << mtf->size() << std::endl;
            }
            std::cout << "bookStack" << std::endl;
            std::cout << "h2 = " << stats(wSize, exp, MoveToFrontList::cnt, count) << std::endl;
            std::cout << "******************************" << std::endl;
            infile.close();
            MoveToFrontList::cnt = 0;
        }
        //----------------------------- THIS IS ORDERED MOVE TO FRONT -----------------------------
        {
            infile.open(path);
            auto ord = new Ordered(wSize, exp);
            unsigned long num = 0;
            int i = 0;
            while (infile >> num) {
                i++;
                auto tmp = std::shared_ptr<std::pair<unsigned long, int>>(new std::pair<unsigned long, int>(num, 0));
                ord->find(tmp);
                //if (i % 100000 == 0) {
                //std::cout << i << "size is: " << ord->hashSet.size() << "\t" << ord->stash.size() << std::endl;
            }
        }
        std::cout << "Ordered" << std::endl;
        std::cout << "h2 = " << stats(wSize, exp, Ordered::cnt, count) << std::endl;
        infile.close();
        std::cout << "******************************" << std::endl;
        Ordered::cnt = 0;
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
        
        if (remove(path)) {
            assert("ne udalilosya :(");
            getchar();
            return 0;
        }
        
        
    }
    return 0;
}

int main(int argc, const char * argv[]) {
	setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int wSize = 4;
    int exp = 3;
	std::size_t count = 100000;
	const char* path = "/Users/Bin/testing.txt";

    auto var = testingFucntion(path, wSize, exp, count, true);




	//file.close();
    

    //-----------------------------------------------------------------------------------------
    getchar();
}

