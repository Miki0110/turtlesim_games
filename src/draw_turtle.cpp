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
void quicksort(float sortList[][2], float tmpLngth, int first, int last){
int pivot, i, j, tmpX, tmpY;
if (first<last){
        pivot = first;
        i= first;
        j = last;
        float distances[last];
        float fullDistance = 0;
        float calcDistance = 0;
for(int i=0; i<last; i++){
distances[i] = sqrt(pow(sortList[i][0]-sortList[i+1][0],2)+pow(sortList[i][1]-sortList[i+1][1],2)* 1.0);
}
        while(i<j) {
            while (distances[i]<=distances[pivot] && i<last){
                i++;
            }
            while (distances[j]>distances[pivot]){
                j--;
            }
            if(i<j){
                tmpX = sortList[i][0];
                tmpY = sortList[i][1];
                sortList[i][0] = sortList[j][0];
                sortList[i][1] = sortList[j][1];
                sortList[j][0] = tmpY;
                sortList[j][1] = tmpY;

                tmpX = distances[i];
                distances[i] = distances[j];
                distances[j] = tmpX;
            }
        }
        tmpX = sortList[pivot][0];
        tmpY = sortList[pivot][1];
        sortList[pivot][0] = sortList[j][0];
        sortList[pivot][1] = sortList[j][1];
        sortList[j][0] = tmpX;
        sortList[j][1] = tmpY;
        
        tmpX = distances[pivot];
        distances[pivot] = distances[j];
        distances[j] = tmpX;

  std::cout << "\n distances after sort\n";
  
  for(int i=0; i<last+1; i++){
    calcDistance =  fullDistance;
    fullDistance = calcDistance + distances[i];
  }
  std::cout << "(" << fullDistance << ") ";

  if(fullDistance >= tmpLngth)

        quicksort(sortList, tmpLngth, first, j-1);
        quicksort(sortList, tmpLngth, j+1, last);
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

for(int i=0; i<sizeCoordA+1; i++){
        coordinates[i][0] = randomNumber(10, 3);
        coordinates[i][1] = randomNumber(10, 3);
    }
//calculating the distance between each point in the array
/*
for(int i=0; i<sizeCoordA; i++){
distances[i] = sqrt(pow(coordinates[i][0]-coordinates[i+1][0],2)+pow(coordinates[i][1]-coordinates[i+1][1],2)* 1.0);
}
*/
  //////////////////////////////////

  
  //////////////////////////////////

 //quicksort(coordinates, 0, sizeCoordA);

  ///////////////////////////////////// 
  
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
  return 0;
}