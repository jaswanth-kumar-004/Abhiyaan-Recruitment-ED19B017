#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "math.h"

float turtle1PosX;
float turtle1PosY;
float turtle2PosX;
float turtle2PosY;


// This is an absolute value function with modificatio so that it works at the start.
// I did the only fr this specific case as there were errors while starting, like the turtle getting teleported as the values were nearly 0.
/*
float absVal(float a)
{
	if(a < 0)
		return -1 * a;
	else if (a < 0.1)
		return 0.1;
	else
		return a;
}
*/
void turtle1PosCallBack(const turtlesim::Pose::ConstPtr& turtle1Position)
{
	turtle1PosX = turtle1Position->x;
	turtle1PosY = turtle1Position->y;
}

void turtle2PosCallBack(const turtlesim::Pose::ConstPtr& turtle2Position)
{
	turtle2PosX = turtle2Position->x;
	turtle2PosY = turtle2Position->y;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dodger_script");

  ros::NodeHandle n;
  
  ros::Publisher turtle2VelPub = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 1000);
	ros::Subscriber turtle1PosSub = n.subscribe<turtlesim::Pose>("/turtle1/pose", 1000, turtle1PosCallBack);
	ros::Subscriber turtle2PosSub = n.subscribe<turtlesim::Pose>("/turtle2/pose", 1000, turtle2PosCallBack);
	
  ros::Rate loop_rate(10);
  
  geometry_msgs::Twist turtle2Vel;
  
  while (ros::ok())
  {
  	
  	if((turtle1PosX - turtle2PosX) * (turtle1PosX - turtle2PosX) + (turtle1PosY - turtle2PosY) * (turtle1PosY - turtle2PosY) > 4)
  	{
			turtle2Vel.linear.x = 1;
			turtle2Vel.linear.y = 0;
			turtle2Vel.linear.z = 0;
			turtle2Vel.angular.x = 0;
			turtle2Vel.angular.y = 0;
			turtle2Vel.angular.z = 0;
  	}
  	
  	if((turtle1PosX - turtle2PosX) * (turtle1PosX - turtle2PosX) + (turtle1PosY - turtle2PosY) * (turtle1PosY - turtle2PosY) < 4)
  	{
  		turtle2Vel.linear.x = 0.2;
			turtle2Vel.linear.y = 1;
			turtle2Vel.linear.z = 0;
			turtle2Vel.angular.x = 0;
			turtle2Vel.angular.y = 0;
			turtle2Vel.angular.z = 0;
  	}

    turtle2VelPub.publish(turtle2Vel);
    
    ros::spinOnce();

    loop_rate.sleep();
  }
  return 0;
}

