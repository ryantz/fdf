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
  ├─ error_checks()          // Validate argc, check file exists and is readable
  │
  ├─ parse_map_2d()          // Read the .fdf file line-by-line with get_next_line()
  │    ├─ init_outer()       // Zero-initialise the outer array struct
  │    ├─ create_array()     // First pass: count non-blank lines, calloc outer_array
  │    └─ process_map()      // Second pass: copy each line (strip trailing \n)
  │         └─ drain_gnl()   // Flush any remaining GNL static buffer after reading
  │
  ├─ parse_map_3d()          // Convert raw strings into integer z-values + colors
  │    ├─ count_rows()       // Count NULL-terminated outer_array entries
  │    └─ fill_rows()        // Call split_rows for each row, validate column count
  │         └─ split_rows()  // ft_split each row on ' ', atoi z, parse_color hex
  │              └─ fill_arrays() // Populate z and color arrays from split tokens
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
| `main(argc, argv)` | Entry point. Runs error checks, orchestrates parsing → window init → scale computation → rendering → event loop. |

### `errors.c`
| Function | Description |
|----------|-------------|
| `error_checks(argc, argv)` | Validates argument count, checks the file exists with `access(F_OK)`, and checks read permission with `access(R_OK)`. Prints an appropriate message and returns 1 on any failure. |
| `print_error(err)` | Writes a human-readable error message to stderr using the `e_error` enum values (`WRONG_ARGS`, `WRONG_MAP_FORMAT`, `NO_FILE`, `NO_PERMISSIONS`). |

### `parse_map_2d.c`
| Function | Description |
|----------|-------------|
| `parse_map_2d(path, outer)` | Top-level 2D parser. Calls init, create, and process in sequence. Returns 1 on success, 0 on failure. |
| `init_outer(outer)` | Zeroes out the `t_outer_array` struct before use. |
| `create_array(path, outer)` | First file pass: counts non-blank lines with `get_next_line`, then `calloc`s the pointer array with a NULL sentinel. |
| `process_map(path, outer)` | Second file pass: reads each line, skips blank lines, strips the trailing `\n`, and copies into pre-allocated slots with `ft_calloc` + `ft_memcpy`. Calls `drain_gnl` after the loop to flush GNL's static buffer. |
| `drain_gnl(fd, line)` | Frees and reads remaining lines from a file descriptor until GNL returns NULL, preventing static buffer leaks. |

### `parse_map_3d.c`
| Function | Description |
|----------|-------------|
| `parse_map_3d(outer_array, map)` | Counts rows, guards against a 0-row map, allocates `rows_array` and `colors`, then calls `fill_rows`. Sets `map->cols` from the first row's element count. |
| `split_rows(row_str, z_array, colors_row)` | Splits a space-separated string with `ft_split`. Allocates z and color arrays, then calls `fill_arrays` to populate them. |
| `parse_color(token)` | Looks for a comma in the token (e.g. `5,0xFF8800`). If found, passes the substring after the comma to `hex_to_dec`; otherwise returns `-1` (use default color). |
| `compute_scale(map, w)` | Guards against 0-dimension maps, computes a uniform integer scale so the projected map fits within the window, then sets `offset_x`/`offset_y` to center it. |

### `helpers.c`
| Function | Description |
|----------|-------------|
| `hex_to_dec(str)` | Converts a hex string (with or without `0x`/`0X` prefix) to an integer. Supports uppercase and lowercase digits. |
| `free_all(array)` | Iterates a NULL-terminated `char **`, frees each string, then frees the array pointer itself. |
| `free_map(map)` | For each row, frees `rows_array[i].array` and `colors[i]` with NULL guards, then frees the top-level `rows_array` and `colors` pointers. |
| `count_rows(outer_array)` | Returns the number of non-NULL entries in a NULL-terminated `char **`. |
| `fill_rows(outer_array, map)` | Calls `split_rows` for each row. Returns 0 and cleans up if any row fails to parse or has a mismatched column count. |

### `helpers2.c`
| Function | Description |
|----------|-------------|
| `fill_arrays(split_array, n, z_array, colors_row)` | Iterates over `n` tokens, calling `ft_atoi` for z values and `parse_color` for colors, populating the pre-allocated arrays. |

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
| `find_z_range(map, z_min, z_max)` | Scans the full map to set `*z_min` and `*z_max`, used by `compute_scale` to account for altitude range. |
| `key_handler(keycode, fdf)` | Receives all keypress events; maps ESC (keycode 65307) to `window_close_handler`. |
| `window_close_handler(fdf)` | Frees map memory, destroys the image, window, and display, frees the mlx pointer, then calls `exit(0)`. |
| `window_loop(w_data, fdf)` | Registers the keypress hook (event 2) and window-destroy hook (event 17), then enters `mlx_loop`. |

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
### AI Usage
Claude (Anthropic) was used during this project for the following tasks:
- Explaining the mathematics behind the isometric projection formula and validating the `compute_scale` offset calculation.
