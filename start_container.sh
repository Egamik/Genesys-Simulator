#!/bin/bash

# Working directory of socket file
export XSOCK=/tmp/.X11-unix
# Temporary access token 
export XAUTH=/tmp/.docker.xauth

# Check if temoporary token file exists, if not create one
[ -e "$auth_file" ] || touch "$auth_file"

# Generate new access token, set the Authentication Family to 'FamilyWild'
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

# Start container
docker run -it --name genesys-sim --net host \
        -e DISPLAY=$DISPLAY \
        -e XAUTHORITY=$XAUTH \
        -v $XSOCK:$XSOCK \
        -v $XAUTH:$XAUTH \
        xeyes