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
	typedef std::pair<unsigned long, int> Key;

	struct PtrHasher {
		size_t operator()(const Key *it) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn(it->first);
		}
	};

	struct PtrEqual {
		bool operator()(const Key* lhs, const Key* rhs) const {
            bool tmp = lhs->first == rhs->first;
            return tmp;
		}
	};

	struct Equal {
		bool operator()(const Key& lhs, const Key& rhs) const {
			return lhs.first == rhs.first;
		}
	};

	struct Hasher {
		size_t operator()(const Key &it) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn(it.first);
		}
	};


	struct Generator {
		Generator() : m_value(0) { }
		Key* operator()() { return new Key(m_value++, 0); }
		unsigned long m_value;
	};

	struct SetComparator {
		bool operator() (const Key* lhs, const Key* rhs) {
			return lhs->first < rhs->first;
		}
	};

	struct IteratorHash {
		size_t operator()(const std::list<Key>::iterator& it) const {
			std::hash<unsigned long> hash_fn;
			return hash_fn(it->first);
		}
	};

	struct IteratorEqual
	{
		bool operator()(const std::list<Key>::iterator &lhs, const std::list<Key>::iterator &rhs) {
			return (*lhs).first == (*rhs).first;
		}
	};


	//std::vector<std::set<Key*, PtrHasher, PtrEqual>> data;
	//std::set<Key*, PtrHasher, PtrEqual> hashSet;

	std::vector<std::list<Key>> data;
	std::unordered_set<std::list<Key>::iterator, IteratorHash, IteratorEqual> hashSet;

	Ordered(int _wLen, int _exp) : wLen(_wLen), exp(_exp) {
		init();
	}

	static bool zalupa(const Key* lhs, const Key* rhs) {
		std::cout << lhs->first << "\t" << rhs->first << "\t" << (lhs->first == lhs->second) << std::endl;
		return lhs->first == rhs->first;
	}

	void init() {
		std::random_device rd;
		std::mt19937 re(rd());
		std::uniform_int_distribution<unsigned long> ui(1, (unsigned long)pow(2, wLen));
		data.push_back(std::list<Key>());
		std::unordered_set<Key, Hasher, Equal> base_data;
		if (exp != wLen) {
			while (base_data.size() != (size_t)pow(2, exp)) {
				base_data.insert(Key(ui(re), 0));
				std::cout << base_data.size() << std::endl;
			}
		}
		else {
			assert("ueban nelza tak delat");
		}
		for (const Key& k : base_data) {
			data[0].push_front(std::move(const_cast<Key &>(k)));
		}

		for (auto it = std::begin(data[0]); it != std::end(data[0]); ++it) {
			hashSet.insert(it);
		}

		for (auto &el : hashSet) {
			std::cout << (*el).first << "\t" << (*el).second << std::endl;
		}

		std::cout << "zaebok" << std::endl;
	}

	void find(Key key) {
		//auto found = hashSet.find(&key);
		//std::cout << "lurking for " << key.first << "\t " << key.second << std::endl;
		//if (found != hashSet.end()) {
		//	//std::cout << "We've found element (" << (*found)->first << ", " << (*found)->second << ")" << std::endl;
		//	auto freq = (*found)->second;
		//	if (freq == data.size() - 1) {
		//		data.push_back(std::set<Key*, SetComparator>());
		//	}
		//	auto foundInStack = data[freq].find(*found);
		//	if (foundInStack != data[freq].end()) {
		//		cnt++;
		//		auto new_pair = new Key((*foundInStack)->first, ++(*foundInStack)->second);
		//		data[freq].erase(*found);
		//		hashSet.erase(*found);
		//		data[new_pair->second].insert(new_pair);
		//		hashSet.insert(new_pair);
		//	}
		//	else {
		//		data[freq].erase(*found); 
		//		(*found)->second++;
		//		data[++freq].insert(*found);
		//		data[0].erase(--data[0].end());
		//	}
		//}
		//else {
		//	key.second = 1;
		//	if (data.size() < 2) {
		//		data.push_back(std::set<Key*, SetComparator>());
		//	}
		//	data[1].insert(&key);
		//	data[0].erase(--data[0].end());
		//}
		//for (int i = 0; i < data.size(); i++) {
		//	for (auto it = data[i].begin(); it != data[i].end(); ++it) {
		//		std::cout << "frenq " << i << ":\t" << (*it)->first << "\t" << (*it)->second << std::endl;
		//	}
		//}
		//std::cout << "-------------------------" << std::endl;
	}
};