/*
 * Copyright 2020 Christian Lienen <christian.lienen@upb.de>
 */

#ifndef ROS_H
#define ROS_H

/*
 * Structure representing a ros node
 */
struct ros_node {
    rcl_context_t       context;
    rcl_init_options_t  init_options;
    rcl_node_t          node;

};

/*
 * Initiali;zes the ros node. You must call this method before you
 * can use the ros node .
 *
 *  ros_node   - pointer to the ros_node
 * 
 */
extern int ros_node_init(struct ros_node *ros_node);

/*
 * Frees all used memory of the ros_node.
 *
 *   ros_node - pointer to the rosnode 
 */
extern void ros_node_destroy(struct ros_node *ros_node);



#endif /* ROS_H */
