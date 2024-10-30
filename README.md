# NodeMCU Flight Management System

## Overview

This project implements a Flight Management System (FMS) using a NodeMCU board (ESP8266). The system allows users to load and manage flight plans, including departure and destination information and multiple waypoints, through a simple web interface.

## Features

- Connects to a Wi-Fi network.
- Loads and saves flight plans (departure, destination, and up to 5 waypoints).
- Displays the current flight plan on a web interface.
- Web form to update flight plan details.

## Requirements

### Hardware

- NodeMCU (ESP8266) development board.

### Software

- Arduino IDE with ESP8266 board package installed.
- Libraries:
  - `ESP8266WiFi`
  - `ESP8266WebServer`
  - `EEPROM`

## Setup Instructions

1. **Install Arduino IDE**:
   - Download and install the [Arduino IDE](https://www.arduino.cc/en/software).

2. **Install ESP8266 Board Package**:
   - Open the Arduino IDE.
   - Go to `File` > `Preferences`.
   - In the "Additional Board Manager URLs" field, add:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Go to `Tools` > `Board` > `Board Manager`, search for "ESP8266", and install the package.

3. **Clone or Download the Repository**:
   - Clone this repository or download it as a ZIP file and extract it.

4. **Open the Code**:
   - Open the provided `.ino` file in the Arduino IDE.

5. **Configure Wi-Fi Credentials**:
   - In the code, replace `your_SSID` and `your_PASSWORD` with your actual Wi-Fi credentials.

6. **Upload the Code**:
   - Connect your NodeMCU to your computer.
   - Select the appropriate board and port in the Arduino IDE (`Tools` > `Board` > `NodeMCU 1.0 (ESP-12E Module)` and `Tools` > `Port`).
   - Click the upload button.

7. **Access the Web Interface**:
   - Open the Serial Monitor (`Tools` > `Serial Monitor`) to find the IP address assigned to your NodeMCU.
   - Enter this IP address in a web browser to access the Flight Management System.

## Usage

- The web interface displays the current flight plan (departure, destination, and waypoints).
- Use the form provided to input and update the flight plan details.
- The system saves the flight plan in EEPROM, making it persistent across power cycles.

## Customization

- To change the flight plan logic or data handling, modify the structure and functions related to `FlightPlan` in the code.
- You can increase the number of waypoints by adjusting the `waypoints` array size in the `FlightPlan` struct.

## Future Enhancements

- **Navigation Features**: Implement waypoint navigation and tracking.
- **User Authentication**: Secure the web interface with user authentication.
- **Multiple Flight Plans**: Allow management of multiple flight plans.
- **Sensor Integration**: Integrate with GPS or other sensors for real-time flight data.

## License

This project is licensed under the MIT License. Feel free to modify and use the code for your projects.
