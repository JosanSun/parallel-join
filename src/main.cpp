#include <iostream>

#include <joinAlgorithms.h>

#include "common.h"


int main()
{
    welcome();
    int primaryKeyLen;
    // primary key comes from DataKey0M16M
    unsigned int *primaryKey = new unsigned int[data_len[0]];
    // 取值范围 [0, 16M)，数量 16M
    loaddata(0, primaryKey, &primaryKeyLen);
    std::cout << "length of primary key is " << primaryKeyLen << std::endl;

    int idx = 1;
    // foreign key comes from one of other dataset
    unsigned int *foreignKey = new unsigned int[data_len[idx]];
    int foreignKeyLen;
    // 取值范围 [0, 16M)， 数量：取决于使用的数据集
    loaddata(idx, foreignKey, &foreignKeyLen);
    std::cout << "length of foreign key is " << foreignKeyLen << std::endl;

    struct timespec tw1;
    clock_gettime(CLOCK_MONOTONIC, &tw1);

    // join算法实现要求：采用自然连接，将外键中数值跟主键相同的索引跟主键连接在一起
    // 所以输出值是一个大小不定（最大为外键数据集的数量）的list，其中first为主键，
    // second为原外键的索引。
    std::list<std::pair<unsigned int, unsigned int> > result;
    join(primaryKey, primaryKeyLen, foreignKey, foreignKeyLen, result);

    struct timespec tw2;
    clock_gettime(CLOCK_MONOTONIC, &tw2);
    double posix_wall = 1000.0 * tw2.tv_sec + 1e-6 * tw2.tv_nsec
                       - (1000.0 * tw1.tv_sec + 1e-6 * tw1.tv_nsec);
    std::cout << "Wall time: " << posix_wall << " ms\n";

    // 这里输出join的结果的元组数
    std::cout << "The number of join result is " << result.size() << std::endl;

    delete []primaryKey;
    delete []foreignKey;
    return 0;
}
