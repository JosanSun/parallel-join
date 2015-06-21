#include <algorithm>
#include <iostream>

#include "joinAlgorithms.h"

void welcome()
{
    std::cout << "Start hash join(serial version)\n";
}

void join(unsigned int *primaryKey, int primaryKeyLen, 
        unsigned int *foreignKey, int foreignKeyLen,
        std::list<std::pair<unsigned int, unsigned int> > &result)
{
    // [0, 16M)
    const int limit = 1 << 24;
    std::list<unsigned int> **keys = (std::list<unsigned int> **)calloc(limit, 
            sizeof(std::list<unsigned int>*));
    for (int i = 0; i < foreignKeyLen; ++i) {
        unsigned int j = foreignKey[i];
        if (keys[j] == nullptr) {
            keys[j] = new std::list<unsigned int>();
        }
        keys[j]->push_back(i);
    }

    for (int i = 0; i < primaryKeyLen; ++i) {
        unsigned int j = primaryKey[i];
        std::list<unsigned int> *res = keys[j];
        if (res != nullptr) {
            for (unsigned int value : *res) {
                result.push_back(std::make_pair(j, value));
            }
        }
    }
    //for (int i = 0; i < foreignKeyLen; ++i) {
        //int j = foreignKey[i];
        //if (keys[j] != nullptr) {
            //delete keys[j];
            //keys[j] = nullptr;
        //}
    //}
    //free(keys);
}
