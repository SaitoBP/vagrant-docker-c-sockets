#!/bin/bash

# Update System
apt update
apt upgrade -y

# Install Dependencies
apt-get install curl apt-transport-https ca-certificates software-properties-common -y

# Add GPG Key
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -

# Add Docker Repository
add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"

# Update Repository Info
apt update

# Install Docker Ubuntu 18.04
apt install docker-ce -y

# Download Docker Compose
curl -L "https://github.com/docker/compose/releases/download/1.29.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose

# Apply Executable Permission to the Binary
chmod +x /usr/local/bin/docker-compose

# Add User to Docker Group
usermod -aG docker $USER