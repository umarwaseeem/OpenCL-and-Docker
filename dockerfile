FROM ubuntu:18.04

RUN apt-get update && \
    apt-get install -y pocl-opencl-icd ocl-icd-opencl-dev gcc clinfo

WORKDIR /app

COPY host.c /app/
COPY Makefile /app/