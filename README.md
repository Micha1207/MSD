# MSD
Simple system monitor for GNU/Linux distributions.
Licensed under GNU GPL, version 3 (full license in LICENSE file).

---

## Getting started
This project is written in **C with GNU extensions**.

### Features
- Colorful Ncurses interface
- Real-time system monitoring (every one second)
- Bars showing percentage of RAM's and CPU's usage

---

### Requirements
Make sure to have `gcc`, `make` and `git` programs and Ncurses development library installed on your system:

Debian/Ubuntu/Mint: `apt install gcc make git ncurses-dev`

Fedora: `dnf install gcc make git ncurses-devel`

NOTE: Make sure to install packages as root, with `sudo`.

---

### Controls
- Press q or Q to exit

1. **Download sources**
   Clone project's repo with `git`:
   ```bash
   git clone https://github.com/Micha1207/MSD.git
   cd MSD
   ```

   Or download ZIP file directly from [project's GitHub page](https://github.com/Micha1207/MSD) and extract it.

2. **Compilation**:
   To compile this project, run `make` in project directory.

3. **Usage**:
   - To run directly: `./msd`
   - To install system-wide: `make install`. Make sure, to run as root.
   - Clean: `make clean` removes object files and binary.
