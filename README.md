*This project has been created as part of the 42 curriculum by ryatan.*

# FDF — Wireframe Model

## Description

FDF (short for *fil de fer*, French for "wireframe model") is a 42 School graphics project that reads a heightmap file and renders it as an isometric 3D wireframe landscape using the MiniLibX library.

Each point in the `.fdf` file represents a vertex in 3D space: its column index is the X coordinate, its row index is the Y coordinate, and its integer value is the Z (altitude). Adjacent points are connected by line segments drawn using Bresenham's line algorithm, producing a mesh that visually conveys the terrain's elevation.

The program supports per-vertex color encoding directly in the `.fdf` file (e.g. `10,0xFF0000` for a red peak), automatic scale fitting so the map fills the window regardless of its size, and clean window/event management (ESC or clicking the close button exits gracefully).

---

## Program Flow

```
main()
  │
  ├─ parse_map_2d()          // Read the .fdf file line-by-line with get_next_line()
  │    ├─ init_outer()       // Zero-initialise the outer array struct
  │    ├─ create_array()     // First pass: count lines, malloc outer_array
  │    └─ process_map()      // Second pass: copy each line (strip trailing \n)
  │
  ├─ parse_map_3d()          // Convert raw strings into integer z-values + colors
  │    └─ split_rows()       // ft_split each row on ' ', atoi z, parse_color hex
  │
  ├─ free_all()              // Release the intermediate string array
  │
  ├─ init_win_data()         // mlx_init, new window, new image, get data addr
  │
  ├─ find_z_range()          // Scan all z values to find z_min and z_max
  │
  ├─ compute_scale()         // Derive scale + offset_x/y to fit map in window
  │
  ├─ render_iso()            // Draw every vertex connection onto the mlx image
  │    └─ draw_connections() // For each (i,j): project to 2D, bresenham to right & down
  │         ├─ project()     // Isometric projection: rotate 30°, apply scale/offset
  │         └─ bresenham()   // Rasterise a line segment pixel-by-pixel
  │
  └─ window_loop()           // Register hooks, enter mlx_loop (blocking)
       ├─ key_handler()      // ESC (65307) → window_close_handler
       └─ window_close_handler() // free_map, destroy mlx resources, exit(0)
```

---

## Function Reference

### `main.c`
| Function | Description |
|----------|-------------|
| `main(argc, argv)` | Entry point. Orchestrates parsing → window init → scale computation → rendering → event loop. |

### `parse_map_2d.c`
| Function | Description |
|----------|-------------|
| `parse_map_2d(path, outer)` | Top-level 2D parser. Calls init, create, and process in sequence. Returns the filled `outer_array`. |
| `init_outer(outer)` | Zeroes out the `t_outer_array` struct before use. |
| `create_array(path, outer)` | First file pass: counts lines with `get_next_line`, then `malloc`s the pointer array with a NULL sentinel. |
| `process_map(path, outer)` | Second file pass: reads each line again, strips the trailing `\n`, and copies it into the pre-allocated slots with `ft_calloc` + `ft_memcpy`. |
| `print_parsed_map(map, outer)` | Debug helper — prints every raw line to stdout (can be removed before submission). |

### `parse_map_3d.c`
| Function | Description |
|----------|-------------|
| `parse_map_3d(outer_array, map)` | Counts rows from the NULL-terminated array, allocates `rows_array` and `colors`, then calls `split_rows` for each row. Sets `map->cols` from the first row's element count. |
| `split_rows(row_str, z_array, colors_row)` | Splits a space-separated string with `ft_split`. For each token: `ft_atoi` gives the z value, `parse_color` extracts an optional hex color. |
| `parse_color(token)` | Looks for a comma in the token (e.g. `5,0xFF8800`). If found, passes the substring after the comma to `hex_to_dec`; otherwise returns `-1` (use default color). |
| `compute_scale(map, w)` | Computes a uniform integer scale so the projected map fits within the window dimensions, then sets `offset_x`/`offset_y` to center it. |
| `find_z_range(map, z_min, z_max)` | Linear scan over all z values to establish the altitude range used by `compute_scale`. |

### `rendering.c`
| Function | Description |
|----------|-------------|
| `render_iso(w, map)` | Outer loop over every `(i, j)` cell. Calls `draw_connections` for each, then pushes the completed image to the window with `mlx_put_image_to_window`. |
| `draw_connections(w, map, i, j)` | Projects the current point, then draws a line to the right neighbour `(i, j+1)` and the lower neighbour `(i+1, j)` if they exist. Uses the per-vertex color if set, otherwise WHITE. |
| `project(x, y, z, map)` | Applies the standard isometric projection: `screen_x = (x - y) * cos(30°) * scale + offset_x`, `screen_y = (x + y) * sin(30°) * scale - z * scale + offset_y`. |
| `bresenham(w, p0, p1, color)` | Classic Bresenham line rasteriser. Drives two error accumulators (`dx`, `dy`) to step one pixel at a time from `p0` to `p1`, calling `put_pixel` at each step. |
| `put_pixel(w_data, x, y, color)` | Bounds-checks `(x, y)` then writes the 32-bit color value directly into the mlx image's raw memory buffer. |

### `window_event.c`
| Function | Description |
|----------|-------------|
| `init_win_data()` | Creates the mlx connection, a 1280×900 window, an off-screen image of the same size, and retrieves the image's raw data address. |
| `find_z_range(map, z_min, z_max)` | (Declared here, used in main) Scans the full map to set `*z_min` and `*z_max`. |
| `key_handler(keycode, fdf)` | Receives all keypress events; currently maps ESC (keycode 65307) to `window_close_handler`. |
| `window_close_handler(fdf)` | Frees map memory, destroys the image, window, and display, frees the mlx pointer, then calls `exit(0)`. |
| `window_loop(w_data, fdf)` | Registers the keypress hook (event 2) and window-destroy hook (event 17), then enters `mlx_loop`. |

### `helpers.c`
| Function | Description |
|----------|-------------|
| `hex_to_dec(str)` | Converts a hex string (with or without `0x`/`0X` prefix) to an integer. Supports uppercase and lowercase digits. |
| `free_all(array)` | Iterates a NULL-terminated `char **`, frees each string, then frees the array pointer itself. |
| `free_map(map)` | For each row, frees `rows_array[i].array` and `colors[i]`, then frees the `rows_array` and `colors` top-level pointers. |

---

## Instructions

### Dependencies
- MiniLibX (Linux version with X11)
- A C compiler (`cc`) with `-Wall -Wextra -Werror`
- `libft` and `ft_printf` (included as submodules/folders)
- `get_next_line` (included under `get_next_line/`)

### Compilation
```bash
make        # builds ./fdf
make clean  # removes object files
make fclean # removes objects + binary
make re     # fclean then all
```

### Execution
```bash
./fdf path/to/map.fdf
```

The `.fdf` format is a grid of space-separated integers, one row per line. Optional per-vertex colors can be appended with a comma: `10,0xFF8800`.

Press **ESC** or click the window's close button to exit cleanly.

---

## Resources

### Documentation & References
- [MiniLibX Linux documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Bresenham's line algorithm — Wikipedia](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- [Isometric projection — Wikipedia](https://en.wikipedia.org/wiki/Isometric_projection)
- [Isometric math explained (tileengines)](https://clintbellanger.net/articles/isometric_math/)
- [42 Docs — FDF overview](https://harm-smits.github.io/42docs/projects/fdf)

### AI Usage
Claude (Anthropic) was used during this project for the following tasks:
- Explaining the mathematics behind the isometric projection formula and validating the `compute_scale` offset calculation.
