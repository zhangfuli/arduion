#include"ioCC2530.h"
#include"variable.h"

//115200 8N1
void UartInitial()
{
  PERCFG = 0x00;
  P0SEL = 0x0c;
  P2DIR &= ~0xc0;
   U0CSR |= 0x80;//设置串口
 // U0UCR = 0x00;
  U0GCR |= 11;
  U0BAUD |= 216;
  U0CSR |= 0x40;
  UTX0IF = 0;
  
}


void UartSend(uchar infor)
{
  U0DBUF = infor;
  while(UTX0IF == 0);
  UTX0IF = 0;
}

//串口发送字符串函数			
void UartSend_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}

