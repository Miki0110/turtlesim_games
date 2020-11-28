#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <iostream>
#include "stdlib.h"
#include "time.h"



int main(int argc, char *argv[]) {
  ros::init(argc, argv, "move_turtlesim");
 
  srand (time(NULL));
  int randomRed = rand() % 255 + 1;
  ROS_INFO("Random Red number: %d", randomRed);
  int randomGreen = rand() % 255 + 1;
  ROS_INFO("Random Green number: %d", randomGreen);
  int randomBlue = rand() % 255 + 1;
  ROS_INFO("Random Blue number: %d", randomBlue);
  int randomPlacement[2] = {rand() % (6-4 + 1) + 4,rand() % (6-4 + 1) + 4};
  ROS_INFO("Random start: x = %d, y = %d", randomPlacement[0],randomPlacement[1]);

  ros::NodeHandle nh;
  ros::Duration(2.0).sleep();
  ros::service::waitForService("/turtle1/teleport_absolute", -1);
  ros::Rate loop_rate(10);
  ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
  ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");


  turtlesim::SetPen pen_srv;
  turtlesim::TeleportAbsolute srv;
  loop_rate.sleep();
  pen_srv.request.off = true;
  pen_client.call(pen_srv);
  srv.request.x = 5.5;
  srv.request.y = 5.5;
  teleport_client.call(srv);
  loop_rate.sleep();

  pen_srv.request.off = false;
  pen_srv.request.width = 1.0;
  pen_srv.request.r = randomRed;
  pen_srv.request.g = randomGreen;
  pen_client.call(pen_srv);
  loop_rate.sleep();
//moving to a random point
  srv.request.x = randomPlacement[0];
  srv.request.y = randomPlacement[0];
  teleport_client.call(srv);
  loop_rate.sleep();
//get the angle from the center
double x_distance = randomPlacement[0] - 5.5;
double y_distance = randomPlacement[1] - 5.5;
double heading =atan2(y_distance,x_distance);
ROS_INFO("heading (%2f)", heading);
int points = 10;
double length = 3.0;
double xPoint[points];
double yPoint[points];

xPoint[0] = randomPlacement[0];
yPoint[0] = randomPlacement[1];

for (int i=1;i<10+1;){
  //first point
  xPoint[i] = xPoint[i-1]+length*cos(heading);
  yPoint[i] = yPoint[i-1]+length*sin(heading);

  //second point
  xPoint[i+1] = xPoint[i]+1.0*cos(heading-M_PI/2);
  yPoint[i+1] = yPoint[i]+1.0*sin(heading-M_PI/2);

  //third point
  xPoint[i+2] = xPoint[i+1]-length*cos(heading);
  yPoint[i+2] = yPoint[i+1]-length*sin(heading);

  //fourth point
  xPoint[i+3] = xPoint[i+2]+1.0*cos(heading-M_PI/2);
  yPoint[i+3] = yPoint[i+2]+1.0*sin(heading-M_PI/2);
i = i+4;
}

for (int i =1;i<10+1;i++){
  loop_rate.sleep();
  srv.request.x = xPoint[i];
  srv.request.y = yPoint[i];
  teleport_client.call(srv);
}

  return 0;
}