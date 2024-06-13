# Arduino BME680 Sensor Data Monitoring Project

This project involves using an Arduino with a BME680 sensor to collect environmental data and publish it via MQTT. The data is displayed in real-time on a website.

## Team Members
- **Patrik Perčinić**
- **Tin Cik**
- **Luka Petrečija**
- **Leo Brčina**

## Overview
The Arduino collects temperature, humidity, pressure, and air quality data using the BME680 sensor. Data is transmitted via MQTT to a server or cloud platform and visualized on a website.

## Components Used
- Arduino board
- BME680 sensor
- MQTT broker (e.g., Mosquitto)
- Web server (for hosting the website)
- Front-end technologies (HTML, CSS, JavaScript)

## Setup Instructions
1. **Hardware Setup:**
   - Connect the BME680 sensor to the Arduino board.

2. **Software Setup:**
   - Install necessary Arduino libraries for the BME680 sensor and MQTT.
   - Configure MQTT settings in the Arduino sketch.

3. **MQTT Broker:**
   - Set up an MQTT broker (local or cloud-based).

4. **Website:**
   - Develop a web interface to display real-time sensor data.
   - Use HTML, CSS, JavaScript, and MQTT.js for data integration.

5. **Usage:**
   - Access the website to monitor environmental data in real-time.

## Contributing
Contributions are welcome! Fork the repository, make your changes, and submit a pull request.

## License
This project is licensed under the [MIT License](LICENSE).
