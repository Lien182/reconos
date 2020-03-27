/*
 * Copyright 2020 Christian Lienen <christian.lienen@upb.de>
 */

#include <stdio.h>
#include <std_msgs/msg/string.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>


#include "ros_sub.h"
#include "rmw/types.h"

#include "../utils.h"

int ros_subscriber_init(struct ros_subscriber_t *ros_sub, struct ros_node_t * ros_node, char* topic, uint32_t max_msg_size)
{
    rcl_ret_t rc;
    // create subscription
    ros_sub->sub = rcl_get_zero_initialized_subscription();
    rcl_subscription_options_t my_subscription_options = rcl_subscription_get_default_options();

    const rosidl_message_type_support_t * my_type_support =
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String);

    rc = rcutils_uint8_array_init(&ros_sub->sub_msg,max_msg_size, &ros_node->allocator );
    if (RCUTILS_RET_OK != rc)
    {
        printf("[ROS Subscriber] Error msg array init %d\n", rc);
        return -1;
    }

    rc = rcl_subscription_init(
        &ros_sub->sub,
        &ros_node->node,
        my_type_support,
        topic,
        &my_subscription_options);  

    if (rc != RCL_RET_OK) {
        panic("[ROS Subscriber] Failed to create subscriber: %s\n", topic);
        return -2;
    } 
    else 
    {
        debug("[ROS Subscriber] Created subscriber: %s\n", topic);
    } 

    ros_sub->max_msg_size = max_msg_size;

    //ros_sub->sub_msg = rcutils_get_zero_initialized_uint8_array();

    
    return 0;
}

/*
 * Frees all used memory of the mbox.
 *
 *   mb - pointer to the mbox
 */
int ros_subscriber_destroy(struct ros_subscriber_t *ros_sub)
{
    return rcl_subscription_fini(&ros_sub->sub, ros_sub->node);
}

/*
 * Puts a single word into the mbox and blocks if it is full.
 *
 *   mb  - pointer to the mbox
 *   msg - message to put into the mbox
 */
int ros_subscriber_try_take(struct ros_subscriber_t *ros_sub, uint8_t * msg)
{
    rcl_ret_t rc;
    rmw_message_info_t messageInfo;
    
    rc = rcl_take_serialized_message(&ros_sub->sub, &ros_sub->sub_msg,  &messageInfo, NULL);
    
    if(rc != RCL_RET_OK)
    {
        if(rc != RCL_RET_SUBSCRIPTION_TAKE_FAILED)
        {
            debug("[ROS Subscriber] Error number: %d\n", rc);
            return -1;
        }
        else
        {
            debug("[ROS Subscriber] Return code : %d\n", rc);
            return 1;
        }        
    }

    memcpy(msg, ros_sub->sub_msg.buffer, ros_sub->max_msg_size);

    return 0;
}