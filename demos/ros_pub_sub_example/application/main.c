#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "ros.h"
#include "ros_sub.h"
#include "ros_pub.h"


struct ros_node_t resources_rosnode_s;
struct ros_node_t * resources_rosnode = &resources_rosnode_s;

struct ros_subscriber_t resources_subdata_s;
struct ros_subscriber_t *resources_subdata = &resources_subdata_s;

struct ros_publisher_t resources_pubdata_s;
struct ros_publisher_t *resources_pubdata = &resources_pubdata_s;

void my_handler (int sig)
{
	printf("Interrupt\n");
	ros_subscriber_destroy(resources_subdata);
  	ros_node_destroy(resources_rosnode);
	exit(0);
}


int main(int argc, char **argv) {
	int ret = 0;
	int i = 0;
	char msg[100];
	char pub_msg[]="ROS2 ReconOS\n";



	signal (SIGQUIT, my_handler);
	signal (SIGINT, my_handler);


	ros_node_init(resources_rosnode);

	ros_publisher_init(resources_pubdata, resources_rosnode, "chatter", 100);
	//ros_subscriber_init(resources_subdata, resources_rosnode, "chatter", 10);
	

	for(i = 0; i <20; i++ )
	{
		ros_publisher_publish(resources_pubdata, (uint8_t*)pub_msg, strlen(pub_msg));
		
	/*	ret = ros_subscriber_try_take(resources_subdata, msg);
		if(ret == 0)
			printf("Message %d: %s\n",i, msg);
		else
		{
			printf("return code %d: %d\n",i, ret);
		}*/
			
		usleep(1000000);
	}

	ros_node_destroy(resources_rosnode);

	return 0;
}