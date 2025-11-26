#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")"/.. && pwd)"
cd "$ROOT_DIR"

sudo docker build -t cuda-with-cmake .
sudo docker compose up -d
sudo docker compose exec cuda-service bash

