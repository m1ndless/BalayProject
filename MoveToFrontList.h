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
    
}



class MoveToFrontList {
public:
    static int cnt;
    size_t wLength;
    int exponent;
    std::list<Key>::iterator it;
    
    std::list<Key> bookStack;
    std::unordered_set<std::list<Key>::iterator, hashUtils::IteratorHash> hashSet;
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
        bookStack.push_back(Key(new boost::dynamic_bitset<>(this->wLength, pow(2, this->exponent))));
        bookStack.insert(<#const_iterator __p#>, <#initializer_list<value_type> __il#>)
        it = bookStack.begin();
        for (;it != bookStack.end(); ++it) {
            hashSet.insert(it);
        }
        
    }
    
    void out() {
        for (auto it = bookStack.begin(); it != bookStack.end(); ++it) {
            std::cout << *(it->key.get()) << std::endl;
            }
    }
            
    void outHashSet() {
        for (auto it = hashSet.begin(); it != hashSet.end(); ++it) {
            std::cout << *(*it)->key.get() << std::endl;
        }    }
            

    
    //Найди заданный элемент и вернуть его позицию в дэке
    Key findPosition(boost::dynamic_bitset<> *el) {
        //auto elem = new Element(el);
        Key elem(el);
        //hashSet.fi
        auto res = hashSet.find(&elem);
//        if (res != hashSet.end()) {
//            topPartCount++;
//            return res->key;
//        }
//        else return nullptr;
        
        
        
        
        return nullptr;
    }
    
    void resetDequePositions(int position) {
        //Если нашли в верхней части стопки, то переписываем индексы выше
//        if (position != -1) {
//            for (auto it = bookStack.begin(); it < bookStack.begin() + position; ++it) {
//                (*it).key->dequePosition++;
//            }
//            bookStack.erase(bookStack.begin() + position);
//            return;
//        }
//        //Не нашли - вставляем в вершину стопки и сжигаем нахуй нижную книгу (Коран)
//        else if (position == -1) {
//            bookStack.erase(bookStack.begin() + bookStack.size() - 1);
//            for (auto it = bookStack.begin(); it < bookStack.end(); ++it) {
//                (*it).key->dequePosition++;
//            }
//            return;
//        }
//        return;
    }
    
    void process(boost::dynamic_bitset<> *bs) {
        //int cnt = 0;
        std::cout << "Ищем слово " << *bs << std::endl;
        //std::cout <<  "Текущая стопка: " << std::endl;
        //out();
        
        //auto t = hashSet.hash_function();
        //std::cout << "Хэш искомого слова: " << t(bs) << std::endl;
        
//        for (auto it = bookStack.begin(); it != bookStack.end(); ++it) {
//            std::cout << t(it->key) << std::endl;// << t(std::shared_ptr<Element>(new Element(bs, 0))) << std::endl;
//        }
        
        //std::cout << (findPosition(bs).key.get()) << std::endl;
        //std::cout << "Позиция искомого в дэке слова: " << pos << " найдено " << ++cnt << std::endl;
        //std::cout << "Перехуячиваем позиции" << std::endl;
        //resetDequePositions(pos);
        //out();
        //std::cout << "Встовляем" << std::endl;
        //bookStack.push_front(std::shared_ptr<Element>(new Element(bs, 0)));
        //out();
        
#ifndef DEBUG
        //        std::cout << "SUKA" << std::endl;
        //        auto pos = findPosition(&el);
        //        resetDequePositions(pos);
        //        bookStack.push_front(el);
#endif
    }


};