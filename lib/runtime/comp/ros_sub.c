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
#include "../utils.h"


int ros_subscriber_init(struct ros_subscriber *ros_sub, cl_node_t* node, char* topic, uint32_t max_msg_size)
{
    rcl_ret_t rc;
    // create subscription
    rcl_subscription_t my_sub = rcl_get_zero_initialized_subscription();
    rcl_subscription_options_t my_subscription_options = rcl_subscription_get_default_options();

    std_msgs__msg__String__init(&ros_sub->sub_msg);

    rc = rcl_subscription_init(
        &ros_sub->sub,
        ros_sub->node,
        my_type_support,
        topic,
        &my_subscription_options);  

    if (rc != RCL_RET_OK) {
        printf("Failed to create subscriber %s.\n", topic_name);
        return -1;
    } 
    else 
    {
        debug("Created subscriber %s:\n", topic_name);
    } 
}

/*
 * Frees all used memory of the mbox.
 *
 *   mb - pointer to the mbox
 */
void ros_subscriber_destroy(struct ros_subscriber *ros_sub)
{
    rcl_subscription_fini(ros_sub->sub, ros_sub->node);
}

/*
 * Puts a single word into the mbox and blocks if it is full.
 *
 *   mb  - pointer to the mbox
 *   msg - message to put into the mbox
 */
int ros_subscriber_try_take(struct ros_subscriber *ros_sub, uint8_t * msg);
{
    rcl_ret_t rc;

    rc = rcl_take(&ros_sub->sub, &sub_msg, &messageinfo, &allocator);
    if(rc != RCL_RET_OK)
    {
        if(rc != RCL_RET_SUBSCRIPTION_TAKE_FAILED)
            debug("Error number: %d\n", rc);
        else
        {
            debug("Return code : %d\n", rc)
        }
        
    }
}