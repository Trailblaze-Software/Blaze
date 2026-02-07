# Releasing Blaze

Blaze uses an automated release process triggered by GitHub tags. When a new version tag is pushed, the CI/CD pipeline builds binaries for multiple platforms, packages the QGIS plugin, and updates the documentation.

## How to Create a Release

To trigger a new release, you need to create and push a git tag following the semantic versioning format (e.g., `v0.0.1`).

### Using the Command Line

1.  **Tag the latest commit**:
    ```bash
    git tag v0.0.1
    ```

2.  **Push the tag to GitHub**:
    ```bash
    git push origin v0.0.1
    ```

### Using the GitHub UI

1.  Go to the repository on GitHub.
2.  Click on **Releases** in the right sidebar.
3.  Click **Draft a new release**.
4.  Click **Choose a tag**, type your version (e.g., `v0.0.1`), and select **Create new tag**.
5.  Click **Publish release**.

---

## What Happens Automatically

Once the tag is pushed, the following actions are performed:

1.  **Application Binaries**: The CI builds and attaches the following installers to the release:
    *   **Windows**: x64 and ARM64 installers (.exe)
    *   **Linux**: x64 and ARM64 Debian packages (.deb)
2.  **QGIS Plugin**: The Blaze Map Loader plugin is packaged into a `.zip` file and attached to the release.
3.  **Documentation**: A new version of the documentation site is published. The `latest` alias will be updated to point to this new release.
4.  **Source Code**: GitHub automatically bundles the source code as `.zip` and `.tar.gz` archives.

## Versioning Policy

We follow [Semantic Versioning (SemVer)](https://semver.org/):
*   **MAJOR** version for incompatible API changes.
*   **MINOR** version for functionality in a backwards compatible manner.
*   **PATCH** version for backwards compatible bug fixes.
