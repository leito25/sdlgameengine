#!/bin/bash
# ============================================================================
# TwoDEngine Documentation Generator
# ============================================================================
# This script generates both Doxygen and MkDocs documentation
# ============================================================================

echo ""
echo "========================================"
echo " TwoDEngine Documentation Generator"
echo "========================================"
echo ""

# ============================================================================
# Generate Doxygen API Documentation
# ============================================================================

echo "[1/2] Generating Doxygen API documentation..."
echo ""

# Check if Doxygen is installed
if ! command -v doxygen &> /dev/null; then
    echo "[ERROR] Doxygen is not installed"
    echo "Please install Doxygen from your package manager:"
    echo "  Ubuntu/Debian: sudo apt-get install doxygen"
    echo "  macOS: brew install doxygen"
    exit 1
fi

# Generate Doxygen docs
doxygen Doxyfile
if [ $? -ne 0 ]; then
    echo "[ERROR] Failed to generate Doxygen documentation"
    exit 1
fi

echo "[SUCCESS] Doxygen documentation generated!"
echo "Location: docs/api/html/index.html"
echo ""

# ============================================================================
# Generate MkDocs User Documentation
# ============================================================================

echo "[2/2] Generating MkDocs user documentation..."
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
    pip3 install mkdocs mkdocs-material
    if [ $? -ne 0 ]; then
        echo "[ERROR] Failed to install MkDocs"
        exit 1
    fi
    echo "[SUCCESS] MkDocs installed!"
    echo ""
fi

# Build MkDocs site
python3 -m mkdocs build
if [ $? -ne 0 ]; then
    echo "[ERROR] Failed to generate MkDocs documentation"
    exit 1
fi

echo "[SUCCESS] MkDocs documentation generated!"
echo "Location: site/index.html"
echo ""

# ============================================================================
# Summary
# ============================================================================

echo "========================================"
echo " Documentation Generation Complete!"
echo "========================================"
echo ""
echo "Generated documentation:"
echo "  1. API Reference (Doxygen):"
echo "     docs/api/html/index.html"
echo ""
echo "  2. User Guide (MkDocs):"
echo "     site/index.html"
echo ""
echo "To view documentation:"
echo "  - Run: ./serve_docs.sh (for live server)"
echo "  - Run: ./view_api_docs.sh (for API docs)"
echo "  - Or open the HTML files directly"
echo ""
