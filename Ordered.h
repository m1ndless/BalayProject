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
			return lhs.get()->first == rhs.get()->first;
		}
	};

	struct Hasher {
		size_t operator()(const Key &it) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn(it.get()->first);
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
        this->shotchik = 0;
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
                
		std::copy(std::begin(base_data), std::end(base_data), std::back_inserter(*data[0]));
		for (auto iter = std::begin(*data[0]); iter != std::end(*data[0]); ++iter) {
			hashSet.insert(iter);
		}
	}

	void outhash() {
		for (auto it = std::begin(hashSet); it != std::end(hashSet); ++it) {
			std::cout << (*it)->get()->first << "\t" << (*it)->get()->second << "\t" << (*it)->get() << std::endl;
		}
		std::cout << "------------" << std::endl;
		int totalCount = 0;
		for (auto &el : hashSet) {
			totalCount += el->get()->second;
		}

		for (auto &el : stash) {
			totalCount += el->second;
		}
		std::cout << "total summ is: " << totalCount << std::endl;
	}

	void out() {
		for (auto it = std::begin(hashSet); it != std::end(hashSet); ++it) {
			std::cout << (*it)->get()->first << " ";
		}
		std::cout << std::endl;

		for (auto it = std::begin(stash); it != std::end(stash); ++it) {
			std::cout << (*it)->first << " ";
		}
		std::cout << std::endl;

	}
            
    void outStack() {
        for(int i = 0; i < data.size(); i++) {
            if (data[i]->size() != 0) {
                std::cout << "+++++++++++++++++++++" << std::endl;
                std::cout << "FREQ = " << i << std::endl;
                for(auto it = data[i]->begin(); it != data[i]->end(); ++it) { 
                    std::cout << (*it).get()->first << std::endl;
                }
            }
            else {
                continue;
            }
        }
        std::cout << "stash is: ";
        for(auto it = stash.begin(); it != stash.end(); ++it) {
            std::cout << "{" << (*it)->first << "," << (*it)->second << "}";
        }
        std::cout << std::endl;
    }

	void find(Key& key) {
        std::list<Key> temp;
        temp.push_front(key);
        auto inStash = stash.find(*temp.begin());
        
        if (inStash != std::end(stash)) {
            auto freq = inStash->get()->second;
            if (freq < minFreq) {
                inStash->get()->second++;
                return;
            }
            
            auto insert = Key(new std::pair<unsigned long, int>(inStash->get()->first, freq + 1));

			if (freq == data.size() - 1) {
				data.push_back(new std::list<Key>());
			}

            data[freq + 1]->push_front(insert);
            hashSet.insert(data[freq + 1]->begin());
            stash.erase(inStash);
            
            for (int i = shotchik; i < data.size(); i++) {
                if (data[i]->size()) {
                    hashSet.erase(--data[i]->end());
                    stash.insert(std::move(*(--data[i]->end())));
                    data[i]->resize(data[i]->size() - 1);
                    if (data[i]->size()) {
						this->minFreq = shotchik;
                    }
                    break;
                    return;
                }
				else {
					shotchik++;
				}
            }
			return; 
        }
        
        auto found = hashSet.find(temp.begin());

		if (found != hashSet.end()) {
			cnt++;
			auto insert = Key(new std::pair<unsigned long, int>((*found)->get()->first, (*found)->get()->second + 1));
			auto freq = (*found)->get()->second;
			if (freq == data.size() - 1) {
				data.push_back(new std::list<Key>());
			}

			auto toInsert = Key(new std::pair<unsigned long, int>((*found)->get()->first, freq + 1));
			data[freq + 1]->push_front(toInsert);
			auto copy = std::list<Key>::iterator(*found);
			hashSet.erase(copy);
			data[freq]->erase(copy);
            if (!data[minFreq]->size()) minFreq++;
			hashSet.insert(data[freq + 1]->begin());
			return;
		}
        
        else {
            auto freq = temp.begin()->get()->second;
			if (freq > data.size() - 2) {
				data.push_back(new std::list<Key>());
			}


            temp.begin()->get()->second++;
            auto insert = Key(new std::pair<unsigned long, int>(temp.begin()->get()->first, 1));

            if (minFreq) {
                stash.insert(insert);
                return;
            }
            
            
            data[1]->push_front(insert);
			hashSet.insert(data[1]->begin());

            //Удаляем в стэш лишний элемент
			for (int i = shotchik; i < data.size(); i++) {
				if (data[i]->size()) {
					hashSet.erase(--data[i]->end());
                    stash.insert(std::move(*(--data[i]->end())));
					data[i]->resize(data[i]->size() - 1);
                    if (data[i]->size()) {
						this->minFreq = shotchik;
                    }
                    break;
					return;
				}
				else {
					shotchik++;
				}
			}
        }
		return;

	}
};