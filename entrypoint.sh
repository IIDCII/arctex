#!/bin/bash
# entrypoint.sh

# Fix ownership of mounted volumes
sudo chown -R $(id -u):$(id -g) ~/.cache/nvim
sudo chown -R $(id -u):$(id -g) ~/.local/share/nvim
sudo chown -R $(id -u):$(id -g) ~/.local/state/nvim

# Execute the command
exec "$@"
