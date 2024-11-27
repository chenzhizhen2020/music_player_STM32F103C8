#include "music.h"
#include "mbed.h"
#include "i2c_oled.h"
PwmOut pin(A6);
DigitalIn pin2(A5,PullDown);
DigitalIn pin3(A7,PullDown);
void play(int x,double t){
    pin.period_us(1000000/x);
    wait_us(1000000*t);
}
#define C0 (2)

#define C1_LOW  (262)
#define C2_LOW  (294)
#define C3_LOW  (330)
#define C4_LOW  (349)
#define C5_LOW  (392)
#define C6_LOW  (440)
#define C7_LOW  (494)

#define C1      (523)
#define C2      (587)
#define C3      (659)
#define C4      (698)
#define C4S     (740)//C4#
#define C5      (784)
#define C5S     (831)//C5#
#define C6      (880)
#define C7      (988)

#define C1_HIGH (1046)
#define C2_HIGH (1175)
#define C3_HIGH (1318)
#define C4_HIGH (1397)
#define C5_HIGH (1568)
#define C6_HIGH (1760)
#define C7_HIGH (1976)

#define WHOLE (1)
#define HALF (0.5)
#define QUARTER (0.25)
#define EIGHTH (0.125)
#define SIXTEENTH (0.0625)

int tune[]=                 //根据简谱列出各频率
{
    C6,C7,
   
    C1_HIGH,C7,C1_HIGH,C3_HIGH,//
    C7,C3,C3,
    C6,C5,C6,C1_HIGH,
    C5,C0,C3,C3,
    C4,C3,C4,C1_HIGH,
    C3,C0,C1_HIGH,C1_HIGH,C1_HIGH,
    C7,C4S,C4S,C7,
   
    C7,C0,C6,C7,//
    C1_HIGH,C7,C1_HIGH,C3_HIGH,
    C7,C0,C3,C3,
    C6,C5,C6,C1_HIGH,
    C5,C0,C3,
    C4,C1_HIGH,C7,C7,C1_HIGH,
    C2_HIGH,C2_HIGH,C3_HIGH,C1_HIGH,C0,
   
    C1_HIGH,C7,C6,C6,C7,C5S,//
    C6,C0,C1_HIGH,C2_HIGH,
    C3_HIGH,C2_HIGH,C3_HIGH,C5_HIGH,
    C2_HIGH,C0,C5,C5,
    C1_HIGH,C7,C1_HIGH,C3_HIGH,C0,C0,
    C6,C7,C1_HIGH,C7,C2_HIGH,C2_HIGH,
    C1,C5,C5,C0,
   
    C4_HIGH,C3_HIGH,C2_HIGH,C1_HIGH,//
    C3_HIGH,
    C3_HIGH,C0,C3_HIGH,
    C6_HIGH,C5_HIGH,C5_HIGH,
    C3_HIGH,C2_HIGH,C1_HIGH,C0,C1_HIGH,
    C2_HIGH,C1_HIGH,C2_HIGH,C2_HIGH,C5_HIGH,
    C3_HIGH,C0,C3_HIGH,
    C6_HIGH,C5_HIGH,
    C3_HIGH,C2_HIGH,C1_HIGH,C0,C1_HIGH,
    C2_HIGH,C1_HIGH,C2_HIGH,C2_HIGH,C7,

    C6,C0,C6,C7,
   
    C6
};
float durt[]=                   //根据简谱列出各节拍
{
    EIGHTH,EIGHTH,
   
    QUARTER + EIGHTH,EIGHTH,QUARTER,QUARTER,
    QUARTER + QUARTER + QUARTER,EIGHTH,EIGHTH,
    QUARTER + EIGHTH,EIGHTH,QUARTER,QUARTER,
    QUARTER + QUARTER,QUARTER,EIGHTH,EIGHTH,
    QUARTER + EIGHTH,EIGHTH,EIGHTH,QUARTER+EIGHTH,
    QUARTER + QUARTER,QUARTER,EIGHTH,EIGHTH,EIGHTH,
    QUARTER + EIGHTH,EIGHTH,QUARTER,QUARTER,
   
    QUARTER+QUARTER,QUARTER,EIGHTH,EIGHTH,
    QUARTER+EIGHTH,EIGHTH,QUARTER,QUARTER,
    QUARTER+QUARTER,QUARTER,EIGHTH,EIGHTH,
    QUARTER+EIGHTH,EIGHTH,QUARTER,QUARTER,
    QUARTER+QUARTER+QUARTER,EIGHTH,EIGHTH,
    QUARTER,EIGHTH,EIGHTH,EIGHTH,QUARTER,
    EIGHTH,EIGHTH,EIGHTH,QUARTER,QUARTER,
   
    QUARTER,EIGHTH,EIGHTH,EIGHTH,QUARTER,QUARTER,
    QUARTER+QUARTER,QUARTER,EIGHTH,EIGHTH,
    QUARTER+EIGHTH,QUARTER,QUARTER,QUARTER,
    QUARTER+QUARTER,QUARTER,EIGHTH,EIGHTH,
    EIGHTH,EIGHTH,QUARTER,QUARTER,
    QUARTER+QUARTER,QUARTER,QUARTER,
    EIGHTH,EIGHTH,QUARTER,QUARTER,EIGHTH,EIGHTH,
    QUARTER+EIGHTH,EIGHTH,QUARTER,QUARTER,
   
    QUARTER,QUARTER,QUARTER,QUARTER,
    QUARTER+QUARTER+QUARTER,
    QUARTER+QUARTER,QUARTER,QUARTER,
    QUARTER+QUARTER,QUARTER,QUARTER,
    EIGHTH,EIGHTH,QUARTER,EIGHTH,EIGHTH,
    QUARTER,EIGHTH,EIGHTH,EIGHTH,QUARTER,
    QUARTER+QUARTER,QUARTER,QUARTER,
    QUARTER+QUARTER,QUARTER+QUARTER,
    EIGHTH,EIGHTH,QUARTER+QUARTER,EIGHTH,EIGHTH,
    QUARTER,EIGHTH,EIGHTH,EIGHTH,QUARTER,
    QUARTER+QUARTER,QUARTER,EIGHTH,EIGHTH,
   
    QUARTER+QUARTER+QUARTER
   
};

