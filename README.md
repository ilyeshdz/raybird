# raybird

A Flappy Bird clone written in C using [raylib](https://www.raylib.com/).

![C](https://img.shields.io/badge/C-11-blue.svg)
![raylib](https://img.shields.io/badge/raylib-5.5-orange.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## Controls

- **SPACE** - Jump
- **ESC** - Toggle pause/resume
- **R** - Restart game (when paused)
- **Q** - Quit game (when paused)

## Building

### Prerequisites

- [raylib](https://github.com/raysan5/raylib) (required)
- GCC or Clang compiler
- Make

### Install raylib

#### macOS

Using Homebrew:
```bash
brew install raylib
```

Or build from source: https://github.com/raysan5/raylib#building-on-macos

#### Linux (Ubuntu/Debian)

```bash
sudo apt install libraylib-dev
```

Or build from source: https://github.com/raysan5/raylib#building-on-linux

#### Windows

Download precompiled binaries from https://github.com/raysan5/raylib/releases or build from source.

### Build

```bash
make
```

### Run

```bash
make run
```

### Clean

```bash
make clean
```

## License

MIT
