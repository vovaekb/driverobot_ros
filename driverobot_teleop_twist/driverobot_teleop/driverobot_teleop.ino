#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>

using namespace std;


// Robot wheel pins
int m11 = 3;
int m12 = 6;
int m21 = 9;
int m22 = 10;


ros::NodeHandle nh;

void turnLeft()
{
    nh.loginfo("Turn left");
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
    nh.loginfo("Turn right");
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
    nh.loginfo("Go forward");
    // go forward
    analogWrite(m11, 150); 
    analogWrite(m12, 0);
    analogWrite(m21, 150);
    analogWrite(m22, 0);
    
    //delay(15000);
}

void stop()
{
    nh.loginfo("Stop");
    analogWrite(m11, 0);
    analogWrite(m12, 0);
    analogWrite(m21, 0);
    analogWrite(m22, 0);
}


void messageCb(const geometry_msgs::Twist& message) 
{
    // read linear velocity
    geometry_msgs::Vector3 linear = message.linear;
    float forward_vel = (float)linear.x;
    
    if(forward_vel == 0)
    { 
        stop();
        return; 
    }
    
    // read angular velocity
    geometry_msgs::Vector3 angular = message.angular;
    float ang_vel = (float)angular.z;
    
    // if velocity is positive turn left
    if(ang_vel > 0)
    {
        turnLeft();
    }
    // if velocity is negative turn right
    else if(ang_vel < 0)
    {
        turnRight();
    }
    else 
    {
        goForward();
    }
}


ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &messageCb);

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
