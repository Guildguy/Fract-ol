#!/bin/bash

xhost +local:docker > /dev/null 2>&1

docker run --rm -it \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
    fractol:latest "$@"

xhost -local:docker > /dev/null 2>&1
