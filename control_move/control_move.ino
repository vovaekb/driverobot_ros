#include <ros.h>
#include <std_msgs/UInt16.h>

using namespace std;

/* Robot wheel pins */
int m11 = 3;
int m12 = 6;

int m21 = 9;
int m22 = 10;


ros::NodeHandle nh;


void turnLeft()
{
    // turn left
    analogWrite(m21, 150); 
    analogWrite(m22, 0);
    analogWrite(m11, 0);
    analogWrite(m12, 0);
    delay(3000); 
    goForward();
}

void turnRight()
{
    // turn right
    analogWrite(m21, 0);
    analogWrite(m22, 0);
    analogWrite(m11, 150); 
    analogWrite(m12, 0);
    delay(3000); 
    goForward();
}

void goForward()
{
    // go forward
    analogWrite(m11, 150); 
    analogWrite(m12, 0);
    analogWrite(m21, 150); 
    analogWrite(m22, 0);
    
    //delay(15000);
}


void messageCb(const std_msgs::UInt16& message) 
{
  int shift_val = int(message.data);
  
  char* log_msg;
  if(shift_val < 0) log_msg = "Left";
  else log_msg = "Right";
  
  nh.loginfo(log_msg);
}


ros::Subscriber<std_msgs::UInt16> sub("line_shift", &messageCb);

void setup()
{
  nh.initNode();
  nh.subscribe(sub);
  
  Serial.begin(57600);
}

void loop()
{
  nh.spinOnce();
  delay(100);
}
