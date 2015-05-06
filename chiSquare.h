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
#include <unordered_set>
#include <math.h>
#include <random>
#include <iostream>
#include <utility>

#endif /* defined(__BalayProject__chiSquare__) */


class ChiSquare {
    size_t wLength;
    size_t exp;
    unsigned int bucketCount;
    
	typedef std::pair<unsigned long, int> Key;

	struct KeyEqual {
		bool operator()(const Key &lhs, const Key &rhs) {
			return lhs.first == rhs.first;
		}
	};

	struct KeyHash {
		std::size_t operator()(const Key & src) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn(src.first);
		}
	};

    std::vector<unsigned long> *bucketLimits; //ËÌ‰ÂÍÒ „‡ÌË˜ÌÓ„Ó ÒÎÓ‚‡
	

public:
	std::vector<int> *frenqInBuckets;
	std::unordered_set<std::pair<unsigned long, int>, KeyHash, KeyEqual> data;

    ChiSquare(size_t _wLength, size_t _exp, unsigned int _bucketCount) : wLength(_wLength), exp(_exp), bucketCount(_bucketCount ) {
        frenqInBuckets = new std::vector<int>(bucketCount);
        bucketLimits = new std::vector<unsigned long>();
		init();
        calculateLimits(this->wLength, this->bucketCount);
    }

	void init() { //OK
		std::random_device rd;
		std::mt19937 re(rd());
		std::uniform_int_distribution<unsigned long> ui(0, (unsigned long)pow(2, wLength) - 1);

		int i = 0;
		while (data.size() != (size_t)pow(2, exp)) {
			auto pair = data.insert(std::pair<unsigned long, int>(ui(re), i));
			if (pair.second) i++;
            if (data.size() % 10000 == 0) std::cout << "size is: " <<  data.size() << std::endl;
		}
	}
    
    ~ChiSquare() {
        delete frenqInBuckets;
        delete bucketLimits;
    }
    
    void calculateLimits(size_t wLength, int bucketCount) {

		unsigned long inBucket = (size_t)pow(2, exp) / this->bucketCount;
		unsigned long first = inBucket - 1;

		for (int i = 1; i <= bucketCount; i++, first += inBucket) {
			bucketLimits->push_back(first);
		}

		for (auto it = bucketLimits->begin(); it != bucketLimits->end(); ++it) {
			std::cout << *it << std::endl;
		}

    }
    
    void out() {
        for (auto it : *frenqInBuckets) {
            std::cout << it << std::endl;
        }
    }
    
    void search(unsigned long val) {

		Key key = Key(val, 0);
		int i = 0;
        
        auto found = data.find(key);
        
        if (found != data.end()) {
		auto index = data.find(key)->second;
            for (auto it = bucketLimits->begin(); it != bucketLimits->end(); ++it, i++) {
                if (index <= *it) { (*(frenqInBuckets->begin() + i))++;
                    break;
                }
            }
        }
        
        else {
            return;
        }
    }
};