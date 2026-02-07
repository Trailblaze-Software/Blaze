#!/bin/bash

# Ensure we are in the project root
cd "$(dirname "$0")/.."

# Check for Doxygen
if ! command -v doxygen &> /dev/null; then
    echo "Error: doxygen is not installed."
    echo "Install it with: sudo apt install doxygen graphviz"
    exit 1
fi

# Check for Python dependencies
REQUIRED_PKGS=("mkdocs" "mkdocs-material" "mike" "mkdoxy")
MISSING_PKGS=()

for pkg in "${REQUIRED_PKGS[@]}"; do
    if ! python3 -c "import $pkg" &> /dev/null && ! command -v "$pkg" &> /dev/null; then
        MISSING_PKGS+=("$pkg")
    fi
done

if [ ${#MISSING_PKGS[@]} -ne 0 ]; then
    echo "Missing Python packages: ${MISSING_PKGS[*]}"
    echo "Installing missing packages..."
    pip install "${MISSING_PKGS[@]}"
fi

echo "Starting local documentation server..."
echo "Open http://127.0.0.1:8000 in your browser."
echo "Press Ctrl+C to stop."

# Run mkdocs serve from the docs directory
cd docs && mkdocs serve