double Time = 2;
int length;
void setup()
{
  // put your setup code here, to run once:

    length=sizeof(tune)/sizeof(tune[0]);   //计算长度
}
void loop()
{
    pin.write(0.5f);int bj=0,bj2=0;
    for(int i=0;i<length;i++)
    {
        if(pin3==1){
            if(!bj2){
                bj2=1;
                OLED_ClearBuffer();
                OLED_ShowStringBuffered(0,0,"Pausing",7,16,1);
                OLED_SendBuffer();
            }
            pin.period_ms(1000);wait_us(50);
            continue;--i;
        }
        else{
            if(bj2){
                bj2=0;
                OLED_ClearBuffer();
                OLED_ShowStringBuffered(0,0,"Playing",7,16,1);
                OLED_SendBuffer();
            }
        }
        if(pin2==1&&pin3==0){
            if(!bj){
                bj=1;
                OLED_ClearBuffer();
                OLED_ShowStringBuffered(0,0,"Playing*2",9,16,1);
                OLED_SendBuffer();
            }
            Time=1;
        }
        else if(pin3==0){
            if(bj){
                bj=0;
                OLED_ClearBuffer();
                OLED_ShowStringBuffered(0,0,"Playing",7,16,1);
                OLED_SendBuffer();
            }
            Time=2;
        }
        if(tune[i]!=0)
        {
            play(tune[i],Time*durt[i]);
        }  
        else
        {
            pin.period_ms(1000);
            wait_us(Time*durt[i]*1000000);
        }
    }
}