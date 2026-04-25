# raybird

A Flappy Bird clone written in C using [raylib](https://www.raylib.com/).

## Controls

- **SPACE** - Jump
- Press SPACE when game over to restart

## Building

### Prerequisites

- [raylib](https://github.com/raysan5/raylib) (required)
- GCC or Clang compiler
- Make (optional, but included in Makefile)

### Install raylib

#### macOS

Using Homebrew:
```bash
brew install raylib
```

Or from source: https://github.com/raysan5/raylib#building-on-macos

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
