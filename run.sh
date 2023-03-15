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



