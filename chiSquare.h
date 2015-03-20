//
//  chiSquare.h
//  BalayProject
//
//  Created by Denis Genalitskiy on 09.03.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//

#ifndef __BalayProject__chiSquare__
#define __BalayProject__chiSquare__

#include <stdio.h>
#include <vector>
#include <math.h>
#include <boost/dynamic_bitset.hpp>
#include <iostream>

#endif /* defined(__BalayProject__chiSquare__) */

class ChiSquare {
    size_t wLength;
    unsigned int bucketCount;
    std::vector<int> *frenqInBuckets;
    std::vector<boost::dynamic_bitset<>> *bucketLimits;
public:
    ChiSquare(size_t _wLength, unsigned int _bucketCount) : wLength(_wLength), bucketCount(_bucketCount ) {
        frenqInBuckets = new std::vector<int>(bucketCount);
        bucketLimits = new std::vector<boost::dynamic_bitset<>>();
        calculateLimits(this->wLength, this->bucketCount);
    }
    
    void calculateLimits(size_t wLength, int bucketCount) {
        unsigned long countInSingleBucket = (pow(2, wLength) / bucketCount);
        unsigned long first = countInSingleBucket - 1;
        for (int i = 1; i <= bucketCount; i++) {
            bucketLimits->push_back(boost::dynamic_bitset<>(this->wLength, first));
            first += countInSingleBucket;
        }
    }
    
    void out() {
        for (auto it : *frenqInBuckets) {
            std::cout << it << std::endl;
        }
            std::cout << "----------" << std::endl;
            for (auto it : *bucketLimits) {
                std::cout << it.to_ulong() << std::endl;
            }
    }
    
    void search(boost::dynamic_bitset<> &bs) {
        int i = 0;
        for (auto it = bucketLimits->begin(); it != bucketLimits->end(); ++it, i++) {
            if (bs <= *it) {
                (*(frenqInBuckets->begin() + i))++;
                return;
            }
        }
    }
};