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
#include <algorithm>
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
		bool operator()(const Key* lhs, const Key* rhs) const {
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
		//hashSet = std::unordered_set<Key*, PtrHasher, PtrEqual>((size_t)pow(2, wLen));
	}

	bool zalupa(const Key* lhs, const Key* rhs) {
		return lhs->first == rhs->first;
	}

	void init() {

		std::mt19937_64 gen{ std::random_device()() };
		std::uniform_int_distribution<int> uid(0, (size_t)pow(2, exp));

		std::vector<Key*> vector((size_t)pow(2, exp));
		int pos = 0;
		do {
			std::generate(std::begin(vector) + pos, std::end(vector), [&uid, &gen]() -> Key* { return new Key(uid(gen), 0); });
			auto it = std::unique(vector.begin(), vector.end(), zalupa);
			vector.resize(std::distance(std::begin(vector), it));
			pos = vector.size();
			std::cout << pos << std::endl;
			vector.resize((size_t)pow(2, exp));
		} while (pos != (size_t)pow(2, exp));

		std::vector<unsigned long> v;
		for (auto it = std::begin(vector); it != std::end(vector); ++it) {
			v.push_back((*it)->first);
		}
		std::sort(v.begin(), v.end());
		for (auto it = v.begin(); it != end(v); ++it) {
			std::cout << *it << std::endl;
		}



		auto tmp = std::unordered_set<Key*, PtrHasher, PtrEqual>(std::make_move_iterator(std::begin(vector)), std::make_move_iterator(std::end(vector)));

		data.push_back(std::unordered_set<Key*, PtrHasher, PtrEqual>());
		for (int i = 0; i < pow(2, exp); i++) {
			auto pair = new Key(i, 0);
			//hashSet.insert(pair);
			//data[0].insert(pair);
		}
		std::cout << "zaebok" << std::endl;
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