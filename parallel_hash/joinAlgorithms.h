#ifndef JOINALGORITHMS_H
#define JOINALGORITHMS_H
#include <list>

void welcome();
void join(unsigned int *primaryKey, int primaryKeyLen, 
        unsigned int *foreignKey, int foreignKeyLen,
        std::list<std::pair<unsigned int, unsigned int> > &result);

#endif /* JOINALGORITHMS_H */
