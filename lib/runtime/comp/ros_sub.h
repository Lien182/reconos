/*
 * Copyright 2020 Christian Lienen <christian.lienen@upb.de>
 */

#ifndef ROSSUB_H
#define ROSSUB_H

#include <rcl/subscriber.h>
#include <stdint.h>

/*
 * Structure representing a mbox
 */
struct ros_subscriber {
    cl_node_t*              node;
    rcl_subscription_t      sub;
    uint32_t                max_msg_size;
    std_msgs__msg__String   sub_msg;
};

/*
 * Initializes the mbox. You must call this method before you
 * can use the mbox.
 *
 *  mb   - pointer to the mbox
 *  size - size of the mbox in 32bit-words
 */
extern int ros_subscriber_init(struct ros_subscriber *ros_sub, char* topic, uint32_t max_msg_size);

/*
 * Frees all used memory of the mbox.
 *
 *   mb - pointer to the mbox
 */
extern void ros_subscriber_destroy(struct ros_subscriber *ros_sub);

/*
 * Puts a single word into the mbox and blocks if it is full.
 *
 *   mb  - pointer to the mbox
 *   msg - message to put into the mbox
 */
extern int ros_subscriber_try_take(struct ros_subscriber *ros_sub, uint8_t * msg);


#endif /* ROSSUB_H */
