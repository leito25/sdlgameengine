# Documentation Scripts

This directory contains convenient scripts for generating and viewing TwoDEngine documentation.

## Available Scripts

### Windows Scripts (.bat)

| Script | Purpose | Usage |
|--------|---------|-------|
| [`serve_docs.bat`](serve_docs.bat:1) | Start MkDocs development server | Double-click or run `serve_docs.bat` |
| [`view_api_docs.bat`](view_api_docs.bat:1) | Open Doxygen API documentation | Double-click or run `view_api_docs.bat` |
| [`generate_all_docs.bat`](generate_all_docs.bat:1) | Generate all documentation | Double-click or run `generate_all_docs.bat` |

### Linux/macOS Scripts (.sh)

| Script | Purpose | Usage |
|--------|---------|-------|
| [`serve_docs.sh`](serve_docs.sh:1) | Start MkDocs development server | `./serve_docs.sh` |
| [`view_api_docs.sh`](view_api_docs.sh:1) | Open Doxygen API documentation | `./view_api_docs.sh` |
| [`generate_all_docs.sh`](generate_all_docs.sh:1) | Generate all documentation | `./generate_all_docs.sh` |

## Quick Start

### View Documentation (Recommended)

**Windows:**
```cmd
serve_docs.bat
```

**Linux/macOS:**
```bash
chmod +x serve_docs.sh  # First time only
./serve_docs.sh
```

Then open your browser to: **http://127.0.0.1:8000/TwoDEngine/**

### View API Documentation

**Windows:**
```cmd
view_api_docs.bat
```

**Linux/macOS:**
```bash
chmod +x view_api_docs.sh  # First time only
./view_api_docs.sh
```

### Generate All Documentation

**Windows:**
```cmd
generate_all_docs.bat
```

**Linux/macOS:**
```bash
chmod +x generate_all_docs.sh  # First time only
./generate_all_docs.sh
```

## Script Details

### serve_docs.bat / serve_docs.sh

**What it does:**
- Checks if Python is installed
- Installs MkDocs and Material theme if needed
- Starts the MkDocs development server
- Opens documentation at http://127.0.0.1:8000/TwoDEngine/

**Features:**
- Auto-installs dependencies
- Hot-reload: Changes to docs are reflected immediately
- Press Ctrl+C to stop the server

**Output:**
```
========================================
 TwoDEngine Documentation Server
========================================

[INFO] Starting MkDocs development server...

========================================
 Documentation will be available at:
 http://127.0.0.1:8000/TwoDEngine/
========================================

Press Ctrl+C to stop the server
```

### view_api_docs.bat / view_api_docs.sh

**What it does:**
- Checks if Doxygen documentation exists
- Generates it if missing (runs Doxygen)
- Opens the API documentation in your default browser

**Features:**
- Auto-generates docs if needed
- Opens directly in browser
- Shows location of documentation files

**Output:**
```
========================================
 TwoDEngine API Documentation
========================================

[INFO] Opening API documentation in browser...

[SUCCESS] API documentation opened!
Location: docs/api/html/index.html
```

### generate_all_docs.bat / generate_all_docs.sh

**What it does:**
1. Generates Doxygen API documentation
2. Generates MkDocs user documentation
3. Shows summary of generated files

**Features:**
- Checks all prerequisites
- Installs MkDocs if needed
- Generates both documentation systems
- Provides summary with file locations

**Output:**
```
========================================
 TwoDEngine Documentation Generator
========================================

[1/2] Generating Doxygen API documentation...
[SUCCESS] Doxygen documentation generated!
Location: docs/api/html/index.html

[2/2] Generating MkDocs user documentation...
[SUCCESS] MkDocs documentation generated!
Location: site/index.html

========================================
 Documentation Generation Complete!
========================================

Generated documentation:
  1. API Reference (Doxygen):
     docs/api/html/index.html

  2. User Guide (MkDocs):
     site/index.html
```

## Prerequisites

### For All Scripts
- **Python 3.7+**: Required for MkDocs
- **Doxygen**: Required for API documentation

### Installation

#### Windows
```cmd
# Python: Download from https://www.python.org/
# Doxygen: Download from https://www.doxygen.nl/download.html

# MkDocs (auto-installed by scripts, or manually):
pip install mkdocs mkdocs-material
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install python3 python3-pip doxygen

# MkDocs (auto-installed by scripts, or manually):
pip3 install mkdocs mkdocs-material
```

#### macOS
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install python doxygen

# MkDocs (auto-installed by scripts, or manually):
pip3 install mkdocs mkdocs-material
```

## Troubleshooting

### "Python is not installed or not in PATH"
- Install Python from https://www.python.org/
- Make sure to check "Add Python to PATH" during installation
- Restart your terminal/command prompt

### "Doxygen is not installed or not in PATH"
- Install Doxygen from https://www.doxygen.nl/download.html
- Add Doxygen to your system PATH
- Restart your terminal/command prompt

### "Permission denied" (Linux/macOS)
```bash
# Make scripts executable
chmod +x serve_docs.sh view_api_docs.sh generate_all_docs.sh
```

### MkDocs server won't start
```bash
# Check if port 8000 is already in use
# Windows:
netstat -ano | findstr :8000

# Linux/macOS:
lsof -i :8000

# Kill the process or use a different port:
mkdocs serve -a 127.0.0.1:8001
```

### Documentation not updating
```bash
# Clean and regenerate
rm -rf site/ docs/api/html/ docs/api/xml/  # Linux/macOS
rmdir /s site docs\api\html docs\api\xml   # Windows

# Then regenerate
./generate_all_docs.sh  # Linux/macOS
generate_all_docs.bat   # Windows
```

## Manual Commands

If you prefer to run commands manually:

### MkDocs Commands
```bash
# Serve with hot-reload
mkdocs serve

# Build static site
mkdocs build

# Deploy to GitHub Pages
mkdocs gh-deploy
```

### Doxygen Commands
```bash
# Generate documentation
doxygen Doxyfile

# Update configuration
doxygen -u Doxyfile
```

## Documentation Structure

After running the scripts, you'll have:

```
TwoDEngine/
├── docs/
│   ├── api/
│   │   ├── html/          # Doxygen HTML output
│   │   └── xml/           # Doxygen XML output
│   ├── getting-started/
│   ├── user-guide/
│   ├── examples/
│   └── development/
├── site/                  # MkDocs static site
├── serve_docs.bat         # Start MkDocs server (Windows)
├── serve_docs.sh          # Start MkDocs server (Linux/macOS)
├── view_api_docs.bat      # View API docs (Windows)
├── view_api_docs.sh       # View API docs (Linux/macOS)
├── generate_all_docs.bat  # Generate all docs (Windows)
└── generate_all_docs.sh   # Generate all docs (Linux/macOS)
```

## Additional Resources

- **Full Documentation Guide**: See [`DOCUMENTATION_README.md`](DOCUMENTATION_README.md:1)
- **MkDocs Documentation**: https://www.mkdocs.org/
- **Material for MkDocs**: https://squidfunk.github.io/mkdocs-material/
- **Doxygen Manual**: https://www.doxygen.nl/manual/

## Tips

1. **Use serve_docs for development**: The hot-reload feature makes writing docs much faster
2. **Generate all docs before committing**: Run `generate_all_docs` to ensure everything builds
3. **Check for warnings**: Both Doxygen and MkDocs show warnings about missing links or documentation
4. **Keep docs in sync**: Update documentation when you change code

---

**Need help?** Check [`DOCUMENTATION_README.md`](DOCUMENTATION_README.md:1) for detailed documentation system information.
