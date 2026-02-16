# Contributing

Contributions are welcome! Please feel free to submit a pull request at [https://github.com/Trailblaze-Software/Blaze/pulls](https://github.com/Trailblaze-Software/Blaze/pulls).

## Licensing

By contributing to Blaze, you agree that your contributions will be licensed under the project's [GPLv3 License](license.md) and grant an implicit perpetual, irrevocable, non-exclusive, royalty-free license to Trailblaze Software to use, modify, distribute and adapt your contributions without limitation.

## Development Workflow

1. **Fork the repository** on GitHub.
2. **Clone your fork** locally.
3. **Create a branch** for your feature or bugfix.
4. **Commit your changes** (see formatting guidelines below).
5. **Push to your fork** and submit a **Pull Request**.

## Coding Standards

- **Pre-commit**: We recommend installing `pre-commit` to automatically run linters and formatting before committing. The CI will not allow a PR to be merged until these requirements have been met.

    ```bash
    pip install pre-commit
    pre-commit install
    ```

    You can then run pre-commit on all files using `pre-commit run -a`.

- **C++**: We use C++20. Please follow the existing code patterns and style where possible. We use `clang-format` in the pre-commit to maintain consistency.
