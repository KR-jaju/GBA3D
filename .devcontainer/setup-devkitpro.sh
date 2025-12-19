#!/usr/bin/env bash
set -euo pipefail
export DEBIAN_FRONTEND=noninteractive

# ---- paths / flags ----
WORKDIR="/workspaces"
LOG="$WORKDIR/.devkitpro_setup.log"
FLAG="$WORKDIR/.devkitpro_setup_done"

log() { echo "[devkitPro] $*" | tee -a "$LOG"; }

# ---- wait for apt/dpkg lock ----
wait_for_apt() {
  local start
  start=$(date +%s)
  while sudo fuser /var/lib/dpkg/lock-frontend >/dev/null 2>&1 \
     || sudo fuser /var/lib/dpkg/lock >/dev/null 2>&1 \
     || sudo fuser /var/lib/apt/lists/lock >/dev/null 2>&1; do
    log "apt/dpkg lock held, waiting..."
    sleep 2
    if (( $(date +%s) - start > 600 )); then
      log "ERROR: timeout waiting for apt lock"
      exit 1
    fi
  done
}

log "===== setup start $(date -Is) ====="

# ---- already installed? ----
if command -v arm-none-eabi-gcc >/dev/null 2>&1 && [[ -d /opt/devkitpro ]]; then
  log "devkitPro already installed"
  touch "$FLAG"
  exit 0
fi

# ---- prerequisites ----
wait_for_apt
log "installing prerequisites..."
sudo apt-get update -y
sudo apt-get install -y --no-install-recommends \
  ca-certificates wget curl gnupg dirmngr \
  build-essential make git \
  xz-utils bzip2 unzip tar

# ---- devkitPro pacman bootstrap ----
log "installing devkitPro pacman..."
wget -q https://apt.devkitpro.org/install-devkitpro-pacman -O /tmp/install-devkitpro-pacman
chmod +x /tmp/install-devkitpro-pacman
sudo /tmp/install-devkitpro-pacman

# ---- environment (system-wide) ----
log "configuring environment variables..."
sudo tee /etc/profile.d/devkitpro.sh >/dev/null <<'PROFILE'
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=/opt/devkitpro/devkitARM
export PATH="$PATH:$DEVKITARM/bin:$DEVKITPRO/tools/bin"
PROFILE

# ---- apply env to current shell ----
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=/opt/devkitpro/devkitARM
export PATH="$PATH:$DEVKITARM/bin:$DEVKITPRO/tools/bin"

# ---- keyring (defensive) ----
if command -v dkp-pacman-key >/dev/null 2>&1; then
  log "initializing pacman keyring..."
  sudo dkp-pacman-key --init || true
  sudo dkp-pacman-key --populate devkitpro || true
fi

# ---- install gba-dev ----
wait_for_apt
log "installing gba-dev..."
sudo dkp-pacman -Syu --noconfirm
sudo dkp-pacman -S --noconfirm gba-dev

# ---- verification ----
log "verifying installation..."
command -v arm-none-eabi-gcc | tee -a "$LOG"
arm-none-eabi-gcc --version | head -n 1 | tee -a "$LOG"

# ---- done ----
touch "$FLAG"
log "===== setup done $(date -Is) ====="
