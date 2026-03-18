#include <ioCC2530.h>

#define YLED   P1_0 
#define BLED   P1_1	  

#define KEY1   P1_2

#define LED_ON   1
#define LED_OFF  0

#define uint  unsigned int
#define uchar unsigned char

void Delay(uint);	
void InitIO(void);
void InitKey(void); 
uchar KeyScan(void);
void ControlLED(uint);
void Key_ControlLED(void);

uchar Keyvalue = 0 ;           // 按键动作
uint  KeyTouchtimes = 0 ;      // 按键次数

void Delay(unsigned int ms)
{
      unsigned int i, j;
      for(i = 0; i < ms; i++)
      for(j = 0; j < 1600; j++);
}

void InitKey(void)
{
  P1SEL &= ~0X04;  // 设置P1.2为通用IO口
  P1DIR &= ~0X04;  // 设置P1.2为输入模式
  P1INP |= 0x04;   //上拉      
}

void InitIO(void)
{
    P1DIR |= 0x3; //定义P1.0、P1.1为输出
    YLED = LED_OFF;
    BLED = LED_OFF;	    //  熄灯
}

uchar KeyScan(void)
{
  if(KEY1 == 0)    //低电平有效
  {
    Delay(10);
      if(KEY1==0)
      {  //有按键按下
         while(KEY1 == 0);
         Delay(5);
         return 1;
      }
  }
  return 0;
}

void ControlLED(uint count)
{
    switch(count)
    {
        case 1:   // 蓝灯亮
            YLED = LED_OFF;
            BLED = LED_ON;
            break;
            
        case 2:   // 黄灯亮
            YLED = LED_ON;
            BLED = LED_OFF;
            break;
            
        case 3:   // 双灯亮
            YLED = LED_ON;
            BLED = LED_ON;
            break;
            
        case 4:   // 双灯灭，重置计数
            YLED = LED_OFF;
            BLED = LED_OFF;
            KeyTouchtimes = 0;
            break;
            
        default: 
            KeyTouchtimes = 1;
            break;
    }
}

void Key_ControlLED(void)    // 按键控制LED
{
    Keyvalue = KeyScan();       //读取按键动作
    if (Keyvalue==1)
    { 
       KeyTouchtimes ++;    //记录按键次数
       if(KeyTouchtimes > 4)
       {
          KeyTouchtimes = 1;
       }      
       ControlLED(KeyTouchtimes);
     }
}

void main(void)
{
   InitKey();             //初始化按键控制IO口
   InitIO();		//初始化LED灯控制IO口	
  
  while(1)
  {
     Key_ControlLED();
   }
}


