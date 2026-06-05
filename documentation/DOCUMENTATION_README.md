# TwoDEngine Documentation System

This document explains how to generate and view the TwoDEngine documentation.

## Documentation Overview

TwoDEngine uses a dual documentation system:

1. **Doxygen**: Generates API reference documentation from source code comments
2. **MkDocs with Material Theme**: Creates user-friendly guides and tutorials

## Prerequisites

### For Doxygen
- **Doxygen**: Download from [doxygen.nl](https://www.doxygen.nl/download.html)
- Add Doxygen to your system PATH

### For MkDocs
- **Python 3.7+**: Required for MkDocs
- **pip**: Python package manager

## Installation

### Install MkDocs and Material Theme

```bash
# Install MkDocs and Material theme
pip install mkdocs mkdocs-material

# Verify installation
mkdocs --version
```

## Generating Documentation

### Generate Doxygen API Documentation

```bash
# Generate API documentation
doxygen Doxyfile

# Output location: docs/api/html/
```

### Generate MkDocs User Documentation

```bash
# Build static site
mkdocs build

# Output location: site/
```

### Serve Documentation Locally

```bash
# Start local development server
mkdocs serve

# Open browser to: http://127.0.0.1:8000
```

The development server supports hot-reloading, so changes to documentation files are reflected immediately.

## Documentation Structure

```
TwoDEngine/
├── docs/                           # MkDocs documentation source
│   ├── index.md                    # Home page
│   ├── getting-started/            # Getting started guides
│   │   ├── quickstart.md          # Quick start guide
│   │   └── building.md            # Build instructions
│   ├── user-guide/                 # User guides
│   │   └── overview.md            # User guide overview
│   ├── api/                        # API reference
│   │   ├── overview.md            # API overview
│   │   ├── game.md                # Game class documentation
│   │   ├── html/                  # Generated Doxygen HTML (auto-generated)
│   │   └── xml/                   # Generated Doxygen XML (auto-generated)
│   ├── examples/                   # Code examples
│   │   └── basic-game.md          # Basic game example
│   └── development/                # Development guides
│       └── contributing.md        # Contributing guide
├── src/                            # Source code with Doxygen comments
│   ├── Game.h                     # Game class header (documented)
│   ├── Game.cpp                   # Game class implementation
│   └── Main.cpp                   # Main entry point
├── Doxyfile                        # Doxygen configuration
├── mkdocs.yml                      # MkDocs configuration
├── site/                           # Generated MkDocs site (auto-generated)
└── DOCUMENTATION_README.md         # This file
```

## Viewing Documentation

### View Doxygen Documentation

#### Windows
```cmd
start docs/api/html/index.html
```

#### Linux
```bash
xdg-open docs/api/html/index.html
```

#### macOS
```bash
open docs/api/html/index.html
```

### View MkDocs Documentation

#### Option 1: Local Server (Recommended)
```bash
mkdocs serve
# Open http://127.0.0.1:8000 in your browser
```

#### Option 2: Static Files
```bash
# Build the site
mkdocs build

# Open site/index.html in your browser
```

## Writing Documentation

### Adding Doxygen Comments

Document your code using Doxygen-style comments:

```cpp
/**
 * @brief Brief description of the function
 *
 * Detailed description goes here. You can use multiple
 * lines to explain the function's behavior.
 *
 * @param paramName Description of the parameter
 * @return Description of the return value
 *
 * @note Important notes about usage
 * @warning Warnings about potential issues
 *
 * @code
 * // Usage example
 * MyClass obj;
 * obj.MyFunction(42);
 * @endcode
 *
 * @see RelatedFunction(), RelatedClass
 */
void MyFunction(int paramName);
```

### Adding MkDocs Pages

1. Create a new `.md` file in the appropriate `docs/` subdirectory
2. Add the page to `mkdocs.yml` navigation:

```yaml
nav:
  - Home: index.md
  - Getting Started:
      - Quick Start: getting-started/quickstart.md
      - Your New Page: getting-started/your-page.md  # Add here
```

3. Write content using Markdown with Material extensions

### Markdown Features

MkDocs with Material theme supports:

#### Admonitions
```markdown
!!! note "Optional Title"
    This is a note admonition.

!!! warning
    This is a warning.

!!! tip
    This is a helpful tip.
```

#### Code Blocks with Syntax Highlighting
```markdown
​```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
​```
```

#### Tabs
```markdown
=== "C++"
    ​```cpp
    std::cout << "Hello" << std::endl;
    ​```

=== "Python"
    ​```python
    print("Hello")
    ​```
```

#### Grid Cards
```markdown
<div class="grid cards" markdown>

-   :material-clock-fast:{ .lg .middle } __Fast Setup__

    ---

    Get started in minutes

    [:octicons-arrow-right-24: Quick Start](quickstart.md)

</div>
```

## Deploying Documentation

### GitHub Pages

```bash
# Deploy to GitHub Pages
mkdocs gh-deploy

# This builds the site and pushes to gh-pages branch
```

### Manual Deployment

```bash
# Build the site
mkdocs build

# Upload the 'site/' directory to your web server
```

## Configuration

### Doxygen Configuration

Edit `Doxyfile` to customize:

- `PROJECT_NAME`: Project name
- `PROJECT_NUMBER`: Version number
- `INPUT`: Source directories to document
- `OUTPUT_DIRECTORY`: Where to generate docs
- `GENERATE_HTML`: Enable HTML output
- `GENERATE_XML`: Enable XML output (for MkDocs integration)

### MkDocs Configuration

Edit `mkdocs.yml` to customize:

- `site_name`: Site title
- `theme`: Theme settings (colors, fonts, features)
- `nav`: Navigation structure
- `plugins`: Enabled plugins
- `markdown_extensions`: Markdown features

## Troubleshooting

### Doxygen Issues

**Issue**: "doxygen: command not found"
```bash
# Install Doxygen
# Windows: Download from doxygen.nl
# Linux: sudo apt-get install doxygen
# macOS: brew install doxygen
```

**Issue**: Warnings about undocumented functions
- Add Doxygen comments to all public APIs
- Use `@brief`, `@param`, `@return` tags

### MkDocs Issues

**Issue**: "mkdocs: command not found"
```bash
# Install MkDocs
pip install mkdocs mkdocs-material
```

**Issue**: "Config value 'plugins': The 'X' plugin is not installed"
```bash
# Install missing plugin
pip install mkdocs-X-plugin
```

**Issue**: Broken links in documentation
- Check that referenced files exist in `docs/` directory
- Verify paths in markdown links are correct
- Run `mkdocs build` to see all warnings

## Best Practices

### For API Documentation (Doxygen)

1. **Document all public APIs**: Every public class, method, and function
2. **Use consistent style**: Follow the Doxygen comment format
3. **Include examples**: Add `@code` blocks showing usage
4. **Link related items**: Use `@see` to reference related functions
5. **Keep it updated**: Update docs when code changes

### For User Documentation (MkDocs)

1. **Write for your audience**: Assume readers are learning
2. **Use examples**: Show, don't just tell
3. **Structure logically**: Organize content from basic to advanced
4. **Add visuals**: Use diagrams, screenshots, and code examples
5. **Test your docs**: Follow your own tutorials to verify accuracy

## Continuous Integration

### GitHub Actions Example

Create `.github/workflows/docs.yml`:

```yaml
name: Documentation

on:
  push:
    branches: [main]

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2

      - name: Setup Python
        uses: actions/setup-python@v2
        with:
          python-version: 3.x

      - name: Install dependencies
        run: |
          pip install mkdocs mkdocs-material
          sudo apt-get install doxygen

      - name: Generate Doxygen docs
        run: doxygen Doxyfile

      - name: Deploy MkDocs
        run: mkdocs gh-deploy --force
```

## Additional Resources

- **Doxygen Manual**: https://www.doxygen.nl/manual/
- **MkDocs Documentation**: https://www.mkdocs.org/
- **Material for MkDocs**: https://squidfunk.github.io/mkdocs-material/
- **Markdown Guide**: https://www.markdownguide.org/

## Quick Reference

### Common Commands

```bash
# Generate Doxygen docs
doxygen Doxyfile

# Build MkDocs site
mkdocs build

# Serve MkDocs locally
mkdocs serve

# Deploy to GitHub Pages
mkdocs gh-deploy

# Clean generated files
rm -rf site/ docs/api/html/ docs/api/xml/
```

### File Locations

- **Doxygen Config**: `Doxyfile`
- **MkDocs Config**: `mkdocs.yml`
- **Documentation Source**: `docs/`
- **Generated Doxygen**: `docs/api/html/`
- **Generated MkDocs**: `site/`

---

**Last Updated**: 2026-05-06

For questions or issues, please open an issue on GitHub or consult the documentation.
