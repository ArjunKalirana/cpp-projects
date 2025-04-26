# Traffic Light Simulation in C++ 🚦

This project simulates a basic **Traffic Light System** using C++. The program demonstrates how traffic lights (Red, Yellow, and Green) function in sequence, and also plays corresponding musical notes for each light change using the `Beep()` function. This simulation is also a great example of how to use system commands to control the color of the terminal and use time delays for the traffic light cycle.

## Features ✨
- **Red Light**: The red light signals for a "STOP", followed by a beep sound.
- **Green Light**: The green light signals for "GO", accompanied by a beep.
- **Yellow Light**: The yellow light signals "WAIT", with a beep sound.
- **Countdown Timer**: Each light displays a countdown, giving a realistic traffic light effect.

## Prerequisites 🛠️
- **Operating System**: Windows (since the `Beep()` function and `system("Color")` are specific to Windows).
- **C++ Compiler**: Any C++ compiler that supports C++11 or higher.

## How to Run 🚀
1. Clone or download the repository.
2. Open the terminal or command prompt and navigate to the folder containing the `.cpp` file.
3. Compile the program using a C++ compiler (e.g., `g++ traffic_light.cpp -o traffic_light`).
4. Run the program (`./traffic_light` or `traffic_light.exe` on Windows).

## Code Overview

The traffic light simulation is implemented using the following functions:
1. **redLight()**: This function simulates the red light by setting the console color to red (system("Color 0C")), displaying a countdown, and playing a 523 Hz sound (C5 note) using the Beep() function.
2. **yellowLight()**: This function simulates the yellow light by changing the console color to yellow (system("Color 0E")), displaying a countdown, and playing a 659 Hz sound (E5 note).
3. **greenLight()**: This function simulates the green light by changing the console color to green (system("Color 0A")), displaying a countdown, and playing a 784 Hz sound (G5 note).

The main() function loops through the traffic light cycle a number of times (set to 3 cycles by default).

```bash
g++ traffic_light.cpp -o traffic_light
./traffic_light
