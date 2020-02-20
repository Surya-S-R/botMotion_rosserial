#include <ros.h>
#include <std_msgs/String.h>



#define LM1 4
#define LM2 3
#define RM1 5
#define RM2 6
#define ENl 9      // ENABLE
#define ENr 10     // ENABLE


int speed1 = 100;
int speed2 = 90;
int speed4 = 80;
int speed3 = 60;

byte BotState = 0;
int runDelay = 250;

ros::NodeHandle  nh;

void MoveCallback( const std_msgs::String& cmdMove){
  toggle();     //for debugging
  
  if(cmdMove.data[0] == 'F'){
   nh.loginfo("Front");
   Forward();
  }

  if(cmdMove.data[0] == 'B'){
   nh.loginfo("Back");
   Back();
  }

  if(cmdMove.data[0] == 'R'){
   nh.loginfo("Right");
   TurnRight();
  }

  if(cmdMove.data[0] == 'L'){
   nh.loginfo("Left");
   TurnLeft();
  }

  
  toggle();     //for debugging

  if(BotState != 0){
    Stop();
  }
}

ros::Subscriber<std_msgs::String> sub("Bot_movement_cmd", &MoveCallback );

void setup()
{ 
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}


//---------------------------------------------------------------------

void Forward(){
  SetDrivPinFRONT(speed1);
  delay(runDelay);
}

void Back(){
  SetDrivPinBACK(speed1);
  delay(runDelay);
}

void TurnRight(){
  SetDrivPinRight(speed1);
  delay(runDelay);
}

void TurnLeft(){
  SetDrivPinLeft(speed1);
  delay(runDelay);
}

void Stop(){
  SetDrivPinHalt();
}
//---------------------------------------------------------------------

void toggle(){   //just to toggle LED for debugging purpose
  digitalWrite(13, HIGH-digitalRead(13));
}
//---------------------------------------------------------------------

void SetDrivPinFRONT(int pwml)
{
  SetDrivPinFRONT( pwml, pwml);
}


void SetDrivPinFRONT(int pwml,int pwmr)
{
  if (BotState!=1){ SetDrivPinHalt();}
  analogWrite(ENl,pwml);
  analogWrite(ENr,pwmr);
 
  PORTD = (PORTD & B10110111) | B00110000;
  BotState = 1;
}

void SetDrivPinBACK(int pwml)
{
 SetDrivPinBACK( pwml, pwml);
}

void SetDrivPinBACK(int pwml,int pwmr)
{
  if (BotState!=2){SetDrivPinHalt();}
  analogWrite(ENl,pwml);
  analogWrite(ENr,pwmr);
  PORTD = (PORTD & B11001111) | B01001000; 
  BotState = 2;
}

void SetDrivPinHalt()
{
  PORTD = (PORTD & B10000111); 
  BotState = 0;
}

void SetDrivPinLeft(int pwml)
{
   SetDrivPinLeft( pwml, pwml);
}

void SetDrivPinLeft(int pwml,int pwmr)
{
  if (BotState!=4){SetDrivPinHalt();}
  analogWrite(ENl,pwml);
  analogWrite(ENr,pwmr);
  PORTD = (PORTD & B10101111) | B00101000; BotState = 4;
}

void SetDrivPinRight(int pwml)
{
   SetDrivPinRight( pwml, pwml);
}

void SetDrivPinRight(int pwml,int pwmr)
{
  if (BotState!=3){SetDrivPinHalt();}
  analogWrite(ENl,pwml);
  analogWrite(ENr,pwmr);
  PORTD = (PORTD & B11010111) | B01010000; BotState = 3;
}

void BraketheBot()
{
  int speed3=60;
  byte IpH = ((~(PORTD & B01111000))&B01111000) | (PORTD & B10000111);
  if ( BotState != 0)
  {
    SetDrivPinHalt();
    //delay(5);
    analogWrite(ENl, speed3);
    analogWrite(ENr, speed3);
    for (int i = 0; i <= 5; i++)
    {
      PORTD = IpH;
      delay(7);
      SetDrivPinHalt();
      delay(5);
    }
  }
  analogWrite(ENl, 0); //PE3
  analogWrite(ENr, 0); //PB4
  BotState = 0;
}
