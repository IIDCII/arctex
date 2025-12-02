FROM nvidia/cuda:12.6.2-devel-ubuntu22.04

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && \
  apt-get install -y --fix-missing \
  build-essential \
  cmake \
  git \
  curl \
  wget \
  python3 \
  python3-pip \
  ripgrep \
  fd-find \
  unzip \
  ninja-build \
  gettext \
  xclip \
  x11-xserver-utils \
  && rm -rf /var/lib/apt/lists/*

# Install latest Neovim
RUN curl -LO https://github.com/neovim/neovim/releases/latest/download/nvim-linux-x86_64.tar.gz && \
  tar -C /opt -xzf nvim-linux-x86_64.tar.gz && \
  ln -sf /opt/nvim-linux-x86_64/bin/nvim /usr/local/bin/nvim && \
  rm nvim-linux-x86_64.tar.gz

# Set up CUDA environment variables
ENV CUDA_HOME=/usr/local/cuda
ENV PATH=${CUDA_HOME}/bin:${PATH}
ENV LD_LIBRARY_PATH=${CUDA_HOME}/lib64:${LD_LIBRARY_PATH}

# Create user with matching UID/GID
ARG USER_ID=1000
ARG GROUP_ID=1000
ARG USERNAME=developer

# Remove existing ubuntu user if it uses our target UID
RUN if getent passwd ${USER_ID} | grep -v ${USERNAME}; then \
  OLD_USER=$(getent passwd ${USER_ID} | cut -d: -f1); \
  userdel ${OLD_USER}; \
  fi

# Create our user
RUN groupadd -g ${GROUP_ID} ${USERNAME} 2>/dev/null || true && \
  useradd -u ${USER_ID} -g ${GROUP_ID} -m -s /bin/bash ${USERNAME} && \
  echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Create necessary directories
RUN mkdir -p /home/${USERNAME}/.local/share/nvim \
  /home/${USERNAME}/.cache/nvim \
  /home/${USERNAME}/.local/state/nvim && \
  chown -R ${USER_ID}:${GROUP_ID} /home/${USERNAME}/.local \
  /home/${USERNAME}/.cache

# Copy and set up entrypoint script while still root
COPY entrypoint.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/entrypoint.sh

# Switch to the user
USER ${USER_ID}

# Install LazyVim starter config
RUN git clone https://github.com/LazyVim/starter /home/${USERNAME}/.config/nvim

# Remove the .git directory so it doesn't conflict with your git repo
RUN rm -rf /home/${USERNAME}/.config/nvim/.git

# Configure git for this user
RUN git config --global --add safe.directory '*'

# Copy your custom lua files over the defaults
COPY --chown=${USER_ID}:${GROUP_ID} ./docker-configs/${USERNAME}/lua /home/${USERNAME}/.config/nvim/lua


# Set up workspace
WORKDIR /workspace

# Set the entrypoint
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["/bin/bash"]
