# CUDA Dev Environment with LazyVim

This project sets up a GPU-enabled, Dockerized development environment with:

- **Ubuntu 24.04 + CUDA 12.8 + cuDNN**
- **Python 3**
- **Neovim (LazyVim preconfigured)**
- GPU access via **NVIDIA Docker**
- Shared clipboard via **X11**
- Modular support for your own project code

---

## 🚀 Quick Start

### 1. Install Prerequisites

Make sure you have the following installed on your system:

- [Docker](https://docs.docker.com/get-docker/)
- [Docker Compose](https://docs.docker.com/compose/)
- [NVIDIA Container Toolkit](https://doc.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html)  
  (This enables Docker to access your GPU)

---

### 2. Clone the Project

```bash
git clone https://github.com/CldStlkr/cuda-dev-env.git
cd cuda-dev-env
```

---

### 3. Create Your `.env` File

Create a `.env` file in the project root with the following content (adjust as needed):

```env
# .env

USER_ID=1000                     # your user ID (run `id -u`)
GROUP_ID=1000                    # your group ID (run `id -g`)
USERNAME=yourname                # name for user inside the container
NVIM_CONFIG_PATH=/home/you/.config/nvim  # optional, your Neovim config
PROJECT_DIR=/path/to/your/codebase       # optional, fallback is ../
```

If `PROJECT_DIR` is not set, it defaults to the parent folder of this project.

---

### 4. Build the Container

Run the setup script:

```bash
./prepare-and-build.sh
```

This will:

* Optionally reset Neovim volumes
* Copy your local Neovim Lua config (if present)
* Build the container image

---

### 5. Start and Use the Container

Start it:

```bash
docker compose up -d
```

Then enter the container:

```bash
docker compose exec cuda-dev bash
```

You’ll be in `/workspace`, which is your mounted project directory.

---

### 6. Start Neovim

Inside the container, run:

```bash
nvim
```

This uses LazyVim, which will automatically install plugins on first run. Your clipboard should work if X11 is set up.

---

## 🧹 Optional: Reset Neovim Volumes

If you want to clean up and start fresh:

```bash
./prepare-and-build.sh
```

Say `yes` when asked to reset Neovim volumes.

---

## 🛠️ Troubleshooting

* **Clipboard not working?**

  * Make sure `.Xauthority` exists in your home directory

  * Ensure X11 is working on your host

  * Try: `xhost +local:docker`

* **Can't access GPU?**

  * Inside the container, run: `nvidia-smi`
  * Ensure the NVIDIA container toolkit is installed properly

---

## 📂 Project Structure

```
cuda-dev-env/
├── Dockerfile              # Docker image definition
├── docker-compose.yml      # Container orchestration
├── entrypoint.sh           # Runs inside the container, fixes file permissions
├── prepare-and-build.sh    # Easy setup/build/reset script
├── .env                    # Your environment config (not committed)
├── .env.template           # template to copy (cp .env.template .env)
└── docker-configs/         # Temporary folder for custom Lua files (auto-managed)
```

---

## 👥 Collaborating

To share this with others:

1. Share this repo
2. They create their own `.env`
3. Run `./prepare-and-build.sh`
4. Done — no Docker knowledge required
