#ifndef __COMMON_H_
#define __COMMON_H_

#define NAMEMAX 256	//�ļ�����󳤶�

#define UNIFORM 0
#define ZIPFHIGH 1
#define ZIPFLOW 2
#define DATA_TYPE UNIFORM

const char filenames[][NAMEMAX] = {
    "DataKey128K",
#if DATA_TYPE == ZIPFLOW
    "DataZipfLow1M","DataZipfLow2M","DataZipfLow4M","DataZipfLow8M",
    "DataZipfLow16M",
#elif DATA_TYPE == ZIPFHIGH
    "DataZipfHigh1M","DataZipfHigh2M","DataZipfHigh4M","DataZipfHigh8M",
    "DataZipfHigh16M",
#else
    "DataUniform1M","DataUniform2M","DataUniform4M","DataUniform8M",
#endif
};
const int data_len[] = {
    1<<17,
    1<<20, 1<<21, 1<<22, 1<<23,
#if DATA_TYPE != UNIFORM
    1<<24,
#endif
};

//��������,���������ļ�������Ӧ������
void loaddata(int index, unsigned int* key,int *keyLen);

#endif
