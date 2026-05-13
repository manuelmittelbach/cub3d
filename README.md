*This project has been created as part of the 42 curriculum by mmittelb, jnieders.*

# cub3D

A first-person raycasting engine built with the MiniLibX, inspired by the original
Wolfenstein 3D. The player walks through a textured maze loaded from a `.cub` scene
file, with smooth movement, mouse-look and a live minimap.

<br>

## Description

`cub3D` renders a 3D view of a 2D grid map using **raycasting** — for every column of
the screen, a single ray is cast through the grid until it hits a wall. The distance to
that hit decides the height of the vertical strip drawn on screen, and the side of the
wall that was hit picks one of four textures (North, South, West, East).

The engine uses the **DDA (Digital Differential Analyzer)** algorithm to step the rays
across grid lines efficiently — no per-ray trigonometry. Player orientation is held as
a direction vector plus a perpendicular camera plane (FOV ≈ 66°), rotated via a 2D
rotation matrix, following the approach described in Lode Vandevenne's tutorial.

<br>

## Features

### Mandatory

- Parses `.cub` scene files with textures, floor/ceiling colors and the map grid
- Strict validation: required elements, valid characters, surrounding walls, single
  spawn point, RGB range and format
- Four wall textures depending on the wall side (NO / SO / WE / EA)
- Floor and ceiling drawn with two configurable RGB colors
- WASD movement, arrow-key rotation
- ESC or the window close button cleanly tear down the program
- Image-buffered rendering (`mlx_new_image` + `mlx_put_image_to_window`) — no direct
  pixel writes to the window
- Memory clean on every exit path (`valgrind --leak-check=full`: 0 definitely / 0
  indirectly / 0 possibly lost; only X11/mlx still-reachable allocations remain)

### Bonus

- **Wall collisions** with axis-separate checks (slide along walls when moving
  diagonally into a corner)
- **Minimap** overlay showing the surrounding walls and the player's facing direction
  (toggle with `M`)
- **Mouse-look** for horizontal rotation, with a hidden cursor recentered every frame
  (toggle with `T`)

<br>

## Instructions

### Requirements

- A Unix-like environment with an X server (Linux native, WSL with X, or macOS with
  XQuartz)
- `make` and a C compiler (`cc` / `clang` / `gcc`)
- X11 development headers (`libxext-dev`, `libx11-dev` on Debian/Ubuntu)

### Build

```bash
make            # builds the cub3D binary
make clean      # remove object files
make fclean     # remove objects + binary
make re         # full rebuild
make bonus      # same binary; bonus features are built in
```

The bundled `minilibx-linux` is compiled automatically as part of the build.

### Run

```bash
./cub3D maps/map128.cub
```

Any file with a `.cub` extension and a valid scene description works.

<br>

## Controls

| Key | Action |
|---|---|
| `W` / `A` / `S` / `D` | Move forward / strafe left / back / strafe right |
| `←` / `→` | Rotate the view |
| Mouse (horizontal) | Rotate the view (when enabled) |
| `M` | Toggle the minimap on / off |
| `T` | Toggle the mouse-look on / off |
| `ESC` | Quit the program |
| Window close (✕) | Quit the program |

<br>

## Scene file format (`.cub`)

The file contains six elements in any order, followed by the map grid as the very last
block. Empty lines may separate elements, but not inside the map.

```text
NO ./assets/128/n_128x128.xpm
SO ./assets/128/s_128x128.xpm
WE ./assets/128/w_128x128.xpm
EA ./assets/128/e_128x128.xpm

F 242,215,172
C 173,216,230

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11000000110101011100000010001
10000000000000001100000000001
11000001110101011111011110N01
11110111 1110101 101111010001
11111111 1111111 111111111111
```

- Texture identifiers: `NO`, `SO`, `WE`, `EA` followed by an XPM path
- Colors: `F` and `C` followed by `R,G,B` with each value in `[0, 255]`
- Map characters: `0` (floor), `1` (wall), `N`/`S`/`E`/`W` (player spawn + facing),
  space (outside the playable area)
- Exactly one spawn point per map
- The walkable area must be fully enclosed by walls — checked via flood fill from the
  spawn position

On any misconfiguration the program prints `Error\n` followed by an explanatory line
and exits without leaks.

<br>

## Project structure

```text
.
├── Makefile
├── inc/
│   ├── cub3d.h
│   ├── check_input_file.h
│   ├── get_next_line.h
│   ├── libft.h
│   └── minimap.h
├── src/
│   ├── main.c
│   ├── parsing/        # .cub file parsing + map validation
│   ├── mlx/            # window/image init, texture loading, cleanup
│   ├── raycaster/      # DDA loop, wall rendering, floor/ceiling
│   ├── player/         # input events, movement, rotation
│   ├── minimap/        # minimap overlay
│   ├── utils/          # get_next_line + small helpers
│   └── libft/          # the standard 42 libft
├── minilibx-linux/     # bundled MiniLibX source
├── assets/             # XPM wall textures
└── maps/               # example .cub scene files
```

<br>

## Resources

The following references shaped the architecture and the math behind this project:

- **Lode Vandevenne — Raycasting tutorial (Part 1 & 2)**
  [lodev.org/cgtutor/raycasting.html](https://lodev.org/cgtutor/raycasting.html) and
  [raycasting2.html](https://lodev.org/cgtutor/raycasting2.html). The variable names
  and the overall structure of our ray loop follow this tutorial closely.
- **Harm Smits — 42 docs: MiniLibX**
  [harm-smits.github.io/42docs/libs/minilibx](https://harm-smits.github.io/42docs/libs/minilibx).
  Used as the practical MiniLibX reference, since the official documentation is sparse.

### Use of AI

AI tools were used as a **learning aid** during development, mostly to:

- Clarify the theory behind raycasting and the DDA algorithm (what the math actually
  represents, why the camera plane needs to be perpendicular to the direction
  vector, etc.)
- Discuss algorithmic choices (vector-based rotation vs. angle-based, axis-separate
  collision checks vs. a hitbox radius)

All code in this repository was written and integrated by the project authors. AI was
not used to generate complete functions or to copy implementations verbatim.
