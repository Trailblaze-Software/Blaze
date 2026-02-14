#!/usr/bin/env python3
"""
Package the Blaze Loader QGIS plugin into a zip file for installation.

Usage:
    python package_plugin.py
"""

import os
import re
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


def get_release_version():
    """Get the release version from git tag or CMakeLists.txt."""
    repo_root = Path(__file__).parent.parent

    # Try to get version from git tag (same logic as CMakeLists.txt)
    try:
        result = subprocess.run(
            ["git", "describe", "--tags", "--exact-match", "--match", "v*"],
            cwd=repo_root,
            capture_output=True,
            text=True,
            check=False,
        )
        if result.returncode == 0 and result.stdout.strip():
            git_tag = result.stdout.strip()
            # Remove 'v' prefix (e.g., v0.0.1 -> 0.0.1)
            version = re.sub(r"^v", "", git_tag)
            print(f"Version from git tag: {version}")
            return version
    except (subprocess.SubprocessError, FileNotFoundError):
        pass

    # Try to get version from CMakeLists.txt BLAZE_VERSION variable
    cmake_file = repo_root / "CMakeLists.txt"
    if cmake_file.exists():
        try:
            content = cmake_file.read_text()
            # Look for set(BLAZE_VERSION "...") or -DBLAZE_VERSION=...
            match = re.search(r'BLAZE_VERSION[=\s]+["\']?([0-9]+\.[0-9]+\.[0-9]+[^"\']*)["\']?', content)
            if match:
                version = match.group(1).strip()
                # Remove any non-numeric suffixes for plugin version (keep it simple)
                version = re.match(r"^([0-9]+\.[0-9]+\.[0-9]+)", version)
                if version:
                    print(f"Version from CMakeLists.txt: {version.group(1)}")
                    return version.group(1)
        except Exception as e:
            print(f"Warning: Could not read version from CMakeLists.txt: {e}")

    # Fallback: return None to keep existing version
    print("Warning: Could not determine release version, keeping existing version in metadata.txt")
    return None


def update_plugin_version(plugin_dir, version):
    """Update the version in metadata.txt if a new version is provided."""
    if not version:
        return False

    metadata_file = plugin_dir / "metadata.txt"
    if not metadata_file.exists():
        print(f"Warning: metadata.txt not found at {metadata_file}")
        return False

    try:
        content = metadata_file.read_text()
        # Update version line
        new_content = re.sub(r"^version=.*$", f"version={version}", content, flags=re.MULTILINE)

        if new_content != content:
            metadata_file.write_text(new_content)
            print(f"Updated plugin version to: {version}")
            return True
        else:
            print(f"Plugin version already set to: {version}")
            return False
    except Exception as e:
        print(f"Error updating metadata.txt: {e}")
        return False


def get_plugin_version(plugin_dir):
    """Get the current plugin version from metadata.txt."""
    metadata_file = plugin_dir / "metadata.txt"
    if metadata_file.exists():
        try:
            content = metadata_file.read_text()
            match = re.search(r"^version=(.+)$", content, re.MULTILINE)
            if match:
                return match.group(1).strip()
        except Exception:
            pass
    return None


def package_plugin():
    """Create a zip file of the plugin for QGIS installation."""

    # Paths
    plugin_dir = Path(__file__).parent / "blaze_loader"

    if not plugin_dir.exists():
        print(f"Error: Plugin directory not found: {plugin_dir}")
        return False

    # Sync version with release version
    print("Syncing plugin version with release version...")
    release_version = get_release_version()
    if release_version:
        update_plugin_version(plugin_dir, release_version)

    # Get the final version (from release or metadata.txt)
    plugin_version = release_version or get_plugin_version(plugin_dir) or "unknown"

    # Create versioned zip filename
    if plugin_version and plugin_version != "unknown":
        output_zip = Path(__file__).parent / f"blaze_loader_qgis_plugin_v{plugin_version}.zip"
    else:
        output_zip = Path(__file__).parent / "blaze_loader_qgis_plugin.zip"

    print()

    print(f"Packaging plugin from: {plugin_dir}")
    print(f"Output: {output_zip}")
    print(f"Version: {plugin_version}\n")

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
