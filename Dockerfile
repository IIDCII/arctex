FROM nvidia/cuda:12.6.2-devel-ubuntu22.04

# Install cmake, build tools, and CUnit
RUN apt-get update
RUN apt-get install -y --no-install-recommends cmake
RUN apt-get install -y --no-install-recommends build-essential
RUN apt-get install -y --no-install-recommends ninja-build
RUN apt-get install -y --no-install-recommends libcunit1-dev
RUN rm -rf /var/lib/apt/lists/*

WORKDIR /workspace