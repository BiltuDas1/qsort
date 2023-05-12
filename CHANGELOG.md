# Changelog

## [unreleased]
- There's Nothing but Crickets ¯\\_(ツ)_/¯

## [0.3.3-beta] - 2023-05-12
### Removed
- Removed the obsolete Operations.md file

### Added
- Added support for passing a custom configuration file (qsort.conf)
- Added beta support for sorting according to file mime type instead of extensions
- Added support for reading path names from [xdg-user-dirs](https://wiki.archlinux.org/title/XDG_user_directories) for qsort.conf
- Added libmagic-dev as a requirement for qsort to work

### Changed
- Updated README.md to reflect new features
- Changed Continuous Integration (CI) process to improve stability

### Fixed
- Fixed a bug that prevented users from passing multiple parameters to qsort at the same time

## [0.3.2-beta] - 2023-05-02
### Changed
- Updated Debian package information to improve compatibility
- Implemented building using CMake for better cross-platform support

### Fixed
- Fixed an error in the AutoCheck feature

### Removed
- Removed Makefile as it is no longer necessary

## [0.3.1-beta] - 2023-05-01
### Changed
- Updated Debian package information to improve compatibility

### Added
- Added AutoRelease feature to automate the release process

## [0.3-beta] - 2023-04-29
### Added
- Added the [MIT License](https://github.com/BiltuDas1/qsort/blob/main/LICENSE) to the project
- Improved control for Debian packages
- Added multithreading feature to improve performance

## [0.2-beta] - unknown
### Added
- Added support for Debian packages
- Implemented building using Makefile
- Added --help parameter to provide usage instructions

## [0.1-beta] - unknown
- Initial release of qsort.  
---

[unreleased]: https://github.com/BiltuDas1/qsort/compare/0.3.3-beta...pre/beta
[0.3.3-beta]: https://github.com/BiltuDas1/qsort/compare/0.3.2-beta...0.3.3-beta
[0.3.2-beta]: https://github.com/BiltuDas1/qsort/compare/0.3.1-beta...0.3.2-beta
[0.3.1-beta]: https://github.com/BiltuDas1/qsort/compare/0.3-beta...0.3.1-beta
[0.3-beta]: https://github.com/BiltuDas1/qsort/releases/tag/v0.3-beta
[0.2-beta]: about:blank
[0.1-beta]: about:blank