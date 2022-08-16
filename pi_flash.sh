#!/bin/bash
#  ____  _   ____  _             _____ _           _
# |  _ \(_) |  _ \(_) ___ ___   |  ___| | __ _ ___| |__   ___ _ __
# | |_) | | | |_) | |/ __/ _ \  | |_  | |/ _` / __| '_ \ / _ \ '__|
# |  __/| | |  __/| | (_| (_) | |  _| | | (_| \__ \ | | |  __/ |
# |_|   |_| |_|   |_|\___\___/  |_|   |_|\__,_|___/_| |_|\___|_|
# 
# A script to flash a connected pi with a .uf2 file in the invoked directory
#
# Authors: Oran Ellis
# Licence: GPLv3

echo "Attempting to flash to pico"
mkdir $(pwd)/pimount
sudo mount -L RPI-RP2 $(pwd)/pimount
if [[ -e $(pwd)/pimount/INDEX.HTM ]]
then
    sudo cp -f $(pwd)/*.uf2 $(pwd)/pimount
    sleep 0.5
    sudo umount $(pwd)/pimount/
    echo "File copied"
else
    echo "Failed to copy file, no pico present"
fi
rm -rf ./pimount
