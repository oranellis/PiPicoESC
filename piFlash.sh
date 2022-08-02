#!/bin/bash

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
