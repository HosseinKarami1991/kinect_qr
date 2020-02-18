#include <ros/ros.h>
#include <tf/transform_listener.h>
#include<std_msgs/Float32.h>
#include<std_msgs/String.h>
std::string marker;
ros::Publisher pubstatus;
std_msgs::String objstatus;
bool firsttime =true;
std::string lasmsg="";
void qrcallback(const std_msgs::String::ConstPtr& msg){
 
 marker =msg->data;
 //ROS_INFO("sending back response: [%s]", msg->data.c_str()); 
//std::cout<<"marker is "<<marker<<std::endl;
 if (marker =="ar_marker_0"){
  objstatus.data = "faulty";
  

    pubstatus.publish(objstatus);


 } 
 else if (marker =="ar_marker_1"){
objstatus.data = "not_faulty";

    pubstatus.publish(objstatus);


 }
 else {
  objstatus.data = "NA";
    pubstatus.publish(objstatus);
  
 lasmsg=objstatus.data;
 }
}





int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;


  ros::Subscriber qr_id;

  pubstatus= node.advertise<std_msgs::String>("obj_status", 20);
  ros::Rate rate(10.0);
  while (node.ok()){
    qr_id = node.subscribe("qr_id", 20, qrcallback);
    ros::spin();
    rate.sleep();
  }
  return 0;
}

