#define BLINKER_PRINT Serial
#define BLINKER_BLE

#include <Servo.h>
#include <Blinker.h>
#include <Wire.h>
#include <paj7620.h>

#define GES_REACTION_TIME    500
#define GES_ENTRY_TIME      800
#define GES_QUIT_TIME     1000

Servo myservo;

int pos = 0;

//新建组件
BlinkerButton kai("btn-epj");
BlinkerButton guan("btn-ien");
BlinkerButton Stop("btn-663");

//按下按键即会执行该函数
void kai_callback(const String & stata){
  BLINKER_LOG("get button state: ", stata);
  myservo.write(0);

  Blinker.vibrate();
  }
void guan_callback(const String & stata)
{
  BLINKER_LOG("get button stata: ", stata);
  myservo.write(180);


  Blinker.vibrate();
  }

void Stop_callback(const String & stata)
{
  BLINKER_LOG("get button stata: ", stata);
  myservo.write(90);

  Blinker.vibrate();
  }

void setup() {
  paj7620Init();
  
  Serial.begin(9600);
  myservo.attach(9);
  
  Blinker.begin();
  kai.attach(kai_callback);
  guan.attach(guan_callback);
  Stop.attach(Stop_callback);
  

}

void loop() {
  Blinker.run();

  uint8_t data = 0;
  
  //手势传感器
  delay(GES_ENTRY_TIME);
  paj7620ReadReg(0x43, 1, &data); 
  if(data == GES_RIGHT_FLAG)
    {
      myservo.write(0);
      }
  delay(GES_ENTRY_TIME);
  paj7620ReadReg(0x43, 1, &data);
  if(data == GES_LEFT_FLAG)
    {
      myservo.write(180);
      }
}
