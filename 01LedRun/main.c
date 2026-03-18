#include <ioCC2530.h>

#define YLED P1_0   // 黄灯
#define BLED P1_1   // 蓝灯

void Delay(unsigned int);	
void InitIO(void);		
void LetStar(void);

void Delay(unsigned int n)
{
    unsigned int i;
    for(i = 0; i < n; i++);
    for(i = 0; i < n; i++);
    for(i = 0; i < n; i++);
    for(i = 0; i < n; i++);
    for(i = 0; i < n; i++);1
}

void InitIO(void)
{
    P1DIR |= 0x3;  // 定义P10、P11为输出
    YLED = 1;       // 低电平有效，熄灯
    BLED = 1;
  
}

void LetStar(void)
{
  BLED = !BLED;           // 闪绿灯
  Delay(10000);
  YLED = !YLED;           // 闪黄灯
  Delay(10000);
}

void main(void)
{
  InitIO();		//初始化LED灯控制IO口	
  while(1)                //死循环
  {             
    LetStar();
  }
}


