#include <iostream>
#include "joinAlgorithms.h"

void welcome()
{
    std::cout << "Start nested loop join(serial version)\n";
}

void join(unsigned int *primaryKey, int primaryKeyLen, 
        unsigned int *foreignKey, int foreignKeyLen,
        std::list<unsigned int> &result)
{
    for (int i = 0; i < foreignKeyLen; ++i) {
        if (i < primaryKeyLen) {
            result.push_back(primaryKey[i]);
        }
        else {
            result.push_back(foreignKey[i]);
        }
    }
}
