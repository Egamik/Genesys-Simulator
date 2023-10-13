FROM ubuntu:latest

# Set the DEBIAN_FRONTEND variable to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# Create a user 
RUN useradd -ms /bin/bash genesys

# Set the user's password 
RUN echo 'genesys:genesys' | chpasswd

# Grant the user sudo privileges
RUN usermod -aG sudo genesys

# Expose the X11 socket for GUI applications 
ENV DISPLAY=$DISPLAY

# Install dependencies
RUN apt-get update && \
    apt-get -y install openssh-server vim build-essential && \
    apt-get -y install openssl libssl-dev libssl1.0 libgl1-mesa-dev libqt5x11extras5 '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev && \
    apt-get -y install xauth xorg x11-apps && \
    apt-get -y install qtcreator git

WORKDIR /home/genesys

COPY . .

# Start bash when the container starts
CMD ["/bin/bash"]
