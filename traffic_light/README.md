🚦 Traffic Light Simulation (C++)
📋 Project Overview
This project simulates a traffic light system using the console in C++. The simulation cycles through three basic traffic light states: Red, Yellow, and Green, with corresponding beeping sounds for each state. The system operates for a user-defined number of cycles.

The simulation includes:

Red Light: Beeps at a frequency of 523 Hz (C5 note) for 5 seconds.

Yellow Light: Beeps at a frequency of 659 Hz (E5 note) for 3 seconds.

Green Light: Beeps at a frequency of 784 Hz (G5 note) for 4 seconds.

The project provides visual feedback in the terminal and plays different tones for each light, making it both informative and engaging.

⚙️ Technologies Used
C++ for core logic

Windows.h for Beep() and console color manipulation

Console for text output and visual feedback

💻 How to Run the Project
Prerequisites:
A system running Windows (since windows.h is used for color manipulation and beeping functionality).

C++ Compiler (e.g., GCC or MSVC).

Steps:
Clone/Download the Repository:

If you haven't already, clone or download the project to your local machine.

Compile the Program:

Open a terminal/command prompt in the project directory.

Run the following command to compile the project:

Copy
Edit
g++ -o traffic_light_simulation traffic_light_simulation.cpp
Run the Program:

After compilation, execute the program by running the command:

bash
Copy
Edit
./traffic_light_simulation
Observe the Traffic Light Simulation:

The simulation will run for 3 cycles by default, displaying the current state of the traffic light and playing corresponding beeping sounds.

The colors of the console will change based on the light's state, and the remaining time for each light is shown in seconds.

🛠 Features
Red Light (STOP): Beep at 523 Hz (C5), lasts for 5 seconds.

Yellow Light (WAIT): Beep at 659 Hz (E5), lasts for 3 seconds.

Green Light (GO): Beep at 784 Hz (G5), lasts for 4 seconds.

Console Color Changing: The background color changes to represent the active traffic light color:

Red: Red color.

Yellow: Yellow color.

Green: Green color.

🚀 Enhancements for Future
Variable Cycles: Allow users to input the number of cycles for the simulation.

Customizable Timings: Let users adjust the time duration for each light.

Real-Time Simulation: Integrate with actual traffic light systems using sensors or real-time data.

Web or GUI Version: Create a web-based or graphical interface version of the traffic light system for better visualization.

📄 Source Code Explanation
Functions:
redLight(): Simulates the red light (STOP) phase, plays a 523 Hz beep for 5 seconds.

greenLight(): Simulates the green light (GO) phase, plays a 784 Hz beep for 4 seconds.

yellowLight(): Simulates the yellow light (WAIT) phase, plays a 659 Hz beep for 3 seconds.

Main Logic:
The program runs for a defined number of cycles (cycles = 3 by default).

For each cycle, the sequence of Red → Yellow → Green is executed, with corresponding beeps and time remaining displayed in the console.

🤝 Contributing
If you have any suggestions, improvements, or bug fixes, feel free to open an Issue or create a Pull Request. Contributions are welcome!

📄 License
This project is open source and available under the MIT License.
