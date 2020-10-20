#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <iostream>
#include "stdlib.h"
#include "time.h"



int main(int argc, char *argv[]) {
  ros::init(argc, argv, "move_turtlesim");

  int shapeChoice;

  std::cout << "\nPlease choose one of the following shapes\n";
  std::cout << "1: Square\n";
  std::cout << "2: triangle\n";
  std::cout << "3: penis\n";
  std::cout << "Answer = ";
  std::cin >> shapeChoice;
 
  switch (shapeChoice)
  {
  case 1: std::cout << "\nform valgt er firkant"; break;
  case 2: std::cout << "\nform valgt er trekant"; break;
  case 3: std::cout << "\nform valgt er penis"; break;
  default: std::cout << "\nthehell"; break;
  }

float chosenSize = 0.0;
std::cout << "\nPlease choose a size from 1 to 11";
 std::cout << "\nAnswer = ";
  std::cin >> chosenSize;

  srand (time(NULL));
  int randomRed = rand() % 255 + 1;
  ROS_INFO("Random Red number: %d", randomRed);
  int randomGreen = rand() % 255 + 1;
  ROS_INFO("Random Green number: %d", randomGreen);
  int randomBlue = rand() % 255 + 1;
  ROS_INFO("Random Blue number: %d", randomBlue);

  int randomThicc = rand() % 30 + 6;
  ROS_INFO("Random thickness: %d", randomThicc);
  
  float box_size = ros::param::param("~box_size", chosenSize);
  int offsetB = 5.5-box_size/2;

  int randomOffset = rand() % offsetB + 1;
  ROS_INFO("Random offset: %d", randomOffset);
//Koden er sat til aldrig at bygge ud af boksen, men mangler at sætte den i plus minus, så den ikke altid bygger tættere og tættere på højre hjørne


if (shapeChoice == 1) {
  ros::NodeHandle nh;
  ros::Duration(2.0).sleep();
  ros::service::waitForService("/turtle1/teleport_absolute", -1);

  ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
  ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");


  turtlesim::SetPen pen_srv;
  pen_srv.request.off = true;
  pen_client.call(pen_srv);

  turtlesim::TeleportAbsolute srv;

  srv.request.x = randomOffset+5.5-box_size/2;
  srv.request.y = randomOffset+5.5-box_size/2;
  teleport_client.call(srv);

  pen_srv.request.off = false;
  pen_srv.request.width = randomThicc;
  pen_srv.request.r = randomRed;
  pen_srv.request.g = randomGreen;
  //pen_srv.request.b = randomBlue;
  //blå gør den lidt svær at se en gang i mellem
  pen_client.call(pen_srv);

  srv.request.x = randomOffset+5.5-box_size/2;
  srv.request.y = randomOffset+5.5+box_size/2;
  teleport_client.call(srv);

  srv.request.x = randomOffset+5.5+box_size/2;
  srv.request.y = randomOffset+5.5+box_size/2;
  teleport_client.call(srv);

  srv.request.x = randomOffset+5.5+box_size/2;
  srv.request.y = randomOffset+5.5-box_size/2;
  teleport_client.call(srv);

  srv.request.x = randomOffset+5.5-box_size/2;
  srv.request.y = randomOffset+5.5-box_size/2;
  teleport_client.call(srv);

  pen_srv.request.off = true;
  pen_client.call(pen_srv);

  srv.request.x = 5.5+randomOffset;
  srv.request.y = 5.5+randomOffset;
  teleport_client.call(srv);

  pen_srv.request.off = false;
  pen_srv.request.width = 4;
  pen_srv.request.r = 10;
  pen_srv.request.g = 130;
  pen_srv.request.b = 200;
  pen_client.call(pen_srv);
}
 else if (shapeChoice == 2) {
  ros::NodeHandle nh;
  ros::Duration(2.0).sleep();
  ros::service::waitForService("/turtle1/teleport_absolute", -1);

  ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
  ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");


  turtlesim::SetPen pen_srv;
  pen_srv.request.off = true;
  pen_client.call(pen_srv);

  turtlesim::TeleportAbsolute srv;

  srv.request.x = randomOffset+5.5-box_size/2;
  srv.request.y = randomOffset+5.5-box_size/2;
  teleport_client.call(srv);

  pen_srv.request.off = false;
  pen_srv.request.width = randomThicc;
  pen_srv.request.r = randomRed;
  pen_srv.request.g = randomGreen;
  //pen_srv.request.b = randomBlue;
  //blå gør den lidt svær at se en gang i mellem
  pen_client.call(pen_srv);

  srv.request.x = randomOffset+5.5;
  srv.request.y = randomOffset+5.5+box_size/2;
  teleport_client.call(srv);

  srv.request.x = randomOffset+5.5+box_size/2;
  srv.request.y = randomOffset+5.5-box_size/2;
  teleport_client.call(srv);

  srv.request.x = randomOffset+5.5-box_size/2;
  srv.request.y = randomOffset+5.5-box_size/2;
  teleport_client.call(srv);

  pen_srv.request.off = true;
  pen_client.call(pen_srv);

  srv.request.x = 5.5+randomOffset;
  srv.request.y = 5.5+randomOffset;
  teleport_client.call(srv);

  pen_srv.request.off = false;
  pen_srv.request.width = 4;
  pen_srv.request.r = 10;
  pen_srv.request.g = 130;
  pen_srv.request.b = 200;
  pen_client.call(pen_srv);
   
 }
 else {

  ros::NodeHandle nh;
  ros::Duration(2.0).sleep();
  ros::service::waitForService("/turtle1/teleport_absolute", -1);

  ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
  ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");


  turtlesim::SetPen pen_srv;
  pen_srv.request.off = true;
  pen_client.call(pen_srv);

  turtlesim::TeleportAbsolute srv;

  srv.request.x = 5.5;
  srv.request.y = 5.5;
  teleport_client.call(srv);

  pen_srv.request.off = false;
  pen_srv.request.width = randomThicc;
  pen_srv.request.r = randomRed;
  pen_srv.request.g = randomGreen;
  //pen_srv.request.b = randomBlue;
  //blå gør den lidt svær at se en gang i mellem
  pen_client.call(pen_srv);

  srv.request.x = 7;
  srv.request.y = 4;
  teleport_client.call(srv);

  srv.request.x = 8.5;
  srv.request.y = 5.5;
  teleport_client.call(srv);

  srv.request.x = 7;
  srv.request.y = 7;
  teleport_client.call(srv);

srv.request.x = 7;
  srv.request.y = 10;
  teleport_client.call(srv);

srv.request.x = 5.5;
  srv.request.y = 11;
  teleport_client.call(srv);

srv.request.x = 4;
  srv.request.y = 10;
  teleport_client.call(srv);

srv.request.x = 4;
  srv.request.y = 7;
  teleport_client.call(srv);

srv.request.x = 2.5;
  srv.request.y = 5.5;
  teleport_client.call(srv);

srv.request.x = 4;
  srv.request.y = 4;
  teleport_client.call(srv);

 srv.request.x = 5.5;
  srv.request.y = 5.5;
  teleport_client.call(srv);

  pen_srv.request.off = true;
  pen_client.call(pen_srv);

  pen_srv.request.off = false;
  pen_srv.request.width = 4;
  pen_srv.request.r = 10;
  pen_srv.request.g = 130;
  pen_srv.request.b = 200;
  pen_client.call(pen_srv);
   
 }

  return 0;
}