#include "mbed.h"
#include "i2c_oled.h"
#include "music.h"
int main(){
    DigitalOut VCC(D2);VCC=1;
    ThisThread::sleep_for(100ms);
    OLED_Init();
    OLED_ClearBuffer();
    OLED_ShowStringBuffered(0,0,"Playing",7,16,1);
    OLED_SendBuffer();
    setup();
    while(1)loop();
    return 0;
}