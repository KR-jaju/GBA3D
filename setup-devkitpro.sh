#!/usr/bin/env bash
set -euo pipefail
export DEBIAN_FRONTEND=noninteractive

log(){ echo "[devkitPro] $*"; }

# 이미 있으면 종료
if command -v arm-none-eabi-gcc >/dev/null 2>&1 && [[ -d /opt/devkitpro ]]; then
  log "already installed"
  arm-none-eabi-gcc --version | head -n 1
  exit 0
fi

# apt 락 대기
while sudo fuser /var/lib/dpkg/lock-frontend >/dev/null 2>&1 \
   || sudo fuser /var/lib/dpkg/lock >/dev/null 2>&1 \
   || sudo fuser /var/lib/apt/lists/lock >/dev/null 2>&1; do
  log "apt/dpkg lock held, waiting..."
  sleep 2
done

log "installing prerequisites..."
sudo apt-get update -y
sudo apt-get install -y --no-install-recommends \
  ca-certificates wget gnupg dirmngr \
  build-essential make git xz-utils unzip tar

log "installing devkitPro pacman..."
wget -q https://apt.devkitpro.org/install-devkitpro-pacman -O /tmp/install-devkitpro-pacman
chmod +x /tmp/install-devkitpro-pacman
sudo /tmp/install-devkitpro-pacman

log "installing gba-dev..."
sudo dkp-pacman -Syu --noconfirm
sudo dkp-pacman -S --noconfirm gba-dev

log "done"
arm-none-eabi-gcc --version | head -n 1
