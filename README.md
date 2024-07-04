# crypto_dashboard_lilygo
A Lilygo Crypto Dashboard

Arduino Crypto Monitor
This project implements a cryptocurrency monitoring system using Arduino, TFT display, and WiFi connectivity. It fetches real-time data from the Gate.io API and displays it on the screen in a user-friendly manner. The system supports dynamic updating of cryptocurrency pairs via a web interface.

Features
Displays real-time prices and percentage changes for selected cryptocurrency pairs.
Supports connectivity to multiple WiFi networks for robust operation.
Provides a web interface for users to dynamically update cryptocurrency pairs.
Includes splash screen functionality at startup to display essential information.
Components Used
Arduino board: ESP32 or compatible boards
TFT Display: TFT_eSPI library used for display functionalities
WiFi Module: WiFi.h library for network connectivity
Web Server: ESPAsyncWebServer library for handling web interface
Setup Instructions
Hardware Setup: Connect the TFT display and ensure proper wiring with the Arduino board.

Software Dependencies: Install necessary libraries using Arduino Library Manager:

TFT_eSPI
Arduino_JSON
ESPAsyncWebServer
NTPClient
WiFi
Configuration:

Update pin_config.h with your pin mappings if required.
Modify ssidList and passwordList arrays with your WiFi credentials.
Upload Code: Upload the sketch to your Arduino board using the Arduino IDE or compatible software.

Access: Once deployed, access the monitoring interface via the IP address displayed on the TFT screen.

Usage
Upon startup, the system connects to available WiFi networks.
The TFT screen displays real-time cryptocurrency data in a rotating fashion across three screens.
Users can modify the displayed cryptocurrency pairs via the web interface accessible through the IP address displayed on the screen.
Contributing
Contributions are welcome! Feel free to fork the repository, make your changes, and submit a pull request.

License
This project is licensed under the MIT License - see the LICENSE file for details.
