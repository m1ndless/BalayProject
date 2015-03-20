//
//  BitsBuffer.h
//  BalayProject
//
//  Created by Denis Genalitskiy on 03.03.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//

#ifndef __BalayProject__BitsBuffer__
#define __BalayProject__BitsBuffer__

#include <stdio.h>
#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <math.h>


class BitsBuffer {
private:

    unsigned char* buf;
    //razmer buf
    size_t sz;
    //размер слова в битах
    size_t wordsize = 8;
    //текущий байт
    unsigned int currentbyte = 0;
    //текущая позиция в байте (на случай длин слов не кратных восьми)
    unsigned short currentbit = 0;
    
    size_t bytesperread;
    size_t additionalbits;
    
    
    std::string byte_to_binary(int x, int len)
    {
        static char b[9];
        b[0] = '\0';
        
        int z;
        for (z = (int)pow(2, len - 1); z > 0; z >>= 1)
        {
            strcat_s(b, ((x & z) == z) ? "1" : "0");
        }
        
        return b;
    }
    
    
public:
    BitsBuffer(unsigned char* buf, size_t sz) {
        this->buf = buf;
        this->sz = sz;
        
        bytesperread = wordsize / CHAR_BIT;
        additionalbits = wordsize % CHAR_BIT;
    }
    
    boost::dynamic_bitset<> fromCharBuffer(unsigned int currentbyte, unsigned short currentbit) {
        std::string result;
        setNext();
        //подсчитываем колиество полных байт, которые надо взять от текущих значений
        int bytesCount = 0;
        if (wordsize % CHAR_BIT != 0) {
            bytesCount = 1;
            bytesCount += (this->wordsize - (CHAR_BIT - currentbit)) / CHAR_BIT + 1;
            std::string tmp;
            for (int i = currentbyte; i <currentbyte + bytesCount; i++) {
                tmp.append(byte_to_binary(buf[i], CHAR_BIT));
                //std::cout << (int)buf[i] << std::endl;
            }
            result = std::string(tmp.begin() + currentbit, tmp.end() - (CHAR_BIT - this->currentbit));
        }
        
        else {
            bytesCount = wordsize / CHAR_BIT;
            for (int i = currentbyte; i < currentbyte + bytesCount; i++) {
                result.append(byte_to_binary(buf[i], CHAR_BIT));
            }

        }
        return boost::dynamic_bitset<>(result);
    }
    
    boost::dynamic_bitset<> test() {
        //for (int i = 0; i < 10; i++) {
        boost::dynamic_bitset<> t = fromCharBuffer(this->currentbyte, this->currentbit);
        //std::cout << t << "\t" << t.size() << std::endl;
        return t;
        //}
    }
    
    void setNext() {

        //посчитать количество байт с битами, которые надо захватить
        if (currentbit == 0) {
            currentbyte += wordsize / CHAR_BIT;
            currentbit = wordsize % CHAR_BIT;
        }
        else {
            
            //отсчитываем количество полный байт
            currentbyte += wordsize / CHAR_BIT;
            
            //проверяем, залезаем ли мы в следующий байт или нет
            auto tmp = currentbit + wordsize % CHAR_BIT;
            if (tmp > 7) {
                currentbyte++;
            }
            currentbit = (currentbit + (wordsize % CHAR_BIT)) % CHAR_BIT;
        }
    }
    
    boost::dynamic_bitset<>* readNext() {
        
        return new boost::dynamic_bitset<>(8);
    }
    
};

#endif /* defined(__BalayProject__BitsBuffer__) */
