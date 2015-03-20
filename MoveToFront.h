//
//  MoveToFront.h
//  BalayProject
//
//  Created by Denis Genalitskiy on 13.03.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//

#ifndef __BalayProject__MoveToFront__
#define __BalayProject__MoveToFront__



#include <stdio.h>
#include <unordered_set>
#include <boost/dynamic_bitset.hpp>
#include <boost/functional/hash.hpp>
#include <functional>
#include <iostream>
#include <deque>
#include <memory>
#include <math.h>

struct Element {
    boost::dynamic_bitset<> word;
    int dequePosition;
    bool operator==(const Element &src) const {
        return this->word == src.word;
    }
    
    bool operator==(const Element *src) const {
        return this->word == src->word;
    }
    
    Element (boost::dynamic_bitset<> _word, int _dequePosition) : word(_word), dequePosition(_dequePosition) {
    }
    
    Element(boost::dynamic_bitset<> _word) : word(_word), dequePosition(0) {
    }
    
    Element& operator=(Element &src) {
        if (this != &src) {
            this->word = src.word;
            this->dequePosition = src.dequePosition;
        }
        return *this;
    }
    
    Element& operator=(Element&& other) {
        assert (this != &other);
        this->word = other.word;
        this->dequePosition = other.dequePosition;
        return *this;
    }
    
    Element (const Element &src) {
        this->word = src.word;
        this->dequePosition = src.dequePosition;
    }
    
};

struct Key {
    std::shared_ptr<Element> key;
    
    bool operator==(const Key& src) {
        return this->key.get() == src.key.get();
    }
    
    Key(std::shared_ptr<Element> _key) : key(_key) {}
    Key(Element *el) {
        key = std::shared_ptr<Element>(el);
    }
};

namespace boost {
       template<typename B, typename A>
            std::size_t hash_value(const boost::dynamic_bitset<B, A>& bs) {
            return boost::hash_value(bs.m_bits);
    }
}


namespace std {
//        template<>
//        struct hash<Key>
//        {
//            typedef Element argument_type;
//            typedef std::size_t result_type;
//    
//            result_type operator()(const Key& src) const {
//                return boost::hash_value(src.key.get());
//            }
//        };
    
    struct KeyEqual {
        bool operator()(const Key &lhs, const Key &rhs) {
            return *(lhs.key.get()) == *(rhs.key.get());
        }
    };
    
    struct KeyHash {
        std::size_t operator()(const Key & src) const {
            return boost::hash_value(src.key.get()->word);
        }
    };
    

}




class MoveToFront {
public:
    static int cnt;
    //typedef std::shared_ptr<Element> Key;
    
    size_t wLength;
    int exponent;
    
    typedef std::unordered_set<
        Key,
        //std::function<std::size_t(const Key&)>,
        std::KeyHash,
        std::KeyEqual
    > HashSet;
    
    HashSet hashSet;
    
    //std::unordered_set<std::shared_ptr<Element>> hashSet;
    std::deque<Key> bookStack;
    int topPartCount;
    
public:
    MoveToFront(size_t _wLength, int _exponent) : wLength(_wLength), exponent(_exponent) {
        HashSet hashSet(0, std::KeyHash(), std::KeyEqual());
        init();
        
    }
    

    
    
    void init() {
        //Добавить рандомизацию, но пока в целях отладки будем использовать последовательные значения
        for (int i = 0; i < pow(2, this->exponent); i++) {
            boost::dynamic_bitset<> tmp(this->wLength, i);
            std::shared_ptr<Element> element(new Element(tmp, i));
            hashSet.insert(element);
            bookStack.push_back(element);
        }


    }
    
    //Найди заданный элемент и вернуть его позицию в дэке
    int findPosition(Element *el) {
        //auto elem = new Element(el);
        Key elem(el);
        auto res = hashSet.find(elem);
        if (res != hashSet.end()) {
            topPartCount++;
            //return (*res)->dequePosition;
            return (*res).key->dequePosition;
        }
        else return -1;
    }
    
    void resetDequePositions(int position) {
        //Если нашли в верхней части стопки, то переписываем индексы выше
        if (position != -1) {
            for (auto it = bookStack.begin(); it < bookStack.begin() + position; ++it) {
                (*it).key->dequePosition++;
            }
            bookStack.erase(bookStack.begin() + position);
            return;
        }
        //Не нашли - вставляем в вершину стопки и сжигаем нахуй нижную книгу (Коран)
        else if (position == -1) {
          bookStack.erase(bookStack.begin() + bookStack.size() - 1);
            for (auto it = bookStack.begin(); it < bookStack.end(); ++it) {
                (*it).key->dequePosition++;
            }
            return;
        }
        return;
    }
    
    void out() {
        for (int i = 0; i < bookStack.size(); i++) {
            std::cout << bookStack[i].key->word << "\t" << bookStack[i].key->dequePosition << std::endl;
            }
    }
    
    //Процессим
    void process(boost::dynamic_bitset<> bs) {
        //int cnt = 0;
        //std::cout << "Ищем слово " << bs << std::endl;
        //std::cout << "Текущая стопка: " << std::endl;
        //out();
        
        auto t = hashSet.hash_function();
        //std::cout << "Хэш искомого слова: " << t(new Element(bs)) << std::endl;
        
//        for (int i = 0; i < bookStack.size(); i++) {
//            std::cout << t(bookStack[i]) << "\t" << t(std::shared_ptr<Element>(new Element(bs, 0))) << std::endl;
//        }
        
        auto pos = findPosition(new Element(bs));
        //std::cout << "Позиция искомого в дэке слова: " << pos << " найдено " << ++cnt << std::endl;
        //std::cout << "Перехуячиваем позиции" << std::endl;
        resetDequePositions(pos);
        //out();
        //std::cout << "Встовляем" << std::endl;
        bookStack.push_front(std::shared_ptr<Element>(new Element(bs, 0)));
        //out();
        
#ifndef DEBUG
//        std::cout << "SUKA" << std::endl;
//        auto pos = findPosition(&el);            
//        resetDequePositions(pos);
//        bookStack.push_front(el);
#endif
    }
};


///   friend std::size_t hash_value(Element const& src) {
//        std::size_t seed = 0;
//        boost::hash_combine(seed, src.word);
//        return seed;
//    }



#endif /* defined(__BalayProject__MoveToFront__) */
