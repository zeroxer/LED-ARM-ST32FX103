#ifndef _SHOWWAVE_H_
#define _SHOWWAVE_H_
extern float OutData[4];
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);
void OutPut_Data(void);
void showwave(float a,float b,float c,float d);

#endif
