#!/bin/bash

cp Demo/$1 Docker/workspace/tmp -r

sudo docker run -it --rm  --name ros_arm_inst -v /usr/bin/qemu-arm-static:/usr/bin/qemu-arm-static -v $(pwd)/Docker/workspace:/mnt/workspace:rw ros_arm:1.0 bash /mnt/workspace/compile.sh $1

mkdir -p _build
cp Docker/workspace/tmp _build/$1 -r
rm Docker/workspace/tmp -r -f