//
//  MoveToFrontList.h
//  BalayProject
//
//  Created by Denis Genalitskiy on 20.03.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//

#ifndef __BalayProject__MoveToFrontList__
#define __BalayProject__MoveToFrontList__

#include <unordered_set>
#include <boost/dynamic_bitset.hpp>
#include <boost/functional/hash.hpp>

#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <math.h>

#endif /* defined(__BalayProject__MoveToFrontList__) */

struct Key {
    std::shared_ptr<boost::dynamic_bitset<>> key;
    
    bool operator==(const Key& src) {
        return this->key.get() == src.key.get();
    }
    
    Key(boost::dynamic_bitset<> *_key) {
        this->key = std::shared_ptr<boost::dynamic_bitset<>>(_key);
    }
    
    Key(std::shared_ptr<boost::dynamic_bitset<>> _key) : key(_key) {}
    
    
    Key& operator=(Key &src) {
        if (this != &src) {
            this->key = src.key;
        }
        return *this;
    }
    
    Key& operator=(Key&& other) {
        assert (this != &other);
        this->key = other.key;
        return *this;
    }
    
    Key (const Key &src) {
        this->key = src.key;
    }
};

namespace boost {
    template<typename B, typename A>
    std::size_t hash_value(const boost::dynamic_bitset<B, A>& bs) {
        return boost::hash_value(bs.m_bits);
    }
}

namespace hashUtils {
    
    struct KeyEqual {
        bool operator()(const Key &lhs, const Key &rhs) {
            return lhs.key.get() == rhs.key.get();
        }
    };
    
    struct KeyHash {
        std::size_t operator()(const Key & src) const {
            return boost::hash_value(*src.key.get());
        }
    };
    
    struct IteratorHash {
        size_t operator()(std::list<Key>::iterator it) const {
            return boost::hash_value(*it->key.get());
        }
    };

	struct IteratorEqual
	{
		bool operator()(const std::list<Key>::iterator &lhs, const std::list<Key>::iterator &rhs) {
			return *(*lhs).key.get() == *(*rhs).key.get();
		}
	};
    
}



class MoveToFrontList {
public:
    static int cnt;
    size_t wLength;
    int exponent;
    std::list<Key>::iterator it;
    
    std::list<Key> bookStack;
    std::unordered_set<std::list<Key>::iterator, hashUtils::IteratorHash, hashUtils::IteratorEqual> hashSet;
    int topPartCount;
    
    MoveToFrontList(size_t _wLength, int _exponent) : wLength(_wLength), exponent(_exponent) {
        init();
        
    }
    
    void init() {
        //Добавить рандомизацию, но пока в целях отладки будем использовать последовательные значения
        for (int i = 0; i < pow(2, this->exponent); i++) {
            Key tmp(new boost::dynamic_bitset<>(this->wLength, i));
            bookStack.push_back(tmp);
        }  
        it = bookStack.begin();
        for (;it != bookStack.end(); ++it) {
            hashSet.insert(it);
        }
		bookStack.push_back(Key(new boost::dynamic_bitset<>(this->wLength, pow(2, this->exponent))));
		it = --bookStack.end();
    }
    
    void out() {
        for (auto it = bookStack.begin(); it != bookStack.end(); ++it) {
            std::cout << (it->key.get()) << std::endl;
            }
    }
            
    void outHashSet() {
        //auto t = hashSet.hash_function();
        for (auto it = hashSet.begin(); it != hashSet.end(); ++it) {
            std::cout << (*it)->key.get() << std::endl;
        }    
	}
            

    
    //Найди заданный элемент и вернуть его позицию в дэке
    std::list<Key>::iterator findPosition(boost::dynamic_bitset<> *el) {
        //Key elem(el);
		//*it = elem;
        
        *it = Key(el);
        
		auto res = hashSet.find(it);
            //std::cout << "word is: "<< *(*res)->key.get() << std::endl;
        if (res != hashSet.end()) {
			//std::cout << "zaebis" << std::endl;
            //topPartCount++;
            cnt++;
            //std::cout << "word is: "<< *(*res)->key.get() << std::endl;
			return *res;
        }
		else {
			//std::cout << "huevo" << std::endl;
			return bookStack.end();
		}

    }
    
    void resetDequePositions(std::list<Key>::iterator& it) {
        if (it != bookStack.end()) {
            hashSet.erase(it);
            bookStack.erase(it);
            return;
        }
        else {
			//FIX IT !
            hashSet.erase(----bookStack.end());
            bookStack.erase(----bookStack.end());
            return;
        }
    }
    
    void process(boost::dynamic_bitset<> *bs) {
        //int cnt = 0;
        ///std::cout << "Looking for a word " << *bs << std::endl;
        //std::cout <<  "Current stack is: " << std::endl;
        //out();

        
        auto pos = findPosition(bs);
        //std::cout << "Позиция искомого в дэке слова: " << (*pos << " найдено " << ++cnt << std::endl;
        //std::cout << "Перехуячиваем позиции" << std::endl;
        resetDequePositions(pos);
        //out();
        //std::cout << "Встовляем" << std::endl;
        bookStack.push_front(new boost::dynamic_bitset<>(*bs));
        //outHashSet();
        hashSet.insert(bookStack.begin());
        //std::cout << "Inserting: " << (*bookStack.begin()).key.get() << std::endl;
        //outHashSet();
        
        //out();
        
#ifndef DEBUG
        //        std::cout << "SUKA" << std::endl;
        //        auto pos = findPosition(&el);
        //        resetDequePositions(pos);
        //        bookStack.push_front(el);
#endif
    }


};