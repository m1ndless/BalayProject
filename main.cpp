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

#include "chiSquare.h"

int MoveToFrontList::cnt = 0;

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
    int wSize = 24;
    int exp = 24;
    
    auto mtf = new MoveToFrontList(wSize, exp);
    //mtf->out();
    //std::cout << mtf->bookStack.size() << std::endl;
        time_t now;
        time(&now);
        for (int i = 0; i < 10000000; i++) {
            //std::cout << "iteration #" << i << std::endl;
            auto tmp = new boost::dynamic_bitset<>(wSize, rand()%(int)pow(2, 24));
            mtf->process(tmp);
        }
        time_t end;
        time(&end);
    std::cout << end - now << std::endl;
    
    //for (auto it = mtf->hashSet.begin(); it != mtf->hashSet.end(); ++it) {
    //    mtf->bookStack.erase(*it);
    //}
    
    return 0;
}
