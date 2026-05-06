#!/bin/bash
# ============================================================================
# TwoDEngine API Documentation Viewer
# ============================================================================
# This script generates (if needed) and opens the Doxygen API documentation
# ============================================================================

echo ""
echo "========================================"
echo " TwoDEngine API Documentation"
echo "========================================"
echo ""

# Check if Doxygen HTML exists
if [ ! -f "docs/api/html/index.html" ]; then
    echo "[INFO] API documentation not found. Generating now..."
    echo ""

    # Check if Doxygen is installed
    if ! command -v doxygen &> /dev/null; then
        echo "[ERROR] Doxygen is not installed"
        echo "Please install Doxygen from your package manager:"
        echo "  Ubuntu/Debian: sudo apt-get install doxygen"
        echo "  macOS: brew install doxygen"
        exit 1
    fi

    # Generate documentation
    echo "[INFO] Running Doxygen..."
    doxygen Doxyfile
    if [ $? -ne 0 ]; then
        echo "[ERROR] Failed to generate documentation"
        exit 1
    fi
    echo ""
    echo "[SUCCESS] API documentation generated successfully!"
    echo ""
fi

# Open documentation in default browser
echo "[INFO] Opening API documentation in browser..."

# Detect OS and open browser
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    xdg-open docs/api/html/index.html
elif [[ "$OSTYPE" == "darwin"* ]]; then
    open docs/api/html/index.html
else
    echo "[INFO] Please open docs/api/html/index.html in your browser"
fi

echo ""
echo "[SUCCESS] API documentation opened!"
echo "Location: docs/api/html/index.html"
echo ""
