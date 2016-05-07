/*
 * rosserial Servo Control Example
 * This sketch controls hobby R/C servos using ROS and the arduino
*/

#define USE_USBCON

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle nh;

Servo servo;

// Indices of components in joy message
int linear_ind = 1;
int angular_ind = 0;

void servo_cb(const sensor_msgs::Joy& joy)
{
  float angular = joy.axes[angular_ind];
  float linear = joy.axes[linear_ind];
  int cur_pos = servo.read();
  
  if(angular > 0)
  { 
    nh.loginfo("Turn left");
    cur_pos = cur_pos - 20;
    servo.write(cur_pos);
  }
  else if(angular < 0)
  { 
    nh.loginfo("Turn right");
    cur_pos = cur_pos + 20;
    servo.write(cur_pos);
  }
  
  char* log_msg;
//  sprintf(log_msg, "angular: %.3f", angular);
//  nh.loginfo(log_msg);
}


ros::Subscriber<sensor_msgs::Joy> sub("joy", &servo_cb);

void setup()
{
  pinMode(13, OUTPUT);
  
  nh.initNode();
  nh.subscribe(sub);
  
  servo.attach(9); // attach it to pin 9
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
