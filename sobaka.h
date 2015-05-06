//
//  sobaka.h
//  BalayProject
//
//  Created by Denis Genalitskiy on 26.04.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//

#ifndef BalayProject_sobaka_h
#define BalayProject_sobaka_h

#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <algorithm>
#include <deque>

class sobaka {
public:
    int count;
    int exp;
    int wSize;
    
    std::deque<int> values;
    std::unordered_set<int> suka;
    
    sobaka(int _wSize, int _exp) : wSize(_wSize), exp(_exp) {
        while (suka.size() != (int)pow(2, exp)) {
            suka.insert(rand() % (int)pow(2, wSize));
        }
        
        for (auto it = suka.begin(); it != suka.end(); ++it) {
            values.push_back(*it);
        }
    }
    
    void process(int val) {
        auto it = std::find(values.begin(), values.end(), val);
        
        if (it != values.end()) {
            count++;
            values.erase(std::remove(values.begin(), values.end(), *it));
        }
        
        else {
            values.erase(--values.end());
        }
        values.push_front(val);
    }
    
};


#endif
