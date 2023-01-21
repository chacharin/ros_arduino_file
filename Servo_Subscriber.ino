#include <Servo.h> 
#include <ros.h>
#include <std_msgs/Int16.h>
 
ros::NodeHandle  nh;
 
Servo servo_1;
Servo servo_2;
Servo servo_3;
 
void servo_cb_1( const std_msgs::Int16& cmd_msg)
{
  servo_1.write(cmd_msg.data); 
}
 
void servo_cb_2( const std_msgs::Int16& cmd_msg)
}
  servo_2.write(cmd_msg.data); 
}
 
void servo_cb_3( const std_msgs::Int16& cmd_msg)
{
  servo_3.write(cmd_msg.data); 
}

ros::Subscriber<std_msgs::Int16> sub_1("servo_1", servo_cb_1);
ros::Subscriber<std_msgs::Int16> sub_2("servo_2", servo_cb_2);
ros::Subscriber<std_msgs::Int16> sub_3("servo_3", servo_cb_3);
 
void setup(){
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
 
  nh.initNode();
  nh.subscribe(sub_1);
  nh.subscribe(sub_2);
  nh.subscribe(sub_3);
 
  servo_1.attach(9); //attach it to pin 9
  servo_2.attach(10); //attach it to pin 10
  servo_3.attach(11); //attach it to pin 11
}
 
void loop(){
  nh.spinOnce();
  delay(1);
}
