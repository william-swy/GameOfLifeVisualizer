# Conway's Game Of Life Visualizer
Desktop app to graphically visualize Conway's Game Of Life with user manipulable inputs

## Building the Source Code
1. Clone this repository into a folder
2. Make folders for the binaries that you want to build. If you want to build all of them (the GUI app, the console app and the unittests), make folders for each respective binary. If you only want to build one, just make the folder for that specific binary. Call these folders the `builddir`(s). The `CMakeLists.txt` scripts **do not** allow building in the **same directory as the source code**!
3. `cd` into the folder containing the `CMakeLists.txt` for the desired binary. If you want to make `x` number of binaries, repeat steps `3` to `5` `x` number of times.
4. Run `cmake . -B<buildir>` where `builddir` is the previously made folder for the respective binary.
5. `cd` into `buildir` and run `make`

## Notes On Dependencies
- `Catch2` is used as the unittest framework. Building the tests requires `Catch2`. This can be installed [here](https://github.com/catchorg/Catch2) or by using your package manager.
- `Qt` is used as the GUI framework. Building the app requires `Qt` libraries which can be found [here](https://www.qt.io/download) or by using your package manager