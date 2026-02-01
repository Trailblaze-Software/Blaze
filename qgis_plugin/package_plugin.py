#!/usr/bin/env python3
"""
Package the Blaze Loader QGIS plugin into a zip file for installation.

Usage:
    python package_plugin.py
"""

import os
import subprocess
import zipfile
from pathlib import Path


def is_gitignored(filepath, repo_root):
    """Check if a file is gitignored using git check-ignore."""
    result = subprocess.run(
        ["git", "check-ignore", "--quiet", str(filepath)],
        cwd=repo_root,
        capture_output=True,
        check=False,
    )
    return result.returncode == 0


def package_plugin():
    """Create a zip file of the plugin for QGIS installation."""

    # Paths
    plugin_dir = Path(__file__).parent / "blaze_loader"
    output_zip = Path(__file__).parent / "blaze_loader.zip"

    if not plugin_dir.exists():
        print(f"Error: Plugin directory not found: {plugin_dir}")
        return False

    print(f"Packaging plugin from: {plugin_dir}")
    print(f"Output: {output_zip}\n")

    # Remove existing zip if it exists
    if output_zip.exists():
        output_zip.unlink()
        print("Removed existing zip file\n")

    # Create zip file
    repo_root = Path(__file__).parent.parent
    file_count = 0
    with zipfile.ZipFile(output_zip, "w", zipfile.ZIP_DEFLATED) as zipf:
        print("Adding files:")
        for root, dirs, files in os.walk(plugin_dir):
            # Filter out gitignored directories from os.walk
            dirs[:] = [d for d in dirs if not is_gitignored(Path(root) / d, repo_root)]

            for file in files:
                filepath = Path(root) / file

                # Skip if gitignored
                if is_gitignored(filepath, repo_root):
                    continue

                # Add to zip
                arcname = f"blaze_loader/{filepath.relative_to(plugin_dir)}"
                zipf.write(filepath, arcname)
                print(f"  ✓ {filepath.relative_to(plugin_dir)}")
                file_count += 1

    file_size = output_zip.stat().st_size / 1024  # KB
    print("\n✓ Plugin packaged successfully!")
    print(f"  Total files: {file_count}")
    print(f"  File: {output_zip}")
    print(f"  Size: {file_size:.1f} KB")
    print("\nTo install in QGIS:")
    print("  1. Open QGIS")
    print("  2. Go to Plugins > Manage and Install Plugins")
    print("  3. Click 'Install from ZIP' button")
    print(f"  4. Select: {output_zip.name}")
    print("  5. Click 'Install Plugin'")

    return True


if __name__ == "__main__":
    import sys

    success = package_plugin()
    sys.exit(0 if success else 1)
