#include <SPI.h>
#include "printf.h"

//ENA短接 全速运行
const int PWM_ENA = 6;
const int INA = 10;
const int INB = 11;
int MOTOR_STATUS = 0;

const int INC = 4;
const int IND  = 5;
int MOTOR_STATUS_YGX = 0;

void setup()
{
  pinMode(8,OUTPUT);
  Serial.begin(9600);
  pinMode(INA ,OUTPUT);
  pinMode(INB ,OUTPUT);

  pinMode(INC ,OUTPUT);
  pinMode(IND ,OUTPUT);
}

void PWM_PLUS()
{
  const int rate = 700;
  digitalWrite(PWM_ENA,HIGH);
  delayMicroseconds(rate);
  digitalWrite(PWM_ENA, LOW);
  delayMicroseconds(1000 - rate);
}

void ControlMotor()
{
  switch(MOTOR_STATUS)
  {
    case 0:
    digitalWrite(INA,LOW);
    digitalWrite(INB,LOW);
    break;
    case 1:
    digitalWrite(INA,HIGH);
    digitalWrite(INB,LOW);
    break;
    case 2:
    digitalWrite(INA,LOW);
    digitalWrite(INB,LOW);
    break;
    case 3:
    digitalWrite(INA,LOW);
    digitalWrite(INB,HIGH);
    break;
    default:
    MOTOR_STATUS = 0;
    }
}

void ControlMotor_ygx()
{
  switch(MOTOR_STATUS_YGX)
  {
    case 0:
    digitalWrite(INC,LOW);
    digitalWrite(IND,LOW);
    break;
    case 1:
    digitalWrite(INC,HIGH);
    digitalWrite(IND,LOW);
    break;
    case 2:
    digitalWrite(INC,LOW);
    digitalWrite(IND,LOW);
    break;
    case 3:
    digitalWrite(INC,LOW);
    digitalWrite(IND,HIGH);
    break;
    default:
    MOTOR_STATUS_YGX = 0;
    }
}

void loop()
{
  if(Serial.available())
    {
      char receive = Serial.read();
      if(receive == 'l')
      {
        MOTOR_STATUS = 3;
      }
      if(receive == 'r')
      {
        MOTOR_STATUS = 1;
      }
      if(receive == 'm')
      {
        MOTOR_STATUS = 2;
      }

      if(receive == 'f')
      {
        MOTOR_STATUS_YGX = 3;
        digitalWrite(8,HIGH);
      }
      if(receive == 'b')
      {
        MOTOR_STATUS_YGX = 1;
        digitalWrite(8,HIGH);
      }
      if(receive == 's')
      {
        MOTOR_STATUS_YGX = 2;
        digitalWrite(8,LOW);
      }
      Serial.write(receive);
    }
  //PWM_PLUS();
  ControlMotor();
  ControlMotor_ygx();
}
