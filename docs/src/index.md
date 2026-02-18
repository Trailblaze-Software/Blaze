<div align="center">

  <style>
    .blaze-header {
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 10px;
    }
    .blaze-header img {
      vertical-align: middle;
    }
    .blaze-title {
      font-family: 'Courier New', 'Consolas', 'Monaco', monospace;
      font-size: 2.8em;
      font-weight: 700;
      letter-spacing: 0.05em;
      color: #f36f21;
      display: inline-block;
      text-shadow: 1px 1px 2px rgba(128, 128, 128, 0.15);
    }
    @media (max-width: 768px) {
      .blaze-title {
        font-size: 2em;
        padding: 0.15em 0.3em;
      }
      .blaze-header {
        gap: 5px;
      }
    }
  </style>

  <h1 class="blaze-header">
    <img src="assets/images/blaze_icon.png" alt="Blaze Icon" width="60">
    <span class="blaze-title">BLAZE</span>
  </h1>

  <p><strong>A LIDAR mapping tool for processing point cloud data</strong></p>

  <p>
    <a href="https://cmake.org/"><img src="https://img.shields.io/badge/CMake-3.20+-064F8C?style=flat-square&logo=cmake"></a>
    <a href="https://isocpp.org/"><img src="https://img.shields.io/badge/C++-20-00599C?style=flat-square&logo=c%2B%2B"></a>
    <a href="license.md"><img src="https://img.shields.io/badge/license-GPLv3-blue?style=flat-square"></a>
    <a href="https://github.com/Trailblaze-Software/blaze"><img src="https://img.shields.io/badge/platform-Linux%20%7C%20Windows-lightgrey?style=flat-square"></a>
  </p>

</div>

---

**Blaze** is a LIDAR mapping tool designed for processing, analyzing, and visualizing point cloud data from LAS/LAZ files. Built with modern C++20, Blaze provides both command-line (`blaze-cli`) and graphical interfaces (`Blaze` and `Blaze3D`).

Blaze is free and open-source, however if you generate maps using Blaze, we would appreciate a simple acknowledgement and link to this page [https://trailblaze-software.github.io/Blaze](https://trailblaze-software.github.io/Blaze).

If you run into any problems, please [submit an issue](https://github.com/Trailblaze-Software/Blaze/issues) and we will get back to you. Alternately, feel free to fix it yourself and submit a pull request :)

## Quick Links

- [Installation](installation/index.md)
- [Quick Start Guide](usage/index.md)
- [QGIS Plugin](usage/qgis-plugin.md)

---
