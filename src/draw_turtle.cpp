#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <iostream>
#include "stdlib.h"
#include "time.h"
bool temp = 0;

int randomNumber(int maxN, int minN){
    srand (time(NULL));

    int randomNumber = rand() % (maxN-minN+1) + minN;

    //ROS_INFO("Random number: %d", randomNumber);
    return randomNumber;
}
void initTurtlePosition(float x, float y, ros::ServiceClient teleport_client, ros::ServiceClient pen_client, turtlesim::TeleportAbsolute srv, turtlesim::SetPen pen_srv){
  pen_srv.request.off = true;
  pen_client.call(pen_srv);
  srv.request.x = x;
  srv.request.y = y;
  teleport_client.call(srv);
  pen_srv.request.off = false;
  pen_srv.request.width = 2;
  pen_client.call(pen_srv);
}

void moveTurtle(float x, float y, ros::ServiceClient teleport_client, turtlesim::TeleportAbsolute srv){
  srv.request.x = x;
  srv.request.y = y;
  teleport_client.call(srv);
}

bool itIntersects(int max_angle,int x1, int y1, int x2, int y2){

        double x_distance = x1 - x2;
        double y_distance = y1 - y2;
        double header = atan2(y_distance, x_distance);
        double angular_difference = header - temp;
        header = temp;
  if (angular_difference > M_PI && angular_difference < (-M_PI))
    {
        return false;
    }
else
  {
    return true;
  }
  ROS_INFO("\nAngle: %f", angular_difference);
}
void swapValue(int val1, int val2){
    int temp = val1;
    val1 = val2;
    val2 = temp;
}


int main(int argc, char *argv[]) {
  ros::init(argc, argv, "draw_turtle");
  ros::NodeHandle nh;
  ros::service::waitForService("/turtle1/teleport_absolute", -1);
  ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
  turtlesim::TeleportAbsolute srv;
  ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
  turtlesim::SetPen pen_srv;
  ros::Rate loop_rate(2);

  float startX = 5.544445, startY = 5.544445;
  if(argc>1){
    startX = atof(argv[1]);
    startY = atof(argv[2]);
  }

  initTurtlePosition(startX, startY,teleport_client, pen_client, srv, pen_srv);
  loop_rate.sleep();

  const int sizeCoordA = 5;
  const int sizeCoordB = 2;
  int coordinatesX[sizeCoordA+1];
  int coordinatesY[sizeCoordA+1]; 

for(int i=0; i<sizeCoordA+3; i++){
  coordinatesX[i] = randomNumber(10, 3);
  ros::Duration(1.0).sleep();
  coordinatesY[i] = randomNumber(10, 3);
  ros::Duration(1.0).sleep();
    }
    bool sorted = false;
while (!sorted)
{

for(int i=0; i<sizeCoordA+1; i++){
  
  int intersection = itIntersects(130, coordinatesX[i], coordinatesY[i], coordinatesX[i+1], coordinatesY[i+1]);
  
  if (intersection = true){
    swapValue(coordinatesX[i+1], coordinatesX[i]);
    swapValue(coordinatesY[i+1], coordinatesY[i]);
    ROS_INFO("\nsortting");
  }
    }

sorted = true;
for(int i=0; i<sizeCoordA; i++){
  //std::cout << "(" << coordinatesX[i] << ", " << coordinatesY[i] << ") ";
  int intersection = itIntersects(130, coordinatesX[i], coordinatesY[i], coordinatesX[i+1], coordinatesY[i+1]);
  
  if (intersection = true){
     sorted = false;
    ROS_INFO("\nfailed sort");
  }
}
}

for(int i=0; i<sizeCoordA+1; i++){
std::cout << "(" << coordinatesX[i] << ", " << coordinatesY[i] << ") ";
  }

    for(int i=0; i<sizeCoordA+2; i++){
  if (i == 0)
  {
  initTurtlePosition(coordinatesX[i], coordinatesY[i],teleport_client, pen_client, srv, pen_srv);
  loop_rate.sleep();
  }
  
  else if(i == sizeCoordA+1){
    srv.request.x = coordinatesX[0];
    srv.request.y = coordinatesY[0];
    teleport_client.call(srv);
    loop_rate.sleep();
  }    
  else {
    srv.request.x = coordinatesX[i];
    srv.request.y = coordinatesY[i];
    teleport_client.call(srv);
    loop_rate.sleep();
  }
  }
  return 0;
}