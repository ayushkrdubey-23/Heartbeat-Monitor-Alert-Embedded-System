# Heartbeat Monitor — Test Results

## Testing Environment

- Platform: Arduino UNO
- Simulator: Wokwi
- Sensor: Software-generated pulse signal
- Display: 16x2 LCD
- Alert: Buzzer + LEDs

## Test Objective

The objective of testing is to verify the heartbeat detection,
BPM calculation, threshold classification, display output,
LED indicators, and buzzer alert functionality.

## Test Results

| Test ID | Test | Expected Result | Result |
|---|---|---|---|
| TC01 | Startup | System initializes | PASS |
| TC02 | 75 BPM | NORMAL | PASS |
| TC03 | 45 BPM | LOW + Alert | PASS |
| TC04 | 120 BPM | HIGH + Alert | PASS |
| TC05 | 1000 ms | 60 BPM | PASS |
| TC06 | 750 ms | 80 BPM | PASS |
| TC07 | 600 ms | 100 BPM | PASS |
| TC08 | Normal LED | Green ON | PASS |
| TC09 | Low LED | Red ON | PASS |
| TC10 | High LED | Red ON | PASS |
| TC11 | Low Buzzer | Alert | PASS |
| TC12 | High Buzzer | Alert | PASS |
| TC13 | Normal Buzzer | OFF | PASS |
| TC14 | Normal LCD | Correct | PASS |
| TC15 | Low LCD | Correct | PASS |
| TC16 | High LCD | Correct | PASS |

## Conclusion

The software simulation successfully demonstrates:

- Pulse signal generation
- Heartbeat detection
- BPM calculation
- BPM averaging
- Threshold classification
- LCD output
- LED indication
- Buzzer alert generation

## Limitation

This project uses a software-generated pulse signal in Wokwi.
It does not validate the accuracy of a physical pulse sensor.

The prototype is educational and must not be used for medical
diagnosis or medical decision-making.