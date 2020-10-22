#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <iostream>
#include <math.h>
#include "stdlib.h"
#include "time.h"

int randomNumber(int maxN, int minN){
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
void quicksort(float measureList[],float sortList[][2], int first, int last){
int pivot, i, j, tmpX, tmpY;
if (first<last){
        pivot = first;
        i= first;
        j = last;

        while(i<j) {
            while (measureList[i]<=measureList[pivot] && i<last){
                i++;
            }
            while (measureList[j]>measureList[pivot]){
                j--;
            }
            if(i<j){
                tmpX = sortList[i][0];
                tmpY = sortList[i][1];
                sortList[i][0] = sortList[j][0];
                sortList[i][1] = sortList[j][1];
                sortList[j][0] = tmpY;
                sortList[j][1] = tmpY;

                tmpX = measureList[i];
                measureList[i] = measureList[j];
                measureList[j] = tmpX;
            }
        }
        tmpX = sortList[pivot][0];
        tmpY = sortList[pivot][1];
        sortList[pivot][0] = sortList[j][0];
        sortList[pivot][1] = sortList[j][1];
        sortList[j][0] = tmpX;
        sortList[j][1] = tmpY;
        
        tmpX = measureList[pivot];
        measureList[pivot] = measureList[j];
        measureList[j] = tmpX;

        quicksort(measureList, sortList, first, j-1);
        quicksort(measureList, sortList, j+1, last);
    }

}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "draw_turtle");
  ros::NodeHandle nh;
  ros::service::waitForService("/turtle1/teleport_absolute", -1);
  ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
  turtlesim::TeleportAbsolute srv;
  ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
  turtlesim::SetPen pen_srv;
  srand (time(NULL));
  ros::Rate loop_rate(2);

  float startX = 5.544445, startY = 5.544445;
  if(argc>1){
    startX = atof(argv[1]);
    startY = atof(argv[2]);
  }

  initTurtlePosition(startX, startY,teleport_client, pen_client, srv, pen_srv);
  loop_rate.sleep();

  int sizeCoordA = 5;
  std::cout << "Please type the desired amount of points in the Polygon: ";
  std::cin >> sizeCoordA;
  const int sizeCoordB = 2;
float coordinates[sizeCoordA][sizeCoordB];
float distances[sizeCoordA];

for(int i=0; i<sizeCoordA+1; i++){
        coordinates[i][0] = randomNumber(10, 3);
        coordinates[i][1] = randomNumber(10, 3);
    }
//calculating the distance between each point in the array
for(int i=0; i<sizeCoordA; i++){
distances[i] = sqrt(pow(coordinates[i][0]-coordinates[i+1][0],2)+pow(coordinates[i][1]-coordinates[i+1][1],2)* 1.0);
}
  //////////////////////////////////
std::cout << "distances before sort\n";
  for(int i=0; i<sizeCoordA+1; i++){
std::cout << "(" << distances[i] << ") ";
  }
  //////////////////////////////////

quicksort(distances, coordinates, 0, sizeCoordA);

  ///////////////////////////////////// 
  std::cout << "\n distances after sort\n";
  for(int i=0; i<sizeCoordA+1; i++){
std::cout << "(" << distances[i] << ") ";
  }
  /////////////////////////////////////
coordinates[sizeCoordA][0]=coordinates[0][0];
coordinates[sizeCoordA][1]=coordinates[0][1];

  std::cout << "\n Printed coordinates\n";
  for(int i=0; i<sizeCoordA+1; i++){
std::cout << "(" << coordinates[i][0] << ", " << coordinates[i][1] << ") ";
  }

    for(int i=0; i<sizeCoordA+1; i++){
  if (i == 0)
  {
  initTurtlePosition(coordinates[i][0], coordinates[i][1],teleport_client, pen_client, srv, pen_srv);
  loop_rate.sleep();
  }
  else {
    srv.request.x = coordinates[i][0];
    srv.request.y = coordinates[i][1];
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