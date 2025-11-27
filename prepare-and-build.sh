#!/bin/bash
# prepare-and-build.sh

# Change to docker directory
cd "$(dirname "$0")"

# Load environment variables
if [ ! -f .env ]; then
  echo "Error: .env file not found!"
  echo "Please create a .env file with your settings."
  exit 1
fi
source .env

# Set project directory with fallback to parent directory of cuda-docker
PROJECT_DIR="${PROJECT_DIR:-$(cd "$(dirname "$0")/.." && pwd)}"
export PROJECT_DIR
echo "Using project directory: $PROJECT_DIR"

# Stop containers first
echo "Stopping any running containers..."
docker compose down

# Ask if user wants to reset volumes
read -p "Do you want to reset nvim volumes? (y/N): " reset_volumes
if [[ $reset_volumes =~ ^[Yy]$ ]]; then
  echo "Removing ALL nvim-related volumes..."
  nvim_volumes=$(docker volume ls -q | grep -E "(nvim|lazy)" | tr '\n' ' ')
  if [ ! -z "$nvim_volumes" ]; then
    echo "Found volumes: $nvim_volumes"
    docker volume rm $nvim_volumes
    echo "Volumes removed."
  else
    echo "No nvim volumes found."
  fi
fi

# Prepare configs
echo "Preparing configurations for user: $USERNAME..."
mkdir -p ./docker-configs/${USERNAME}

# Copy only your custom lua directory if it exists
if [ -d "${NVIM_CONFIG_PATH}" ] && [ -d "${NVIM_CONFIG_PATH}/lua" ]; then
  echo "Copying custom lua configs from ${NVIM_CONFIG_PATH}/lua..."
  cp -r "${NVIM_CONFIG_PATH}/lua" ./docker-configs/${USERNAME}/
else
  echo "No custom lua configs found at ${NVIM_CONFIG_PATH}/lua (this is fine)"
  echo "LazyVim will use default configuration..."
  mkdir -p ./docker-configs/${USERNAME}/lua
fi

# Build
echo "Building Docker image..."
docker compose build --no-cache

# Cleanup
echo "Cleaning up temporary files..."
rm -rf ./docker-configs/

echo "Done! Your container is ready to use."
echo ""
echo "Next steps:"
echo "1. Run: docker compose up -d"
echo "2. Run: docker compose exec cuda-dev bash"
echo "3. Inside container, run: nvim (it will automatically install plugins)"
