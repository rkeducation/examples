FROM ubuntu:22.04 AS base

# Install necessary tools
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    gdb-multiarch \
    make \
    curl \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /workspace

# Default command
CMD ["bash"]