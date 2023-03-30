#include "boost/thread.hpp"
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"
#include "ros_topic_classwork/classwork_msg.h"

using namespace std;

//Use a class to store the topic data 
//	Just a choice: the best way to share data between a main loop and the ROS callbacks
class ROS_SUB {
	public:
		ROS_SUB();
		void topic_cb( ros_topic_classwork::classwork_msg data);
		void filter();
		
	private:
		ros::NodeHandle _nh;
		//Subscriber object
		ros::Subscriber _topic_sub;
		std_msgs::Float32 filt_value; //filter value published by the node
		float x; //In this variable we store the info of the value of the sine publishsed by the other node
		
};

ROS_SUB::ROS_SUB() {
	//Initialize a subscriber:

	_topic_sub = _nh.subscribe("/classwork_msg", 1, &ROS_SUB::topic_cb, this);
	boost::thread loop_th(&ROS_SUB::filter, this);
	
	
}

//Callback function: the input of the function is the data to read
void ROS_SUB::topic_cb( ros_topic_classwork::classwork_msg  data) {

	x=data.Sin_Value;

}

void ROS_SUB::filter(){
	ros::Publisher _filt_pub;
	_filt_pub=_nh.advertise<std_msgs::Float32>("/filt_msg",10);
	filt_value.data=0.0;
	while(1){
	filt_value.data=0.1*filt_value.data+0.1*x;
	
	_filt_pub.publish(filt_value);
	}
}

int main( int argc, char** argv ) {

	//Init the ros node with ros_subscriber name
	ros::init(argc, argv, "filter_subscriber");

	//Create the ROS_SUB class object
	ROS_SUB rs;
	

	ros::spin(); 



	return 0;
}


