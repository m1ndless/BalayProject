//
//  OrderedMoveToFront.h
//  BalayProject
//
//  Created by Denis Genalitskiy on 26.03.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//

#ifndef __BalayProject__OrderedMoveToFront__
#define __BalayProject__OrderedMoveToFront__

#include <stdio.h>
#include <set>
#include <utility>
#include <unordered_set>
#include <math.h>
#include <memory>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <utility>



class OrderedMoveToFront {
private:
    
    typedef std::shared_ptr<std::pair<int, unsigned long>> Key;

    
    size_t wLength;
    unsigned int exponent;
    
    struct less_key : std::binary_function<std::shared_ptr<Key>,std::shared_ptr<Key>,bool> {
        bool operator()( const Key& b1, const Key& b2 ) {
            return b1->second < b2->second;
        }
    };
    
    struct Hasher {
        size_t operator()(std::multiset<Key>::iterator const &it) const {
            std::hash<unsigned long> hash_fn;
            return hash_fn(it->get()->second);
        }
    };
    
    std::unordered_set<std::multiset<Key>::iterator, OrderedMoveToFront::Hasher> hashSet;
    std::multiset<Key, less_key> bookStack;
    
public:
    OrderedMoveToFront(size_t _wLength, unsigned int _exponent) : wLength(_wLength), exponent(_exponent) {
        init();
    }
    
    void init() {
        for (int i = 0; i < pow(2, exponent); i++) {
            auto tmp = std::shared_ptr<std::pair<int, unsigned long>>(new std::pair<int, unsigned long>(0, i));
            bookStack.insert(tmp);
        }
        
        for (auto it = begin(bookStack); it != end(bookStack); ++it) {
            hashSet.insert(it);
        }
    }
    
    void outBookStack() {
        std::cout << "size is: " << bookStack.size() << std::endl;
        for (auto it = std::begin(bookStack); it != std::end(bookStack); ++it) {
            std::cout << (*it).get()->first << "\t" << (*it).get()->second << std::endl;
        }
    }
    
    void outHashSet(){
        for (auto it = std::begin(hashSet); it != std::end(hashSet); ++it) {
            std::cout << (*it)->get()->first << "\t" << (*it)->get()->second << std::endl;
        }
    }
    
    void process(boost::dynamic_bitset<> *bs) {
        
    }
    
    
    
    
};

#endif /* defined(__BalayProject__OrderedMoveToFront__) */
