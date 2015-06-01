//
//  main.cpp
//  BalayProject
//
//  Created by Denis Genalitskiy on 03.03.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//


#define _CRT_SECURE_NO_WARNINGS
#include <limits>
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
#include "sobaka.h"
#include "LongToBitsetConverter.h"
#include "chiSquare.h"
#include "Utils.h"
//#include <des.h>

int MoveToFrontList::cnt = 0;
int Ordered::cnt = 0;



float stats(int wLen, int exp, int cnt, int n) {
	float p = 1 / pow(2, wLen - exp);
	std::cout << "v stack: " << cnt << std::endl;
	std::cout << "Prop is: " << p << std::endl;
	
	auto tmp1 = ((cnt - n*p)*(cnt - n*p)) / (n*p);
	auto tmp2 = ((n - cnt) - n*(1 - p))*((n - cnt) - n*(1 - p)) / (n*(1 - p));
    std::cout << "x^2 is: " << tmp1 + tmp2 << std::endl;
	return tmp1 + tmp2;
}

void encryptSequence(int from, int to, unsigned long _key, const char* path) {
    
    std::ofstream file(path);
    //auto key = utils::ulongToCharArray(_key);
    //	unsigned char key[32] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    //		0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78,
    //		0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0,
    //		0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe };
    
    unsigned char key[16];
    
    for (int i = 0; i < 16; i++) {
        key[i] = rand() % 256;
        //key[i] = 0;
    }
    
    //for (int i = from; i < to; i++) {
    for (int i = from; i < to; i += 4) {
        unsigned int ct[4], pt[4];
        //pt[0] = pt[1] = pt[2] = 0;
        pt[0] = i;
        pt[1] = i + 1;
        pt[2] = i + 2;
        pt[3] = i + 3;
        utils::rc6_key_setup(key, 16);
        utils::rc6_block_encrypt(pt, ct);
        for (int i = 0; i < 4; i++) {
            file << ct[i] << "\n";
        }
    }
}

void outDataToBinary(int from, int to, const char* path) {
    std::ofstream file(path, std::ios::binary);
    for (int i = from; i < to; i++) {
        file.write(reinterpret_cast<const char*>(&i), sizeof(i));
    }
    file.close();
}

float chiStats(int wLen, int bucketCount, std::vector<int> freq, int count) {
	float result = 0;

	float p = 1 / (float)bucketCount;

	for (auto it = freq.begin(); it != freq.end(); ++it) {
		result += (*it - count * p)*(*it - count * p) / count*p;
	}

	return result;
}

int testingFucntion(const char* path, int wSize, int exp, int count, bool type, int cycles) {
    
    //std::random_device rd;
    //std::mt19937 re(rd());
//    if (type) {
//        std::mt19937 re(rd());
//    }
//    
//    else {
//        std::minstd_rand re(rd());
//    }
    
    std::uniform_int_distribution<unsigned long> ui(0, (unsigned long)pow(2, wSize) - 1);
    
    float chiP = 0;
    float stackP = 0;
    float orderedP = 0;
    
    for (int sh = 0; sh < cycles; sh++) {
        std::cout << "TESTING CYCLE " << sh + 1 << std::endl;
        
        if (sh == 0) {
            chiP = stackP = orderedP = 0;
        }
        //std::ofstream file(path);
        //for (int i = 0; i < count; i++) {
        //    unsigned long num = rand();
        //    num >>= (31 - wSize);
        //    //std::cout << "STALO " <<  num << std::endl;
        //    
        //    file << num;
        //    //file << ui(rd);
        //    file << "\n";
        //}
        //file.close();
//        remove(path);
//        encryptSequence(0, count, 0, path);
        
        
        std::ifstream infile(path);
        //----------------------------- THIS IS CHI SQUARE -----------------------------
        {
            auto chiSquare = new ChiSquare(wSize, exp, 1);
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
            chiP += stats(wSize, exp, tatol, count);
            //std::cout << "h2 = " << stats(wSize, exp, tatol, count) << std::endl;
            std::cout << "******************************" << std::endl;
            infile.close();
            chiSquare->out();
        }
        
        //----------------------------- THIS IS MOVE TO FRONT -----------------------------
        {
            MoveToFrontList::cnt = 0;
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
            stackP += stats(wSize, exp, MoveToFrontList::cnt, count);
            //std::cout << "h2 = " << stats(wSize, exp, MoveToFrontList::cnt, count) << std::endl;
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
        orderedP += stats(wSize, exp, Ordered::cnt, count);
        //std::cout << "h2 = " << stats(wSize, exp, Ordered::cnt, count) << std::endl;
        infile.close();
        std::cout << "******************************" << std::endl;
        Ordered::cnt = 0;
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
        
        //if (remove(path)) {
        //    assert("ne udalilosya :(");
        //    getchar();
        //    return 0;
        //}
        
        
    }
    std::cout << "chi: " << chiP / (cycles) << "\t" << "stackP: " << stackP / (cycles) << "\t" << "orderedP: " << orderedP / (cycles) << std::endl;
    return 0;
}

void zalupa(const char* cyka, const char* sobaka) {
    std::ifstream koza(cyka, std::ios::binary);
    std::ofstream dereza(sobaka);
    
    unsigned int value;
    
    while (koza.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        dereza << value;
        dereza << "\n";
    }
}



int main(int argc, const char * argv[]) {
//	setlocale(LC_ALL, "Russian");
//    srand(time(NULL));
    int wSize = 32;
    int exp = 22;
//	//std::size_t count = 10000000;
    std::size_t count = (size_t)pow(2, 22);
    int cycles = 1;
//	const char* path = "/Users/Bin/crypt.txt";
    zalupa("/Users/Bin/res.txt", "/Users/Bin/kakashka.txt");
    auto var = testingFucntion("/Users/Bin/kakashka.txt", wSize, exp, count, false, cycles);
    //outDataToBinary(0, (int)pow(2, 22), "/Users/Bin/sobaka");

    
    //getchar();
}

