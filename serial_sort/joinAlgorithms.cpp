#include <iostream>
#include <algorithm>

#include "joinAlgorithms.h"

void welcome()
{
    std::cout << "Start merge sort join(serial version)\n";
}

void join(unsigned int *primaryKey, int primaryKeyLen, 
        unsigned int *foreignKey, int foreignKeyLen,
        std::list<std::pair<unsigned int, unsigned int> > &result)
{
    std::sort(primaryKey, primaryKey + primaryKeyLen);
    std::sort(foreignKey, foreignKey + foreignKeyLen);

    int i = 0;
    int j = 0;
    while (i < primaryKeyLen && j < foreignKeyLen) {
        if (primaryKey[i] < foreignKey[j]) {
            ++i;
        }
        else if (primaryKey[i] == foreignKey[j]) {
            int k = j;
            do {
                result.push_back(std::make_pair(primaryKey[i], k));
                ++k;
            } while (k < foreignKeyLen && primaryKey[i] == foreignKey[k]);
            ++i;
        }
        else {
            ++j;
        }
    }
}
