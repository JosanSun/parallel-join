#ifndef __COMMON_H_
#define __COMMON_H_

#define NAMEMAX 256	//�ļ�����󳤶�

const char filenames[][NAMEMAX] = {
    "DataKey0M16M",
    //	"DataUniform16M","DataUniform32M","DataUniform64M","DataUniform128M",
    //	"DataUniform256M","DataUniform512M","DataUniform1024M",
    //  "DataZipfHigh16M","DataZipfHigh32M","DataZipfHigh64M","DataZipfHigh128M",
    //  "DataZipfHigh256M","DataZipfHigh512M",
    "DataZipfLow16M","DataZipfLow32M","DataZipfLow64M","DataZipfLow128M",
    "DataZipfLow256M","DataZipfLow512M"
};
const int data_len[] = {
    1<<24,
    //1<<24, 1<<25, 1<<26, 1<<27,1<<28,1<<29,1<<30,
    //1<<24, 1<<25, 1<<26, 1<<27,1<<28,1<<29,
    1<<24, 1<<25, 1<<26, 1<<27,1<<28,1<<29
};

//��������,���������ļ�������Ӧ������
void loaddata(int index, unsigned int* key,int *keyLen);

#endif
