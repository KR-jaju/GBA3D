#!/usr/bin/env bash
set -euo pipefail

# 이미 설치돼 있으면 스킵(재실행 안전)
if command -v arm-none-eabi-gcc >/dev/null 2>&1 && [[ -d "${DEVKITPRO:-/opt/devkitpro}" ]]; then
  echo "[devkitPro] already installed"
  exit 0
fi

echo "[devkitPro] installing prerequisites..."
sudo apt-get update
sudo apt-get install -y wget ca-certificates gnupg build-essential make git

echo "[devkitPro] installing dkp-pacman..."
wget -q https://apt.devkitpro.org/install-devkitpro-pacman -O /tmp/install-devkitpro-pacman
chmod +x /tmp/install-devkitpro-pacman
sudo /tmp/install-devkitpro-pacman

# dkp-pacman 설치 후에는 보통 /opt/devkitpro 아래로 깔림
# 이 환경변수는 셸 세션에서 계속 필요하니 profile에 박아둠
echo 'export DEVKITPRO=/opt/devkitpro' | sudo tee /etc/profile.d/devkitpro.sh >/dev/null
echo 'export DEVKITARM=/opt/devkitpro/devkitARM' | sudo tee -a /etc/profile.d/devkitpro.sh >/dev/null
echo 'export PATH="$PATH:$DEVKITARM/bin"' | sudo tee -a /etc/profile.d/devkitpro.sh >/dev/null

echo "[devkitPro] installing gba-dev..."
sudo dkp-pacman -Syu --noconfirm
sudo dkp-pacman -S --noconfirm gba-dev

echo "[devkitPro] done"
