#include<zlib.h>
int zcompress(Bytef *data, uLong ndata,Bytef *zdata, uLong *nzdata);
int gzcompress(Bytef *data, uLong ndata,Bytef *zdata, uLong *nzdata);
int zdecompress(Byte *zdata, uLong nzdata,Byte *data, uLong *ndata);
int httpgzdecompress(Byte *zdata, uLong nzdata,Byte *data, uLong *ndata);
int gzdecompress(Byte *zdata, uLong nzdata,Byte *data, uLong *ndata);
#define BUF_SIZE 65535