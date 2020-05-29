#!/bin/sh
#the following commands will setup the game environment
sudo apt update -y && sudo apt upgrade -y
sudo apt install libx11-dev -y
sudo apt install libxext-dev -y
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
