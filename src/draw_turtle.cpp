#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <iostream>
#include "stdlib.h"
#include "time.h"

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
        double angular_difference = header * 180 / M_PI;
  ROS_INFO("\nAngle: %f", angular_difference);
  if (angular_difference < max_angle && angular_difference > -max_angle)
  {
    return false;
  }
  else
  {
    return true;
  }
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

for(int i=0; i<sizeCoordA+1; i++){
  coordinatesX[i] = randomNumber(10, 3);
  ros::Duration(1.0).sleep();
  coordinatesY[i] = randomNumber(10, 3);
  ros::Duration(1.0).sleep();
    }
    bool fullIntersect = true;
while (fullIntersect == true)
{

for(int i=0; i<sizeCoordA+1; i++){
  
  int intersection = itIntersects(130, coordinatesX[i], coordinatesY[i], coordinatesX[i-1], coordinatesY[i-1]);
  
  if (intersection = true){
    swapValue(coordinatesX[i], coordinatesX[i-1]);
    swapValue(coordinatesY[i], coordinatesY[i-1]);
    ROS_INFO("\nsortting");
  }
    }

fullIntersect = false;
for(int i=0; i<sizeCoordA; i++){
  //std::cout << "(" << coordinatesX[i] << ", " << coordinatesY[i] << ") ";
  int intersection = itIntersects(130, coordinatesX[i], coordinatesY[i], coordinatesX[i+1], coordinatesY[i+1]);
  
  if (intersection = true){
    fullIntersect = true;
    ROS_INFO("\nfailed sort");
  }
}
}
/*std::sort(coordinatesX, coordinatesX + sizeCoordA);
std::sort(coordinatesY, coordinatesY + sizeCoordA);*/
  for(int i=0; i<sizeCoordA+1; i++){
std::cout << "(" << coordinatesX[i] << ", " << coordinatesY[i] << ") ";
  }

//for calculating the angle
for(int i=0; i<sizeCoordA+1; i++){
double x_distance = coordinatesX[i] - coordinatesX[i-1];
double y_distance = coordinatesY[i] - coordinatesY[i-1];
double header = atan2(y_distance, x_distance);
double angular_difference = header * 180 / M_PI;

ROS_INFO("\nAngle: %f", angular_difference);
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

   /*
       for(int i = 0; i < sizeCoordA; i++){
      
if(i == sizeCoordA-1){
  ros::Rate loop_rate(2);
  float randomX = startX;
  float randomY = startY;
  moveTurtle(randomX, randomY, teleport_client, srv);
  loop_rate.sleep();
}
else {
    int randomX = {randomNumber(10, 3)};
    ros::Duration(1.0).sleep();
    int randomY = {randomNumber(10, 3)};
    moveTurtle(randomX, randomY, teleport_client, srv);
    loop_rate.sleep();
    }
    */

/* Exercise 2
  pen_srv.request.off = true;
  pen_client.call(pen_srv);
  srv.request.x = startX;
  srv.request.y = startY;
  teleport_client.call(srv);
  pen_srv.request.off = false;
  pen_srv.request.width = 2;
  pen_client.call(pen_srv);
  loop_rate.sleep();

  int sizeCoordA = 5;
  int sizeCoordB = 2;
  float coordinates[sizeCoordA][sizeCoordB] = {{startX+5, startY},{startX+5, startY+4},{startX+2, startY+4},{startX,startY+6},{startX, startY}};

  for(int i=0; i<sizeCoordA; i++){
    srv.request.x = coordinates[i][0];
    srv.request.y = coordinates[i][1];
    teleport_client.call(srv);
    loop_rate.sleep();
  }

  */

/* Exercise 1
  int sizeCoordA = 5;
  int sizeCoordB = 2;
  float startX = 5.544445, startY = 5.544445;
  float coordinates[sizeCoordA][sizeCoordB] = {{startX+3, startY},{startX+3, startY+4},{startX-3, startY+4},{startX-3,startY},{startX, startY}};

  for(int i=0; i<sizeCoordA; i++){
    srv.request.x = coordinates[i][0];
    srv.request.y = coordinates[i][1];
    teleport_client.call(srv);
    loop_rate.sleep();
  }
*/
  return 0;
}