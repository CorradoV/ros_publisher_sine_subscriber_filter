
//include ros header file
#include "ros/ros.h" 
//header file of the message to publish
#include "std_msgs/Int32.h"  
#include "ros_topic_classwork/classwork_msg.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {

	
	ros::init(argc, argv,"sinu_pub");
	
	//Declare the node handle: our interface with the ROS system
	ros::NodeHandle n;

	//Create a publisher object:

	ros::Publisher p = n.advertise<ros_topic_classwork::classwork_msg>("/classwork_msg", 10);

	ros_topic_classwork::classwork_msg s;

	cout<<"Insert Sine amptitude : ";
	cin>>s.Amptitude;
	cout<<"\nInsert Sine period: ";
	cin>>s.Period;

	ros::Rate rate(10); 
	float t = 0.0;

	while(ros::ok()){
		s.Sin_Value=s.Amptitude*sin((2*3.14*t)/s.Period);
		t+=1.0/10.0;

		p.publish(s);
		rate.sleep();
	}

	return 0;
}
