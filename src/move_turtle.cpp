#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <iostream>
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "move_turtle");

  ros::NodeHandle nh;
  ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1);
  ros::Rate loop_rate(10);

  geometry_msgs::Twist twist;
//  int count = 0;
 ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");


  turtlesim::SetPen pen_srv;
  pen_srv.request.off = false;
  pen_client.call(pen_srv);

  pen_srv.request.width = 2;
  pen_srv.request.r = 150;
  pen_srv.request.g = 150;

  int userInput = 1;
    int shapeChoice = 1;

std::cout << "\nPlease choose a shape";
std::cout << "\nSquare = 1";
std::cout << "\nCircle = 2";
std::cout << "\nBenis = 3";
std::cout << "\nAnswer = ";

std::cin >> shapeChoice;

if (shapeChoice != 3)
{
  std::cout << "\nYou chose wrong and got Penis anyway";
  shapeChoice = 3;
}

while(ros::ok() && userInput!=0){

switch (shapeChoice)
{
case 1:
    for(int i=0;i<10;i++){
      twist.linear.x = 3.0;
      twist.angular.z = 0.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
    for(int i=0;i<M_PI_2*10;i++){
      twist.linear.x = 0.0;
      twist.angular.z = 1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
    for(int i=0;i<10;i++){
      twist.linear.x = 3.0;
      twist.angular.z = 0.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
    for(int i=0;i<M_PI_2*10;i++){
      twist.linear.x = 0.0;
      twist.angular.z = 1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
    for(int i=0;i<10;i++){
      twist.linear.x = 3.0;
      twist.angular.z = 0.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
    for(int i=0;i<M_PI_2*10;i++){
      twist.linear.x = 0.0;
      twist.angular.z = 1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
    for(int i=0;i<10;i++){
      twist.linear.x = 3.0;
      twist.angular.z = 0.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
    twist.linear.x = 0.0;
      twist.angular.z = 0.0;
      vel_pub.publish(twist);

    break;
case 2:

for(int i=0;i<M_PI*20;i++){
      twist.linear.x = 1.0;
      twist.angular.z = 1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
    twist.linear.x = 0.0;
      twist.angular.z = 0.0;
      vel_pub.publish(twist);
    break;
case 3:
    for(int i=0;i<2*M_PI*10*0.75;i++){
      twist.linear.x = 1.0;
      twist.angular.z = 1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
     for(int i=0;i<2*M_PI*0.25*10;i++){
      twist.linear.x = 0.0;
      twist.angular.z = -1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
      for(int i=0;i<20;i++){
      twist.linear.x = 1.0;
      twist.angular.z = 0.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
      for(int i=0;i<M_PI*10;i++){
      twist.linear.x = 1.0;
      twist.angular.z = 1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
       for(int i=0;i<20;i++){
      twist.linear.x = 1.0;
      twist.angular.z = 0.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
      for(int i=0;i<2*M_PI*0.25*10;i++){
      twist.linear.x = 0.0;
      twist.angular.z = -1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
      for(int i=0;i<2*M_PI*0.75*10;i++){
      twist.linear.x = 1.0;
      twist.angular.z = 1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
    }
  twist.linear.x = 0.0;
      twist.angular.z = 0.0;
      vel_pub.publish(twist);
    break;
default:
    break;
}


/*
    while (count<10){
      twist.linear.x = 1.0;
      vel_pub.publish(twist);
      loop_rate.sleep();
      count++;
    }
    */
    std::cout << "\ncontinue (yes=1/no=0)? ";
    std::cin >> userInput;

//    if (userInput){
//      count =0;
//    }

  }

  return 0;
}