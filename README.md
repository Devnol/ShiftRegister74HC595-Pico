# ShiftRegister 74HC595 Raspberry Pi Pico/RP2040 Library

This library is a port of the [Arduino ShiftRegister 74HC595 Library by Timo Denk](https://github.com/Simsso/ShiftRegister74HC595), all functions are a 1:1 port of the original apart from the class instantiator due to the Pico's implementation of SPI.

This library simplifies the usage of shift registers. For instance, it allows to set pins of the shift register just like normal pico pins: 
```c++
sr.set(1, 1); //set pin 1 to value 1 (ON)
```
## Usage
For implementation details on how to use the library see the example sketch found in this repository at [/example/example.cpp](example/example.cpp).

It is recommended that you add the library as a git submodule in your project using 
```
git submodule add https://github.com/Devnol/ShiftRegister74HC595-Pico
```
in your project folder.

If you're not using git, you can simply clone the project inside your current project using 
```
git clone https://github.com/Devnol/ShiftRegister74HC595-Pico
```
or download the latest version from github as a zip file.

To integrate it into your project, open your project's CMakeLists.txt and add the following lines:

(after `pico_sdk_init()`):
```
add_subdirectory(ShiftRegister74HC595)

include_directories(ShiftRegister74HC595/src)
```
also add `ShiftRegister74HC595` in your `target_link_libraries()`

## Wiring

An example wiring diagram is available at [/example/example_schematic.png](example/example_schematic.png) or as a fritzing sketch at
[/example/example_schematic.fzz](example/example_schematic.fzz)

## Building Standalone (for development or testing the example)

Building the library requires the pico-sdk folder to be available as the `PICO_SDK_PATH` environment variable. CMake is also required for building.

### Building with Visual Studio Code
To build the project and examples with VScode, open the code workspace and modify the PICO_SDK_PATH variable in [.vscode/settings.json](.vscode/settings.json). Make sure you have the CMake Tools extension installed, then run `CMake: Configure`, choose arm-none-eabi and `CMake: Build` to compile the library and example. The example will be found under the [build/SR_example](./build/SR_example) folder in various formats.

### Building manually
To manually build the project and examples using the command line, create a Build subfolder and move into it:
(examples are for Linux/macOS)
```
mkdir Build
cd Build
```
Then, run cmake in the current folder using the parent folder CMakeLists as the configuration file:
```
cmake ../
```
Finally, run `make` from within the build folder.

## Questions/Issues
If you have a problem, bug or question do not hesitate to [open an issue on this GitHub repository](https://github.com/Devnol/ShiftRegister74HC595-Pico/issues)