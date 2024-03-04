#!/bin/bash

# Execute the vulnerable program
./problem5 &

# Store the PID of the program
PID=$!

# Sleep briefly to ensure that the program starts and enters the usleep call
sleep 0.06

# Create a flag file to indicate that the program is running
touch /tmp/$PID

# Clean up
rm /tmp/$PID