#ifndef __COMMON_H_
#define __COMMON_H_

#define NAMEMAX 256	//文件名最大长度

const char filenames[][NAMEMAX] = {
    "DataKey128K",
    //	"DataUniform16M","DataUniform32M","DataUniform64M","DataUniform128M",
    //	"DataUniform256M","DataUniform512M","DataUniform1024M",
    //  "DataZipfHigh16M","DataZipfHigh32M","DataZipfHigh64M","DataZipfHigh128M",
    //  "DataZipfHigh256M","DataZipfHigh512M",
    "DataZipfLow1M","DataZipfLow2M","DataZipfLow4M","DataZipfLow8M",
    "DataZipfLow16M",
};
const int data_len[] = {
    1<<17,
    //1<<24, 1<<25, 1<<26, 1<<27,1<<28,1<<29,1<<30,
    //1<<24, 1<<25, 1<<26, 1<<27,1<<28,1<<29,
    1<<20, 1<<21, 1<<22, 1<<23, 1<<24,
};

//读入数据,根据上面文件载入相应的数据
void loaddata(int index, unsigned int* key,int *keyLen);

#endif
