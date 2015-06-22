#include <algorithm>
#include <iostream>
#include <iterator>
#include <thread>
#include <vector>

#include "joinAlgorithms.h"

using std::list;
using std::pair;
using std::vector;
typedef list<pair<unsigned int, unsigned int> > pairList;

void welcome()
{
    std::cout << "Start hash join(parallel version)\n";
}

void addThreadLocalResult(int i, vector<pairList> &threadLocalResults, 
        list<unsigned int> **keys, unsigned int *primaryKey, int primaryKeyLenPiece)
{
    int floor = primaryKeyLenPiece * i;
    int ceiling = primaryKeyLenPiece * i + primaryKeyLenPiece;
    for (int j = floor; j < ceiling; ++j) {
        unsigned int k = primaryKey[j];
        list<unsigned int> *res = keys[k];
        if (res != nullptr) {
            for (unsigned int value : *res) {
                threadLocalResults[i].push_back(std::make_pair(k, value));
            }
        }
    }
}

void join(unsigned int *primaryKey, int primaryKeyLen, 
        unsigned int *foreignKey, int foreignKeyLen,
        list<pair<unsigned int, unsigned int> > &result)
{
    const int maxThreadNum = std::thread::hardware_concurrency();
    // threadNum must be 2n - 1
    const int threadNum = std::min(1, maxThreadNum - 1);
    if (primaryKeyLen % (threadNum + 1) != 0 || 
            (foreignKeyLen % (threadNum + 1) != 0)) {
        std::cout << "threadNum must be 2n - 1\n";
        return;
    }

    // [0, 16M)
    const int limit = 1 << 24;
    list<unsigned int> **keys = (list<unsigned int> **)calloc(limit, 
            sizeof(list<unsigned int>*));
    for (int i = 0; i < foreignKeyLen; ++i) {
        unsigned int j = foreignKey[i];
        if (keys[j] == nullptr) {
            keys[j] = new list<unsigned int>();
        }
        keys[j]->push_back(i);
    }

    vector<std::thread> pool(threadNum);
    vector<pairList> threadLocalResults(threadNum);
    const int primaryKeyLenPiece = primaryKeyLen / (threadNum + 1);
    for (int i = 0; i < threadNum; ++i) {
        pool[i] = std::thread(addThreadLocalResult, i, std::ref(threadLocalResults), 
                keys, primaryKey, primaryKeyLenPiece);
    }
    for (int i = primaryKeyLenPiece * threadNum; i < primaryKeyLen; ++i) {
        unsigned int j = primaryKey[i];
        list<unsigned int> *res = keys[j];
        if (res != nullptr) {
            for (unsigned int value : *res) {
                result.push_back(std::make_pair(j, value));
            }
        }
    }

    for (int i = 0; i < threadNum; ++i) {
        pool[i].join();
        std::move(threadLocalResults[i].cbegin(), threadLocalResults[i].cend(),
                std::back_inserter(result));
    }
    // programme will exit soon, so no need to free the memory
    // a trick
    // delete []threadLocalResult;
    //for (int i = 0; i < foreignKeyLen; ++i) {
        //int j = foreignKey[i];
        //if (keys[j] != nullptr) {
            //delete keys[j];
            //keys[j] = nullptr;
        //}
    //}
    //free(keys);
}
