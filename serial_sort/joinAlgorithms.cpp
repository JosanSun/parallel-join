#include <iostream>
#include <algorithm>

#include "joinAlgorithms.h"

void welcome()
{
    std::cout << "Start nested loop join(serial version)\n";
}

void join(unsigned int *primaryKey, int primaryKeyLen, 
        unsigned int *foreignKey, int foreignKeyLen,
        std::list<std::pair<unsigned int, unsigned int> > &result)
{
    std::sort(primaryKey, primaryKey + primaryKeyLen);
    std::sort(foreignKey, foreignKey + foreignKeyLen);
    for (int i = 0, j = 0; i < primaryKeyLen && j < foreignKeyLen; ++i, ++j) {
        int k = j;
        while (primaryKey[i] == foreignKey[k]) {
            result.push_back(std::make_pair(primaryKey[i], k));
            ++k;
        }
    }
}
