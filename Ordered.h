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


	//struct Generator {
	//	Generator() : m_value(0) { }
	//	Key* operator()() { return Key(m_value++, 0); }
	//	unsigned long m_value;
	//};

	struct SetComparator {
		bool operator() (const Key& lhs, const Key& rhs) {
			return lhs->first < rhs->first;
		}
	};

	struct IteratorHash {
		size_t operator()(const std::list<Key>::iterator& it) const {
			std::hash<unsigned long> hash_fn;
			//std::cout << "HASHIM: " << ((*it)->first);
			return hash_fn((*it)->first);
		}
	};

	struct IteratorEqual
	{
		bool operator()(const std::list<Key>::iterator &lhs, const std::list<Key>::iterator &rhs) {
			return (*lhs)->first == (*rhs)->first;
		}
	};


	//std::vector<std::set<Key*, PtrHasher, PtrEqual>> data;
	//std::set<Key*, PtrHasher, PtrEqual> hashSet;

	std::vector<std::list<Key>> data;
	std::unordered_set<std::list<Key>::iterator, IteratorHash, IteratorEqual> hashSet;
	std::list<Key>::iterator it;

	Ordered(int _wLen, int _exp) : wLen(_wLen), exp(_exp) {
		this->wLen = _wLen;
		this->exp = _exp;
		init();
		std::cout << "test" << std::endl;
	}

	//static bool zalupa(const Key* lhs, const Key* rhs) {
	//	std::cout << lhs->first << "\t" << rhs->first << "\t" << (lhs->first == lhs->second) << std::endl;
	//	return lhs->first == rhs->first;
	//}

	void init() {
		std::random_device rd;
		std::mt19937 re(rd());
		std::uniform_int_distribution<unsigned long> ui(0, (unsigned long)pow(2, wLen) - 1);
		data.push_back(std::list<Key>((size_t)pow(2, exp)));
		std::unordered_set<Key, Hasher, Equal> base_data;
		if (exp != wLen) {
			while (base_data.size() != (size_t)pow(2, exp)) {
				base_data.insert(Key(new std::pair<unsigned long, int>(ui(re), 0)));
			}
		}
		//else {
		//	assert("ueban nelza tak delat");
		//}

		auto kostil = Key(new std::pair<unsigned long, int>((unsigned long)pow(2, wLen), 0));
		base_data.insert(kostil);


		std::copy(std::begin(base_data), std::end(base_data), std::back_inserter(data[0]));
		//for (Key& k : base_data) {
		//	data[0].push_front(k);
		//}

		std::cout << "zaebok" << std::endl;

		for (auto iter = std::begin(data[0]); iter != std::end(data[0]); ++iter) {
			hashSet.insert(iter);
		}

		it = std::find(std::begin(data[0]), std::end(data[0]), kostil);
		//for (auto &el : hashSet)
		//	std::cout << (*el)->first << "\t" << (*el)->second << "\t" << &el << std::endl;
		outhash();
		std::cout << "zaebok" << std::endl;
	}

	void outhash() {
		for (auto it = std::begin(hashSet); it != std::end(hashSet); ++it) {
			std::cout << (*it)->get()->first << "\t" << (*it)->get()->second << "\t" << &it << std::endl;
		}
		std::cout << "------------" << std::endl;
	}

	void find(Key& key) {






		//*it = Key(key);
		//outhash();
		//auto found = hashSet.find(it);
		//if (found != hashSet.end()) {
		//	auto freq = (*found)->get()->second;
		//	freq++;
		//	std::cout << "Freq is " << freq << std::endl;
		//	std::cout << "lurking for " << (*found)->get()->first << "\t" << (*found)->get()->second << "\t"  <<&found << std::endl;
		//	if (freq == data.size()) {
		//		std::cout << (freq == data.size() - 1) << std::endl;
		//		data.push_back(std::list<Key>());
		//	}
		//	data[freq].push_front(Key(new std::pair<unsigned long, int>((*it)->first, freq)));
		//	auto inData = data[freq].erase(*found);
			
		//}

		//if (found == hashSet.end()) {
		//	std::cout << "lurking for but not found: " << (*it)->first << "\t" << (*it)->second << "\t " << *it << std::endl;
			//auto freq = (*it)->second;
			//if (freq == data.size() - 1) {
			//	data.push_back(std::list<Key>());
			//}
			//std::cout << data.size() << "SUKAAAAAAAAAAAAAA" <<  std::endl;
			//auto toDelete = ((--std::end(data[freq])) == it) ? --std::end(data[freq]) : ----std::end(data[freq]);
			////data[freq].erase(toDelete);
			//freq++;

			//for (auto &l : data) {
			//	std::cout << "freq is: " << std::endl;
			//	for (auto &el : l) {
			//		std::cout << el->first << "\t" << el->second << "\t" << el << std::endl;
			//	}
			//	std::cout << "------------" << std::endl;
			//}


			//data[freq].push_front(Key(new std::pair<unsigned long, int>((*it)->first, freq)));
		//}

		//for (auto &l : data) {
		//	std::cout << "freq is: " << std::endl;
		//	for (auto &el : l) {
		//		std::cout << el->first << "\t" << el->second << "\t" << el << std::endl;
		//	}
		//	std::cout << "------------" << std::endl;
		//}

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