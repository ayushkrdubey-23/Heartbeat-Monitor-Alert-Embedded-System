# ❤️ Heartbeat Monitor with Alert System
## ⚠️ Educational Prototype Disclaimer

This project is developed for educational and embedded-systems
learning purposes.

**It is NOT a medical diagnostic device.**

The current implementation uses a software-generated pulse signal
inside Wokwi rather than a physical pulse sensor. Hobby-grade
sensors and simulated readings may be approximate and must not be
used for medical decisions.

The LOW/NORMAL/HIGH thresholds used in this project are demonstration
values for testing the embedded alert logic and are not clinical
guidelines.

---

# 📌 Project Overview

The **Heartbeat Monitor with Alert System** is an embedded-systems
prototype designed to demonstrate how a microcontroller can process
heartbeat-related signal data, calculate Beats Per Minute (BPM), and
generate an alert when the calculated value moves outside a
configured demonstration range.

The project is completely implemented in software using the
**Wokwi electronics simulator** and an **Arduino UNO**.

The system demonstrates:

- Software-generated pulse signal
- Heartbeat peak detection
- Beat interval measurement
- BPM calculation
- Moving-average smoothing
- Threshold-based classification
- 16x2 LCD output
- Green LED status indication
- Red LED alert indication
- Buzzer alert
- Serial Monitor logging

---

# 🎯 Problem Statement

Continuous heart-rate monitoring concepts are widely used in
wearable electronics, fitness devices, rehabilitation systems,
and patient-monitoring technologies.

This project demonstrates the fundamental embedded-system workflow
behind such systems:

    Signal Acquisition
            ↓
    Signal Processing
            ↓
    Heartbeat Detection
            ↓
    BPM Calculation
            ↓
    Threshold Comparison
            ↓
    User Alert

The project focuses on understanding the embedded programming and
signal-processing concepts rather than providing medical diagnosis.

---

# 💡 Simple Explanation

The system creates a simulated heartbeat signal.

The Arduino monitors this signal and detects each heartbeat.

It measures the time between two detected beats.

The BPM is calculated using:

    BPM = 60000 / Time Between Beats (milliseconds)

The calculated BPM is then compared with educational demonstration
thresholds.

### LOW

    BPM < 60

The system displays:

    LOW - ALERT

The red LED and buzzer are activated.

### NORMAL

    60 <= BPM <= 100

The system displays:

    STATUS: NORMAL

The green LED is activated and the buzzer remains OFF.

### HIGH

    BPM > 100

The system displays:

    HIGH - ALERT

The red LED and buzzer are activated.

---

# 🔬 Technical Explanation

The Arduino UNO acts as the central embedded controller.

A software pulse generator produces a periodic pulse waveform.

The program samples the simulated signal at regular intervals and
checks whether the signal crosses a configured peak-detection
threshold.

When a valid heartbeat is detected:

1. The current timestamp is recorded.
2. The interval from the previous heartbeat is calculated.
3. BPM is calculated.
4. The BPM value is added to a small history buffer.
5. A moving average is calculated.
6. The averaged BPM is classified as LOW, NORMAL, or HIGH.
7. LCD, LED, and buzzer outputs are updated.

---

# 🏗️ System Architecture

