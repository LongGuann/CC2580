
#include <ioCC2530.h>

#define YLED   P1_1
#define BLED   P1_0
#define KEY1   P1_2

#define LEDOPEN   1
#define LEDCLOSE  0

void Delay(unsigned int);	
void InitKey(void); 
void InitKeyINT(void);

unsigned char Keyvalue = 0 ;                //定义变量记录按键动作
unsigned int  KeyTouchtimes = 0 ;           //定义变量记录按键次数

void Delay(unsigned int ms)
{
      unsigned int i, j;
      for(i = 0; i < ms; i++)
      for(j = 0; j < 1600; j++);
}

void InitKeyINT(void)
{
  P1INP |= 0x04; //上拉    
  
  P1IEN |= 0X04;   //P1.2设置为中断方式
  PICTL |= 0X01;   //下降沿触发
  EA = 1;
  IEN2 |= 0X10;   // P1.2设置为中断方式;

  P1IFG |= 0x00;   //初始化中断标志位
  
}

void InitIO(void)
{
    P1DIR |= 0x03; //P1.0、P1.1定义为输出
    BLED = LEDCLOSE;
    YLED = LEDCLOSE;	//LED灯初始化为灭
}

#pragma vector = P1INT_VECTOR
__interrupt void P1_ISR(void)
{
  if(KEY1 == 0)    //低电平有效
  {
      Delay(10);
      if(KEY1==0)
      {  //有按键按下
         while(KEY1 == 0);
         Delay(5);
      }
  }
  //LED1=~LED1;             //改变LED1状态
  P1IFG = 0;             //清中断标志 
  P1IF = 0;             //清中断标志 
  if (KeyTouchtimes >= 4)
        KeyTouchtimes = 1;
  else
        KeyTouchtimes ++;  // 按键次数加1       
  P1IF = 0;             //清中断标志
}

void main(void)
{
  InitIO();	
  InitKeyINT();   //初始化按键中断
   	     
  while(1)
  {

    switch (KeyTouchtimes)
    {
    case 1:   // 亮黄灯
        YLED = LEDOPEN;                
        BLED = LEDCLOSE;
        break;
    case 2:   // 跑马灯
        YLED = !YLED; 
        BLED = !BLED; 
        Delay(100); 
        break;
    case 3: // 全部亮
        YLED = LEDOPEN;
        BLED = LEDOPEN; 
        break;
    case 4:   // 全部熄灭
        BLED = LEDCLOSE;
        YLED = LEDCLOSE;
        break;
     }
   }
}
