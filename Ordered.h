#pragma once

#include <stdio.h>
#include <set>
#include <utility>
#include <unordered_set>
#include <math.h>
#include <memory>
#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <utility>

class Ordered {
public:
	typedef std::pair<unsigned long, int> Key;

	struct PtrHasher {
		size_t operator()(const Key *it) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn(it->first);
		}
	};

	struct PtrEqual {
		size_t operator()(const Key* lhs, const Key* rhs) const {
            bool tmp = lhs->first == rhs->first;
            return tmp;
		}
	};

	std::vector<std::unordered_set<Key*, PtrHasher, PtrEqual>> data;
	std::unordered_set<Key*, PtrHasher, PtrEqual> hashSet;
	size_t wLen;
	int exp;

	Ordered(size_t _wLen, int _exp) : wLen(_wLen), exp(_exp) {
		init();
	}

	void init() {
		data.push_back(std::unordered_set<Key*, PtrHasher, PtrEqual>());
		for (int i = 0; i < pow(2, exp); i++) {
			auto pair = new Key(i, 0);
			hashSet.insert(pair);
			data[0].insert(pair);
		}
	}

	void find(Key key) {
		auto found = hashSet.find(&key);
		if (found != hashSet.end()) {
			auto freq = (*found)->second;
			//std::cout << "found " << (*found)->first << std::endl;
			if (freq == data.size() - 1) {
				data.push_back(std::unordered_set<Key*, PtrHasher, PtrEqual>());
			}
			auto sec = (*found)->second;
			auto new_pair = new Key((*found)->first, sec);
			data[sec].erase(*found);
			hashSet.erase(*found);
			data[++(*new_pair).second].insert(new_pair);
			hashSet.insert(new_pair);
		}
		else {
            //std::cout << "not found" << std::endl;
			key.second = 1;
			data[1].insert(&key);
			data[0].erase(--data[0].end());
		}
	}
};