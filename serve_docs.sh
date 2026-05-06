#!/bin/bash
# ============================================================================
# TwoDEngine Documentation Server
# ============================================================================
# This script starts the MkDocs development server to view documentation
# ============================================================================

echo ""
echo "========================================"
echo " TwoDEngine Documentation Server"
echo "========================================"
echo ""

# Check if Python is installed
if ! command -v python3 &> /dev/null; then
    echo "[ERROR] Python 3 is not installed"
    echo "Please install Python 3.7+ from your package manager"
    exit 1
fi

# Check if MkDocs is installed
if ! python3 -m mkdocs --version &> /dev/null; then
    echo "[INFO] MkDocs is not installed. Installing now..."
    echo ""
    pip3 install mkdocs mkdocs-material
    if [ $? -ne 0 ]; then
        echo "[ERROR] Failed to install MkDocs"
        exit 1
    fi
    echo ""
    echo "[SUCCESS] MkDocs installed successfully!"
    echo ""
fi

echo "[INFO] Starting MkDocs development server..."
echo ""
echo "========================================"
echo " Documentation will be available at:"
echo " http://127.0.0.1:8000/TwoDEngine/"
echo "========================================"
echo ""
echo "Press Ctrl+C to stop the server"
echo ""

# Start MkDocs server
python3 -m mkdocs serve

# If server stops
echo ""
echo "[INFO] Documentation server stopped."