```text
             SOFTWARE PULSE GENERATOR
                       │
                       ▼
               SIGNAL SAMPLING
                       │
                       ▼
              PEAK DETECTION
                       │
                       ▼
              BEAT INTERVAL
                 MEASUREMENT
                       │
                       ▼
                BPM CALCULATION
                       │
                       ▼
              MOVING AVERAGE
                       │
                       ▼
             THRESHOLD ENGINE
                       │
          ┌────────────┼────────────┐
          ▼            ▼            ▼
         LOW         NORMAL        HIGH
          │            │            │
          ▼            ▼            ▼
      RED LED       GREEN LED    RED LED
      BUZZER           OFF        BUZZER
          └────────────┼────────────┘
                       ▼
                  16x2 LCD
                       │
                       ▼
                 SERIAL MONITOR

🧩 Main Features
Arduino UNO embedded controller
Wokwi virtual simulation
Software-generated heartbeat signal
BPM calculation
Moving-average smoothing
Configurable demonstration thresholds
LOW alert
NORMAL indication
HIGH alert
16x2 LCD
Green LED
Red LED
Buzzer
Serial Monitor
Modular function-based code
Test documentation
GitHub-ready structure

🛠️ Technologies Used
Technology	Purpose
Arduino UNO	Embedded controller
Embedded C / Arduino C++	Firmware development
Wokwi	Virtual hardware simulation
LiquidCrystal	LCD interface
Serial Monitor	Debugging and monitoring
Git	Version control
GitHub	Project documentation and proof of work

🔌 Components
Arduino UNO

Acts as the main microcontroller.

Responsibilities:

Signal processing
Timing
BPM calculation
Threshold comparison
LCD control
LED control
Buzzer control
16x2 LCD

Displays:

BPM
Current status
Alert information

Example:

BPM: 75.0
STATUS: NORMAL
Green LED

Indicates the NORMAL demonstration state.

NORMAL → Green LED ON
Red LED

Indicates an alert state.

LOW  → Red LED ON
HIGH → Red LED ON
Buzzer

Produces a periodic alert when the calculated BPM is outside the
configured demonstration range.

🔗 Circuit Connections
LCD
LCD Pin	Arduino UNO
RS	D12
E	D11
D4	D5
D5	D4
D6	D3
D7	D2
VSS	GND
VDD	5V
Green LED
Connection	Arduino
Anode	D7 through resistor
Cathode	GND
Red LED
Connection	Arduino
Anode	D8 through resistor
Cathode	GND
Buzzer
Connection	Arduino
Positive	D9
Negative	GND

❤️ Pulse Signal Simulation

A physical pulse sensor is not required for the current software
implementation.

Instead, the Arduino generates a software pulse waveform.

The simulated BPM is controlled using:

int simulatedBPM = 75;

Example values:

45  → LOW
75  → NORMAL
120 → HIGH

The program converts the BPM value into a beat interval:

beatInterval = 60000UL / simulatedBPM;

🧮 BPM Calculation

The project uses:

BPM = 60000 / Beat Interval in milliseconds
Example 1
Beat interval = 1000 ms


BPM = 60000 / 1000


BPM = 60
Example 2
Beat interval = 750 ms


BPM = 60000 / 750


BPM = 80
Example 3
Beat interval = 600 ms


BPM = 60000 / 600


BPM = 100


📊 Moving Average

Heartbeat signals can fluctuate.

To demonstrate basic smoothing, the program stores up to five BPM
readings and calculates their average.

BPM History:


74
76
75
77
74


Average:


75.2 BPM

This helps demonstrate a basic digital signal-processing technique.


🚨 Alert Logic

The project uses educational demonstration thresholds.

BPM	Status	Green LED	Red LED	Buzzer
< 60	LOW	OFF	ON	ON
60–100	NORMAL	ON	OFF	OFF
> 100	HIGH	OFF	ON	ON

These values are software demonstration settings only and
should not be interpreted as clinical thresholds.

Actual heart-rate interpretation depends on many factors including
age, activity, health status, medication, and measurement context.


🖥️ LCD Output
Normal
+----------------+
|BPM: 75.0       |
|STATUS: NORMAL  |
+----------------+
Low Alert
+----------------+
|BPM: 45.0       |
|LOW - ALERT     |
+----------------+
High Alert
+----------------+
|BPM: 120.0      |
|HIGH - ALERT    |
+----------------+

🖥️ Serial Monitor

Example:

======================================
 HEARTBEAT MONITOR WITH ALERT SYSTEM
======================================
Platform: Arduino UNO
Simulation: Wokwi
Mode: Software Heartbeat Simulation
Simulated BPM: 75
Beat Interval: 800 ms


Educational Thresholds:
LOW: < 60.00
NORMAL: 60.00 - 100.00
HIGH: > 100.00


WARNING:
Educational prototype only.
Not a medical diagnostic device.
======================================


------------------------------
Heartbeat Count: 2
Instant BPM: 75.0
Average BPM: 75.0
Status: NORMAL
Alert: OFF
------------------------------


🧪 Testing

The project is tested using software-generated BPM values.

Test Cases
Test	Input	Expected
Startup	System ON	Initialization
Normal	75 BPM	NORMAL
Low	45 BPM	LOW + Alert
High	120 BPM	HIGH + Alert
BPM Test	1000 ms	60 BPM
BPM Test	750 ms	80 BPM
BPM Test	600 ms	100 BPM
Output Validation
Normal
Green LED → ON
Red LED   → OFF
Buzzer    → OFF
LCD       → NORMAL
Low
Green LED → OFF
Red LED   → ON
Buzzer    → ALERT
LCD       → LOW - ALERT
High
Green LED → OFF
Red LED   → ON
Buzzer    → ALERT
LCD       → HIGH - ALERT

Detailed test results are available in:

reports/test_results.md


▶️ How to Run
Option 1 — Wokwi Simulation

Open the project:

Wokwi Simulation

https://wokwi.com/projects/472615672214305793

Start the simulation.

The project uses an Arduino UNO and virtual electronic components.

Change Simulated BPM

Open the Arduino sketch and locate:

int simulatedBPM = 75;

Change it to:

int simulatedBPM = 45;

for LOW testing.

Or:

int simulatedBPM = 120;

for HIGH testing.

Run the simulation again.


💻 Local Arduino Development

If Arduino IDE is used for source inspection or future hardware
deployment:

Install Arduino IDE.
Open arduino_code/heartbeat_monitor.ino.
Select Arduino UNO.
Install/use the required LCD library.
Compile the program.
Open Serial Monitor at 9600 baud.

The current project itself is validated through Wokwi rather than
physical hardware.

📁 Project Structure
Heartbeat-Monitor-Alert-Embedded-System/
│
├── arduino_code/
│   └── heartbeat_monitor.ino
│
├── simulation/
│   ├── diagram.json
│   └── libraries.txt
│
├── circuit_diagram/
│   └── circuit_description.md
│
├── data/
│   └── sample_bpm_data.csv
│
├── outputs/
│   └── sample_serial_output.txt
│
├── screenshots/
│   ├── 01_normal_bpm.png
│   ├── 02_low_alert.png
│   ├── 03_high_alert.png
│   └── 04_wokwi_circuit.png
│
├── reports/
│   └── test_results.md
│
├── docs/
│   ├── architecture.md
│   └── project_notes.md
│
├── src/
│   └── README.md
│
├── README.md
└── .gitignore
📸 Screenshots

The repository will contain screenshots demonstrating:

Wokwi circuit
Normal BPM
Low BPM alert
High BPM alert
LCD output
Green LED state
Red LED state
Serial Monitor output
🏭 Industry Relevance

The concepts demonstrated in this project are relevant to:

wearable electronics
fitness monitoring
patient-monitoring concepts
rehabilitation technology
sports monitoring
IoT health-monitoring prototypes
embedded sensor systems

The project demonstrates several concepts commonly found in
real-time embedded monitoring systems:

Sensor/Input
     ↓
Sampling
     ↓
Signal Processing
     ↓
Decision Logic
     ↓
User Interface
     ↓
Alert System
🧠 Embedded Systems Concepts Demonstrated
Microcontroller

Arduino UNO performs the central processing.

GPIO

GPIO pins control:

LEDs
buzzer
LCD interface
Timing

millis() is used for non-blocking timing operations.

Signal Sampling

The simulated signal is sampled periodically.

Peak Detection

A threshold is used to identify heartbeat peaks.

BPM Calculation

The time between beats is converted into BPM.

Filtering

A moving average is used to reduce fluctuations.

Decision Logic

The BPM is classified into:

LOW
NORMAL
HIGH
Human-Machine Interface

LCD provides readable status information.

Alert Generation

LED and buzzer provide immediate software-defined alerts.

🔮 Future Improvements

The project can be extended with:

1. Physical Pulse Sensor

Replace the software-generated pulse waveform with a real
pulse sensor.

2. MAX30102

Use an optical heart-rate sensor for a more realistic sensor
interface.

3. OLED

Replace the 16x2 LCD with an I2C OLED display.

4. ESP32

Move the project to ESP32 for additional connectivity options.

5. Data Logging

Store BPM readings for later analysis.

6. Bluetooth

Send readings to a nearby application.

7. Wi-Fi Dashboard

Display simulated/collected readings on a web dashboard.

8. Better Signal Processing

Implement more advanced filtering and peak-detection algorithms.

9. Battery Operation

Develop a low-power embedded implementation.

10. Hardware Validation

Compare simulated results against a physical prototype.

⚠️ Limitations

The current project has several limitations:

It does not use a physical pulse sensor.
The heartbeat signal is software-generated.
The project has not been medically validated.
The demonstration thresholds are not clinical thresholds.
Noise conditions are simplified.
Real human pulse signals are more complex.
The prototype is intended for educational purposes.
🎓 Learning Outcomes

Through this project, I learned about:

Embedded C / Arduino programming
Microcontroller GPIO
Timing using millis()
Signal sampling
Peak detection
BPM calculation
Moving-average filtering
LCD interfacing
LED control
Buzzer control
Threshold-based decision systems
Virtual embedded-system simulation
Testing and validation
Git and GitHub project management

📈 Project Workflow
Project Planning
      ↓
System Architecture
      ↓
Wokwi Circuit
      ↓
Software Pulse Generation
      ↓
Heartbeat Detection
      ↓
BPM Calculation
      ↓
BPM Smoothing
      ↓
LCD Integration
      ↓
LED Integration
      ↓
Buzzer Integration
      ↓
Testing
      ↓
Documentation
      ↓
GitHub
🔗 https://github.com/ayushkrdubey-23/Heartbeat-Monitor-Alert-Embedded-System

Wokwi

Run the complete software simulation here:

https://wokwi.com/projects/472615672214305793

📌 Repository Goals

This repository is intended to demonstrate practical understanding
of embedded systems through a complete software-based project.

It focuses on:

implementation
testing
documentation
simulation
version control
engineering reasoning

rather than simply providing source code.

👨‍💻 Author

Ayush Kumar Dubey

Computer Science & Engineering Student

Interested in:

Embedded Systems
Programming
Software Development
Artificial Intelligence
Machine Learning
⭐ Acknowledgement

This project was developed as part of an Embedded Systems learning
project using Arduino and Wokwi virtual simulation.

📜 License

This project is intended for educational purposes.
