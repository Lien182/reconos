/*
 * Copyright 2020 Christian Lienen <christian.lienen@upb.de>
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include "ros.h"

#include <rcl/rcl.h>


#include "../utils.h"


int ros_node_init(struct ros_node_t *ros_node)
{
  ros_node->context = rcl_get_zero_initialized_context();
  ros_node->init_options = rcl_get_zero_initialized_init_options();
  rcl_allocator_t allocator = rcl_get_default_allocator();
  rcl_ret_t rc;

  // create init_options
  rc = rcl_init_options_init(&ros_node->init_options, allocator);
  if (rc != RCL_RET_OK) {
    printf("Error rcl_init_options_init.\n");
    return -1;
  }


  // create context
  rc = rcl_init(0, 0, &ros_node->init_options, &ros_node->context);
  if (rc != RCL_RET_OK) {
    printf("Error in rcl_init.\n");
    return -1;
  }
  
  // create rcl_node
  ros_node->node = rcl_get_zero_initialized_node();
  rcl_node_options_t node_ops = rcl_node_get_default_options();

  rc = rcl_node_init(&ros_node->node, "node_1", "", &ros_node->context, &node_ops);
  if (rc != RCL_RET_OK) {
    printf("Error in rcl_node_init\n");
    return -1;
  }

  return 0;
}

int ros_node_destroy(struct ros_node_t *ros_node)
{
  int ret = 0;
  ret += rcl_node_fini(&ros_node->node);
  ret += rcl_init_options_fini(&ros_node->init_options);
  return ret;
}