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

	struct Hasher {
		size_t operator()(const Key &it) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn(it.first);
		}
	};

	struct PtrEqual {
		size_t operator()(const Key* lhs, const Key* rhs) const {
			return lhs->first == lhs->first;
		}
	};

	struct Equal
	{
		bool operator()(const Key &lhs, const Key &rhs) {
			return lhs.first == rhs.first;
		}
	};


	std::vector<std::unordered_set<Key, Hasher, Equal>> data;
	std::unordered_set<Key, Hasher, Equal> hashSet;
	size_t wLen;
	int exp;

	Ordered(size_t _wLen, int _exp) : wLen(_wLen), exp(_exp) {
		init();
	}

	void init() {
		data.push_back(std::unordered_set<Key, Hasher, Equal>());
		for (int i = 0; i < pow(2, exp); i++) {
			//auto pair = new std::pair<unsigned long, int>(rand() % 1000, 0);
			auto pair = Key(i, 0);
			hashSet.insert(pair);

			data[0].insert(pair);
			//auto delta = pair->second - data.size() - 1;
			//if (delta > 0) {
			//	for (int i = 0; i < delta; i++) {
			//		data.push_back(std::unordered_set<Key>());
			//	}
			//}
			
		}
		std::cout << "Done!" << std::endl;
	}

	void find(Key key) {
		auto found = hashSet.find(key);

		if (found != hashSet.end()) {
			//std::cout << "getting element from vector" << std::endl;
			auto freq = (*found).second;
			if (freq == data.size() - 1) {
				data.push_back(std::unordered_set<Key, Hasher, Equal>());
			}
			auto sec = (*found).second;
			auto new_pair = Key((*found).first, sec);
			data[(*found).second].erase(found);
			data[new_pair.second].insert(new_pair);
		}

		else {
			std::cout << "cyka" << std::endl;
		}
	}

	void out() {
		for (int i = 0; i < data.size(); i++) {
			std::cout << "\t"<< "freq " << i << std::endl;
			for (auto it = std::begin(data[i]); it != std::end(data[i]); ++it) {
				std::cout << (*it).first << "\t" << (*it).second << std::endl;
			}
			std::cout << "-------------------" << std::endl;
		}
		
	}

};