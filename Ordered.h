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
	static int cnt;
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
			//std::cout << "We've found element (" << (*found)->first << ", " << (*found)->second << ")" << std::endl;
			auto freq = (*found)->second;
			if (freq == data.size() - 1) {
				data.push_back(std::unordered_set<Key*, PtrHasher, PtrEqual>());
			}
			auto foundInStack = data[freq].find(*found);
			if (foundInStack != data[freq].end()) {
				cnt++;
				auto new_pair = new Key((*foundInStack)->first, ++(*foundInStack)->second);
				data[freq].erase(*found);
				hashSet.erase(*found);
				data[new_pair->second].insert(new_pair);
				hashSet.insert(new_pair);
			}
			else {
				data[freq].erase(*found); 
				(*found)->second++;
				data[++freq].insert(*found);
				data[0].erase(--data[0].end());
			}
		}
		else {
			key.second = 1;
			if (data.size() < 2) {
				data.push_back(std::unordered_set<Key*, PtrHasher, PtrEqual>());
			}
			data[1].insert(&key);
			data[0].erase(--data[0].end());
		}
	}
};