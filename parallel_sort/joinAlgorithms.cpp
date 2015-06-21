#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

#include "joinAlgorithms.h"

void welcome()
{
    std::cout << "Start merge sort join(parallel version)\n";
}

void join(unsigned int *primaryKey, int primaryKeyLen, 
        unsigned int *foreignKey, int foreignKeyLen,
        std::list<std::pair<unsigned int, unsigned int> > &result)
{
    const int maxThreadNum = std::thread::hardware_concurrency();
    // threadNum must be 2n - 1
    const int threadNum = std::max(1, maxThreadNum - 1);
    if (primaryKeyLen % (threadNum + 1) != 0 || 
            (foreignKeyLen % (threadNum + 1) != 0)) {
        std::cout << "threadNum must be 2n - 1\n";
        return;
    }
    const int primaryKeyPiece = primaryKeyLen / (threadNum + 1);
    const int foreignKeyPiece = foreignKeyLen / (threadNum + 1);
    std::vector<std::thread> pool(threadNum);
    for (int i = 0; i < threadNum; ++i) {
        // skip the first piece, it will be computed in main thread
        int j = i + 1;
        pool[i] = std::thread([&]{
            std::sort(primaryKey + primaryKeyPiece * j, 
                primaryKey + primaryKeyPiece * (j + 1));
            std::sort(foreignKey + foreignKeyPiece * j, 
                foreignKey + foreignKeyPiece * (j + 1));
        });
    }
    std::sort(primaryKey, primaryKey + primaryKeyPiece);
    std::sort(foreignKey, foreignKey + foreignKeyPiece);
    for (int i = 0; i < threadNum; ++i) {
        pool[i].join();
        int j = i + 1;
        std::inplace_merge(primaryKey, primaryKey + primaryKeyPiece * j,
               primaryKey + primaryKeyPiece * (j + 1));
        std::inplace_merge(foreignKey, foreignKey + foreignKeyPiece * j,
               foreignKey + foreignKeyPiece * (j + 1));
    }

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
