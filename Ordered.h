#pragma once

#include <stdio.h>
#include <set>
#include <utility>
#include <unordered_set>
#include <math.h>
#include <memory>
#include <iostream>
#include <vector>
#include <random>
#include <list>
#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include <utility>

class Ordered {
public:
	int wLen;
	int exp;
	static int cnt;
	typedef std::shared_ptr<std::pair<unsigned long, int>> Key;

	struct PtrHasher {
		size_t operator()(const Key& it) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn(it->first);
		}
	};

	struct PtrEqual {
		bool operator()(const Key& lhs, const Key& rhs) const {
            bool tmp = lhs->first == rhs->first;
            return tmp;
		}
	};

	struct Equal {
		bool operator()(const Key& lhs, const Key& rhs) const {
			return lhs->first == rhs->first;
		}
	};

	struct Hasher {
		size_t operator()(const Key &it) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn(it->first);
		}
	};

	struct SetComparator {
		bool operator() (const Key& lhs, const Key& rhs) {
			return lhs->first < rhs->first;
		}
	};

	struct IteratorHash {
		size_t operator()(const std::list<Key>::iterator& it) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn((*it)->first);
		}
	};

	struct IteratorEqual
	{
		bool operator()(const std::list<Key>::iterator &lhs, const std::list<Key>::iterator &rhs) {
			return (*lhs)->first == (*rhs)->first;
		}
	};

	std::vector<std::list<Key> *> data;
	std::unordered_set<std::list<Key>::iterator, IteratorHash, IteratorEqual> hashSet;
    std::unordered_set<Key, Hasher, Equal> stash;
    int minFreq;
    int shotchik;

	Ordered(int _wLen, int _exp) : wLen(_wLen), exp(_exp) {
		this->wLen = _wLen;
		this->exp = _exp;
		init();
		std::cout << "test" << std::endl;
        this->minFreq = 0;
        this->shotchik = 1;
	}
    
	size_t size() {
		auto result = 0;
		for (int i = 1; i < data.size(); i++) {
			result += data[i]->size();
		}
		return result;
	}

	void init() {
		
		std::random_device rd;
		std::mt19937 re(rd());
		std::uniform_int_distribution<unsigned long> ui(0, (unsigned long)pow(2, wLen) - 1);
		
		std::unordered_set<Key, Hasher, Equal> base_data;
		if (exp != wLen) {
			while (base_data.size() != (size_t)pow(2, exp)) {
				base_data.insert(Key(new std::pair<unsigned long, int>(ui(re), 0)));
			}
		}
        
        else {
            assert("nelza");
        }


		data = std::vector<std::list<Key>*>();
		data.push_back(new std::list<Key>());
		data.push_back(new std::list<Key>());
		data.push_back(new std::list<Key>()); //“‡Í Ì‡‰Ó
                
		std::copy(std::begin(base_data), std::end(base_data), std::back_inserter(*data[1]));
		for (auto iter = std::begin(*data[1]); iter != std::end(*data[1]); ++iter) {
			hashSet.insert(iter);
		}

		//it = std::find(std::begin(data[0]), std::end(data[0]), kostil);
        
//        for (auto &l : data) {
//            std::cout << "freq is: " << std::endl;
//            for (auto &el : *l) {
//                std::cout << el->first << "\t" << el->second << "\t" << el << std::endl;
//            }
//            std::cout << "------------" << std::endl;
//        }
        
	}

	void outhash() {
		for (auto it = std::begin(hashSet); it != std::end(hashSet); ++it) {
			std::cout << (*it)->get()->first << "\t" << (*it)->get()->second << "\t" << (*it)->get() << std::endl;
		}
		std::cout << "------------" << std::endl;
	}

	void find(Key& key) {
		//std::cout << "////////////////////////////////" << std::endl;
		//outhash();
        std::list<Key> temp;
        temp.push_front(key);
        
        //std::cout << temp.begin()->get()->first << "\t" << temp.begin()->get()->second << std::endl;
        
        auto inStash = stash.find(*temp.begin());
        
        if (inStash != std::end(stash)) {
            //std::cout << "НАЙДЕНО В СТЭШЕ!!!!!" <<  std::endl;
            auto freq = inStash->get()->second;
            
            if (freq < minFreq) {
                //std::cout << "не вариант, ибо надо "<< minFreq << ", а есть" << freq << std::endl;
                inStash->get()->second++;
                return;
            }
            
            auto insert = Key(new std::pair<unsigned long, int>(inStash->get()->first, freq + 1));
            data[freq + 2]->push_front(insert);
            hashSet.insert(data[freq + 2]->begin());
            stash.erase(inStash);
            
            for (int i = 1; i < data.size(); i++) {
                if (data[i]->size()) {
                    hashSet.erase(--data[i]->end());
                    stash.insert(std::move(*(--data[i]->end())));
                    data[i]->resize(data[i]->size() - 1);
                    if (data[i]->size()) {
                        this->minFreq = i - 1;
                        this->shotchik = minFreq < 1 ? 1 : minFreq;
                    }
                    break;
                    return;
                }
            }
        }
        
        auto found = hashSet.find(temp.begin());

		if (found != hashSet.end()) {
			cnt++;
			//std::cout << "FOUND !! !  " << (*found)->get()->first << "\t" << (*found)->get()->second << "\t" << (*found)->get() << std::endl;
			auto insert = Key(new std::pair<unsigned long, int>((*found)->get()->first, (*found)->get()->second + 1));
			auto freq = (*found)->get()->second;
			if (freq > data.size() - 3) {
				data.push_back(new std::list<Key>());
			}

			auto toInsert = Key(new std::pair<unsigned long, int>((*found)->get()->first, freq + 1));
			data[freq + 2]->push_front(toInsert);
			auto copy = std::list<Key>::iterator(*found);
			hashSet.erase(copy);
			data[freq + 1]->erase(copy);
			hashSet.insert(data[freq + 2]->begin());
			return;
		}
        
		//богатая кодировка
        else {
            //d::cout << "не встречалось " << std::endl;
            //std::cout << "not found " << temp.begin()->get()->first << "\t" << temp.begin()->get()->second << "\t"  << temp.begin()->get() << std::endl;
            auto freq = temp.begin()->get()->second;

			if (freq > data.size() - 2) {
				data.push_back(new std::list<Key>());
			}


            temp.begin()->get()->second++;
            auto insert = Key(new std::pair<unsigned long, int>(temp.begin()->get()->first, 1));
            
            if (freq < minFreq) {
                //data[2]->push_front(insert);
                stash.insert(insert);
                //data[2]->erase(data[2]->begin());
                return;
            }
            
            
            data[2]->push_front(insert);
			hashSet.insert(data[2]->begin());

            //Удаляем в стэш лишний элемент
			for (int i = 1; i < data.size(); i++) {
				if (data[i]->size()) {
					hashSet.erase(--data[i]->end());
                    stash.insert(std::move(*(--data[i]->end())));
					data[i]->resize(data[i]->size() - 1);
                    if (data[i]->size()) {
                        this->minFreq = i - 1;
                        this->shotchik = minFreq < 1 ? 1 : minFreq;
                    }
                    break;
					return;
				}
			}
        }
		//std::cout << " DATA SIZE IS " << data.size() << std::endl;
  //      for (auto &l : data) {
  //      	std::cout << "size is: " << l->size() << std::endl;
  //      	for (auto &el : *l) {
  //      		std::cout << el->first << "\t" << el->second << "\t" << el << std::endl;
  //      	}
  //      	std::cout << "------------" << std::endl;
  //      }
		//std::cout << "////////////////////////////////" << std::endl;
        //outhash();
	}
};