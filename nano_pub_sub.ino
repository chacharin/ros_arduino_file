#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include<Servo.h>
Servo S3; Servo S5; Servo S6; Servo S9; Servo S10; Servo S11;

ros::NodeHandle nh; 
std_msgs::Float32 sensorData;
ros::Publisher pub("/topic_A", &sensorData);


void callback( const std_msgs::Int16 &recived_msg){
  if(recived_msg.data == 0){digitalWrite(13, 0); S3.write(90);}   
  else if (recived_msg.data == 1){digitalWrite(13, 1); S3.write(180);}  
}
ros::Subscriber<std_msgs::Int16> sub("/topic_B", &callback);


void setup() {
   S3.attach(3);S5.attach(5);S6.attach(6);S9.attach(9); S10.attach(10);S11.attach(11);delay(1000);
   S3.write(90); delay(200); S5.write(90); delay(200); S6.write(90); delay(200); 
   S9.write(90); delay(200); S10.write(90); delay(200); S11.write(90); delay(200);
   pinMode(13, OUTPUT);
   pinMode(A0,INPUT);
   nh.initNode();
   nh.subscribe(sub);
   nh.advertise(pub);
}
 
void loop() {
    sensorData.data = analogRead(A0);
    pub.publish(&sensorData);
    delay(1);
    nh.spinOnce();
}
