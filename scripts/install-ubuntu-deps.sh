#!/bin/bash

# Use sudo if available and not running as root
if command -v sudo >/dev/null 2>&1 && [ "$(id -u)" -ne 0 ]; then
	SUDO=sudo
else
	SUDO=""
fi

$SUDO apt-get update
$SUDO apt-get install -y --no-install-recommends libgdal-dev libopencv-dev cmake libomp-dev rpm qt6-base-dev \
	libglx-dev libgl1-mesa-dev qt6-image-formats-plugins libqt6svg6-dev ccache mold ninja-build
