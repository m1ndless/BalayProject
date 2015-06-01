//
//  LongToBitsetConverter.h
//  BalayProject
//
//  Created by Denis Genalitskiy on 12.05.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//

#ifndef BalayProject_LongToBitsetConverter_h
#define BalayProject_LongToBitsetConverter_h

#include <boost/dynamic_bitset.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>

class LongToBitsetConverter {
private:
    const char* path;
    const char* outPath;
    size_t wLen;
    size_t srcLen;
    std::ifstream infile;
public:
    LongToBitsetConverter(const char* from, const char* to, size_t _srcLen, size_t _wLen) : path(from), outPath(to),
                                                                                        srcLen(_srcLen), wLen(_wLen) {
        infile = std::ifstream(path);
    }
    
    void convert() {
        
        std::ofstream outputFile(outPath);
        unsigned long num;
        auto modulo = 0;
        boost::dynamic_bitset<unsigned long> restBitset;
        while (infile >> num) {
            auto bitset = boost::dynamic_bitset<unsigned long>(srcLen, num);
            std::string str;
            boost::to_string(bitset, str);
            if (srcLen % wLen == 0) {
                auto div = srcLen / wLen;
                int start_index = 0;
                for (int i = 0; i < div; i++, start_index += wLen) {
                    boost::dynamic_bitset<unsigned long> subset(str.substr(start_index, wLen));
                    
                    outputFile << subset.to_ulong() << "\n";
                }
            }
            
            else {
                if (!modulo) {
                    int div = srcLen / wLen;
                    int start_index = 0;
                    for (int i = 0; i < div; i++, start_index += wLen) {
                        boost::dynamic_bitset<unsigned long> subset(str.substr(start_index, wLen));
                        outputFile << subset.to_ulong() << "\n";
                    }
                    modulo = srcLen - start_index; //всегда должно быть четным, продебажить
                    restBitset = boost::dynamic_bitset<unsigned long>(str.substr(start_index, modulo));
                }
                
                else if (modulo == wLen) {
                    outputFile << restBitset.to_ulong() << "\n";
                    modulo = 0;
                    int div = srcLen / wLen;
                    int start_index = 0;
                    for (int i = 0; i < div; i++, start_index += wLen) {
                        boost::dynamic_bitset<unsigned long> subset(str.substr(start_index, wLen));
                        outputFile << subset.to_ulong() << "\n";
                    }
                    modulo = srcLen - start_index; //всегда должно быть четным, продебажить
                    restBitset = boost::dynamic_bitset<unsigned long>(str.substr(start_index, modulo));
                }
                
                else {
                    boost::dynamic_bitset<unsigned long> first(wLen, 0);
                    int cyka = modulo;
                    for (int i = wLen; i >= 0, modulo >= 0; i--) {
                        first[i] = restBitset[modulo--];
                    }
                    
                    int free_bits = srcLen;
                    for (int i = wLen - cyka; i >= 0; i--, free_bits--) {
                        first[i] = bitset[free_bits];
                    }
                    
                    outputFile << first.to_ulong() << "\n";
                    
                    if (free_bits < wLen) {
                        modulo = free_bits + 1;
                        restBitset = boost::dynamic_bitset<unsigned long>(str.substr(srcLen - modulo, modulo));
                        continue;
                    }
                    
                    else {
                        int div = srcLen / wLen;
                        int start_index = free_bits;
                        for (int i = 0; i < div; i++, start_index += wLen) {
                            boost::dynamic_bitset<unsigned long> subset(str.substr(start_index, wLen));
                            outputFile << subset.to_ulong() << "\n";
                        }
                        modulo = srcLen - start_index; //всегда должно быть четным, продебажить
                        restBitset = boost::dynamic_bitset<unsigned long>(str.substr(start_index, modulo));
                    }
                }
            }
        }

    }
};


#endif
