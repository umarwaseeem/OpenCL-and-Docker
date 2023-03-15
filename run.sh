#!/bin/bash

# Step 1 - Download Docker Desktop
# Skip this step if Docker Desktop is already installed

# Step 2 - Clone/Open the repo
git clone https://github.com/Umar-Waseem/OpenCL-and-Docker

# Step 3 - Navigate to the repo
cd OpenCL-and-Docker

# Step 4 - Build Docker image
docker build -t opencl-image .

# Step 5 - Run Docker container
docker run -it opencl-image

# Step 6 - Verify that the `host.c` file exists
if [ ! -f "/app/host.c" ]; then
    echo "host.c file not found"
    exit 1
fi

# Step 7 - Compile the code
gcc /app/host.c -o host -lOpenCL

# Step 8 - Run the code
./host

