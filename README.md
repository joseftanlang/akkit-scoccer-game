# AkKit Soccer Game (STM32L151)

A small embedded soccer game built on the Ak Base Kit (STM32L series). This repository contains firmware sources, bootloader components, board resources, and build artifacts used to develop and flash the game onto supported Ak Base Kit hardware.


---

**Table of contents**

- [Project overview](#project-overview)
- [Quick start](#quick-start)
- [Prerequisites](#prerequisites)
- [Build instructions](#build-instructions)
- [Flashing and running](#flashing-and-running)
- [Directory layout](#directory-layout)
- [Hardware](#hardware)
- [Software](#software)
- [Replicating this project](#replicating-this-project)
- [Code development](#code-development)
- [Development workflow](#development-workflow)
- [Contributing](#contributing)
- [Troubleshooting](#troubleshooting)
- [Security](#security)
- [License](#license)
- [Contact](#contact)

---

## Project overview

This repository implements a simple soccer game that runs on Ak Base Kit hardware (STM32L microcontroller). The game includes player, keeper, striker, goal post, and ball logic, along with display drivers and input handling. The codebase combines application-level game logic (under `application/`) with board/bootloader resources (`boot/`, `hardware/`) and reusable libraries.

The project is intended as a teaching/demo project for embedded game development on constrained microcontrollers.

## Quick start

1. Install toolchain and prerequisites (see Prerequisites).
2. Build the application: `make` in the appropriate `Makefile` directory (see Build instructions).
3. Flash the resulting binary to your board using the recommended programmer.

See the Build and Flash sections below for exact commands and notes.

## Prerequisites

- A Linux development host (this repo was developed on Linux; adjust commands for macOS/Windows).
- ARM GCC toolchain (arm-none-eabi-gcc, arm-none-eabi-ld, etc.).
- `make` and GNU build tools.
- OpenOCD or a compatible flasher tool for STM32L series, or a vendor tool that supports your board.
- Optional: `gdb-multiarch` for debugging via `stm32l_init.gdb` and OpenOCD.

Install common packages on Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential make git gcc-arm-none-eabi openocd gdb-multiarch
```

Adjust package names per your distribution.

## Build instructions

The project contains multiple `Makefile`s for different build targets. Typical targets:

- Build the main application: `cd application && make` (or `cd application/build_soccer_game && make` depending on configuration).
- Build the bootloader: `cd boot && make`.

Example:

```bash
cd application
make clean
make all
# built artifacts will be in application/build_soccer_game/ or similar
```

Notes:
- The repository keeps prebuilt artifacts under `application/build_soccer_game/` for convenience. When making changes, rebuild to regenerate `.d` and `.su` files.
- If you have multiple toolchain versions, ensure `arm-none-eabi-gcc` in your PATH matches the expected release.

## Flashing and running

- Use OpenOCD, ST-Link, or your preferred programmer to flash the generated `.bin` or `.elf` file.
- Example using OpenOCD + GDB:

```bash
openocd -f interface/stlink.cfg -f target/stm32l1x.cfg &
arm-none-eabi-gdb application/build_soccer_game/app.elf
(gdb) target remote :3333
(gdb) monitor reset halt
(gdb) load
(gdb) monitor reset init
(gdb) continue
```

Replace `app.elf` path with your built ELF file.

## Directory layout

Top-level layout (high-level overview):

- `application/` — Main game firmware source, build artifacts, and Makefiles.
	- `build_soccer_game/` — prebuilt objects and build outputs.
- `boot/` — Bootloader sources and build artefacts.
- `hardware/` — Board assembly resources, schematics, manufacturing files.
- `resources/` — Bitmap and image assets used by the game.

Files of interest:

- `application/Makefile` — primary build entry for the application.
- `application/stm32l_init.gdb` — GDB init script for debugging.
- `boot/stm32l_init.gdb` — GDB init for bootloader context.

## Development workflow

1. Create a feature branch for your change: `git checkout -b feat/description`.
2. Implement changes to sources under `application/sources/` or other relevant folders.
3. Rebuild: run `make` in the relevant directory.
4. Test on hardware and iterate.
5. Open a pull request with a clear description and test notes.

Code style:
- Keep C file formatting consistent with the existing style in the repo.
- Preserve existing function naming and architecture-specific conventions.

## Contributing

Contributions are welcome. Please follow these guidelines:

- Open issues to discuss significant changes before implementing them.
- Keep commits focused and descriptive.
- Include hardware testing information in PRs.

If you want help setting up a dev environment or debugging a build failure, open an issue with your system details and build log.

## Troubleshooting

- Build failures: check that `arm-none-eabi-gcc` is installed and in PATH. Inspect `config` sections inside `Makefile` for expected toolchain prefixes.
- Flashing issues: ensure your board is powered and connected, and that no other process (e.g., ST-Link Server) holds the programmer.
- Runtime problems: use GDB to attach and inspect logs. Hardware peripherals may require specific power sequencing.

## Hardware

This section explains the physical hardware needed to replicate the project.

- Target board: Ak Base Kit with an STM32L-series MCU (verify exact MCU variant on your board)
- Optional components: OLED display (Adafruit-compatible), buttons, buzzer, LEDs, connectors for power and programming
- Bill of Materials (example):
	- 1 × Ak Base Kit board (STM32L)
	- 1 × 128x64 OLED display (SPI or I2C depending on wiring)
	- 3–5 × tactile push buttons
	- 1 × piezo buzzer
	- Wires / header pins, power supply

Wiring / Pinout

- See `hardware/` for board-specific diagrams and assembly notes. Typical wiring:
	- Display: connect MOSI/MISO/SCLK/CS/D/C/RST to the MCU SPI pins (or I2C SDA/SCL for I2C displays)
	- Buttons: connected to GPIO with pull-up/down as implemented in `application/io_cfg` or `application/sources`
	- Buzzer: GPIO with appropriate transistor driver if needed

If you add or change wiring, update the `hardware/` folder with schematics and a short README describing pin mapping.

## Software

This section details software dependencies and recommended versions.

- Toolchain: `arm-none-eabi-gcc` (ARM Embedded Toolchain) — recommended recent stable release
- Build tools: `make`, `binutils`, `openocd` for flashing/debugging
- Debugging: `gdb-multiarch` or `arm-none-eabi-gdb` with OpenOCD
- Optional tooling: `stlink` utilities if using ST-Link programmer

Example install on Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y gcc-arm-none-eabi binutils-arm-none-eabi make openocd gdb-multiarch
```

## Replicating this project (step-by-step)

1. Obtain hardware matching the Ak Base Kit or compatible STM32L board.
2. Assemble peripherals (display, buttons, buzzer) following the wiring notes above or in `hardware/`.
3. Install software dependencies listed in the Software section.
4. Build the firmware:

```bash
cd application
make clean
make all
```

5. Flash the firmware using OpenOCD or your preferred flasher (example):

```bash
openocd -f interface/stlink.cfg -f target/stm32l1x.cfg &
arm-none-eabi-gdb application/build_soccer_game/app.elf
(gdb) target remote :3333
(gdb) load
(gdb) monitor reset init
(gdb) continue
```

6. Verify operation: power the board and observe the display and inputs. Use `gdb` to step through code if necessary.

Notes on reproducing images/assets

- Assets are stored in `resources/bitmap` and `resources/image`. If you change or optimize assets, ensure they are converted to the formats expected by the display driver (see `application/app_data` and `Adafruit_oled_drv` files).

## Code development

Code layout

- `application/sources/` — C source files for game logic and drivers
- `application/build_soccer_game/` — build outputs and prebuilt objects
- `boot/` — bootloader sources
- `hardware/` — board and manufacturing resources

Guidance for contributors working on code

- Static analysis: run your C linter/formatter that matches the repository conventions.
- Adding features: implement changes in `application/sources/`, update `Makefile` or build scripts if new files are required, and include brief hardware testing notes in your PR.
- Unit testing: full unit tests are difficult on bare-metal firmware; prefer small host-side test utilities for algorithms, and hardware-in-the-loop testing for drivers.

Debugging tips

- Use `stm32l_init.gdb` files in `application/` and `boot/` to set breakpoints and initialize the debug session.
- Add serial or GPIO-based logging where practical. Keep logs minimal to avoid timing perturbations.

---

_If you'd like, I can also add a short hardware README under `hardware/` with a BOM, annotated photos, and a simple wiring diagram._

### Code samples (C)

Below are short, hardware-agnostic C snippets to help contributors get started. These intentionally avoid pin mappings and focus on the software structure and APIs you can adapt to your board layer.

- Minimal `main.c` skeleton:

```c
// main.c
#include "board.h"    // platform-specific init wrappers
#include "game.h"     // game logic API

int main(void) {
	board_init();      // clocks, power, low-level init
	display_init();    // initialize display driver
	input_init();      // initialize buttons/inputs
	buzzer_init();     // optional

	game_init();       // set up game state

	while (1) {
		game_update(); // update state (logic, physics)
		game_render(); // draw to display
	}

	return 0;
}
```

- Display helper example (Adafruit-like API):

```c
// ui.c
void render_score(uint8_t home, uint8_t away) {
	display_clear();
	display_setCursor(0, 0);
	display_printf("Home: %u  Away: %u", home, away);
	display_update(); // pushes buffer to OLED
}
```

- Input abstraction example:

```c
// input.c
bool is_button_pressed(button_id_t id) {
	return input_read(id) == BUTTON_PRESSED; // input_read is platform-implemented
}

void poll_inputs(void) {
	if (is_button_pressed(BTN_LEFT))  player_move_left();
	if (is_button_pressed(BTN_RIGHT)) player_move_right();
	if (is_button_pressed(BTN_ACTION)) player_kick();
}
```

- Fixed-timestep game update loop:

```c
#define TICK_MS 16 // ~60Hz

void game_update(void) {
	static uint32_t last = 0;
	uint32_t now = millis(); // platform-provided ms timer
	if (now - last < TICK_MS) return;
	last += TICK_MS;

	poll_inputs();
	physics_step();
	ai_step();
}
```

- Simple debug logging (non-blocking):

```c
void log_event(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	// format into a small buffer and push to a ring buffer consumed by a background task
	vlog_to_ringbuf(fmt, ap);
	va_end(ap);
}
```

These examples are intentionally concise — if you'd like, I can add matching header files under `application/sources/` (e.g., `board.h`, `display.h`, `input.h`) with minimal implementations you can adapt to your board.

## Security

See `SECURITY.md` for security policy, responsible disclosure, and guidelines.

## License

This project includes a `LICENSE` file at the repository root. Review it to confirm reuse and redistribution terms.

## Contact

For questions or issues, open an issue in this repository or contact the maintainer via the project issue tracker.

---

_Generated on May 21, 2026 — README expanded with structured instructions and references._