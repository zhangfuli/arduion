#include <Stepper.h>
#define STEPS 64


Stepper stepper(STEPS, 8, 10, 9, 11);

//记录蓝牙串口接收的数据
String rec = "";

const int office2Btn = 5;
const int office2Light = 4;
int button2State = 0;
bool on2off = LOW;

const int office1Btn = 13;
const int office1Light = 12;
int button1State = 0;
bool on1off = LOW;
void setup(){
  Serial.begin(38400);
  Serial1.begin(38400);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(office2Light, OUTPUT);
  pinMode(office2Btn, INPUT);
  pinMode(office1Light, OUTPUT);
  pinMode(office1Btn, INPUT);
  
  stepper.setSpeed(500);
  stopFan();
 
}
void loop(){
  while(Serial1.available()){
    rec += char(Serial1.read());
    delay(2);    
  }
  if(rec.length()>0){
    Serial.println(rec);
    if(rec == "office1"){
       digitalWrite(office1Light,HIGH);
       startFan();
       rotating();
    }else if(rec == "office2"){
      digitalWrite(office2Light,HIGH);
      rotating();
   }
    rec = "";
      
  }
  
  button2State = digitalRead(office2Btn);
  button1State = digitalRead(office1Btn);
  if(button2State==LOW || button1State==LOW){
    delay(10); //然后延时一段时间，
    if(digitalRead(office2Btn)==HIGH){
      digitalWrite(office2Light,on2off);  //写入当前LED状态onoff，
      on2off=(!on2off); //然后LED状态反转，以便下一次使用。
      delay(10);  //延时一段时间，防止按钮突然断开再按下。
      while(digitalRead(office2Btn)==HIGH) //判断按钮状态，如果仍然按下的话，等待松开。防止一直按住导致LED输出端连续反转
      {
        delay(1);
      }
    }
    if(digitalRead(office1Btn)==HIGH)
    {
      digitalWrite(office1Light,on1off);  //写入当前LED状态onoff，
      on1off=(!on1off); //然后LED状态反转，以便下一次使用。
      delay(10);  //延时一段时间，防止按钮突然断开再按下。
      while(digitalRead(office1Btn)==HIGH) //判断按钮状态，如果仍然按下的话，等待松开。防止一直按住导致LED输出端连续反转
      {
        delay(1);
      }
    }
  }
}
//步进电机旋转一圈
void rotating(){
   stepper.step(2048);
}
void startFan(){
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}
void stopFan(){
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
}

