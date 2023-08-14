# Shitty Arcade

A shittily thrown together arcade that flops.

## How to build the _**Shitty-Arcade**_

```bash
cd /path/to/shitty-arcade
cmake -S . -B build
cmake --build build
```

... and games can now be found in `./build/shitty-arcade`

## Games included

- Snake
  - Sanke game but every time you grow a new wall gets added to the board
- Tic-Tac-Toe
  - Our invincible bot will block your every move (hopefully :P)
- Minesweeper
  - I copy-pasted my code from leetcode 529. Minesweeper
- Sudoku
  - Hover your cursor over the cell you wish to fill and press number keys 1-9

## Stuff

- **go watch tsoding**: <https://www.youtube.com/@TsodingDaily>
- raylib: <https://github.com/raysan5/raylib>
- modern cmake: <https://gitlab.com/CLIUtils/modern-cmake>
- effective modern cmake:
  <https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1>
- project setup #0:
  <https://stackoverflow.com/questions/62049311/how-do-i-set-up-this-folder-structure-in-cmake>
- project setup #1:
  <https://stackoverflow.com/questions/34438357/cmake-one-build-directory-for-multiple-projects>
- header-only library:
  <https://github.com/nothings/stb/blob/master/docs/stb_howto.txt>
