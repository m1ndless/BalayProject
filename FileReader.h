//
//  FileReader.h
//  BalayProject
//
//  Created by Denis Genalitskiy on 03.03.15.
//  Copyright (c) 2015 Denis Genalitskiy. All rights reserved.
//

#ifndef __BalayProject__FileReader__
#define __BalayProject__FileReader__

#include <stdio.h>
#include <fstream>
#include "BitsBuffer.h"

class FileReader {
private:
    size_t size;
    const char* path;
    std::ifstream ifs;
    
    //in bytes
    void filesize() {
        ifs.seekg(0, ifs.end);
        this->size = this->ifs.tellg();
        ifs.seekg(0, ifs.beg);
    }

    
public:
    FileReader(const char* path) {
        this->path = path;
        this->ifs = std::ifstream(path, std::ifstream::binary);
        filesize();
    }
    
    BitsBuffer* readNext(bool& isNext) {
//        char buf[256];
//        return new BitsBuffer(buf);
        
        //если размер файла больше 50 мегабайт(ов?), делим файл на 10 кусков
        if (this->size > 52428800)
        {
            return nullptr;
        }
        //читаем весь файл целиком
        else {
            isNext = false;
            unsigned char *buf = new unsigned char[this->size];
            ifs.read((char*)buf, this->size);
            return new BitsBuffer(buf, this->size);
        }
    }
    
    

    
};



#endif /* defined(__BalayProject__FileReader__) */
