/*
 * Copyright 2020 Christian Lienen <christian.lienen@upb.de>
 */

#include <stdio.h>
#include <std_msgs/msg/string.h>
#include "rclc/executor.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include "ros_pub.h"
#include "../utils.h"

int ros_publisher_init(struct ros_publisher *ros_pub, cl_node_t* node, char* topic_name, uint32_t max_msg_size)
{
    ros_pub->max_msg_size = max_msg_size;
    
    const rosidl_message_type_support_t * my_type_support =
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String);
  
    rcl_publisher_options_t pub_options = rcl_publisher_get_default_options();
    rc = rcl_publisher_init(
        &ros_pub->rcl_pub,
        node,
        my_type_support,
        topic_name,
        &pub_options);
   
    if (RCL_RET_OK != rc) {
        printf("Error in rcl_publisher_init %s.\n", topic_name);
    return -1;
  }
}

void ros_publisher_destroy(struct ros_publisher *ros_pub)
{
    rcl_publisher_fini(ros_pub, ros_pub->node);
}

int ros_publisher_publish(struct ros_publisher *ros_pub, uint8_t * msg, uint32_t msg_size)
{
    rcl_ret_t rc;
    std_msgs__msg__String pub_msg;
    rosidl_generator_c__String__assignn(&pub_msg, msg, ros_pub);

    rc = rcl_publish(&my_pub, &pub_msg, NULL);
    if (rc == RCL_RET_OK) {
      debug("Published message %s\n", pub_msg.data.data);
    } else {
      debug("Error publishing message %s\n", pub_msg.data.data);
    }
  
}
