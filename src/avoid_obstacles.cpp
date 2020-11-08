#include <iostream>
#include <algorithm>
#include <ros/ros.h>
#include <actionlib/client/simple_client_goal_state.h>
#include <geometry_msgs/PointStamped.h>
#include <move_base_msgs/MoveBaseAction.h> //needed for moving the robot, with a goal sent from client
#include <actionlib/client/simple_action_client.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void sendGoal(int x, int w){
MoveBaseClient ac("move_base", true);
move_base_msgs::MoveBaseGoal goal;
goal.target_pose.header.frame_id = "base_link";
goal.target_pose.header.stamp = ros::Time::now();
goal.target_pose.pose.position.x = x;
goal.target_pose.pose.orientation.w = w;

ac.sendGoal(goal);
ROS_INFO("LET'S FUCKING GOOOOOOOOOO");
ac.waitForResult();
}


int main(int argc, char** argv){
ros::init(argc, argv, "simple_navigation_goals");

//tell the action client that we want to spin a thread by default
MoveBaseClient ac("move_base", true);

//wait for the action server to come up
while(!ac.waitForServer(ros::Duration(5.0))){
ROS_INFO("Zzz... Sleeping untill the move_base server works");
}

move_base_msgs::MoveBaseGoal goal;
float pos_x =1.0;
float pos_y =1.0;

//we'll send a goal to the robot to move 1 meter forward
sendGoal(pos_x, pos_y);

while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("well fuck didn't work");
    pos_y++;
    sendGoal(pos_x, pos_y);
}


ROS_INFO("1 meter is better than no meter");
return 0;
}