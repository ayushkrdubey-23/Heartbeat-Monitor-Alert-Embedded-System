# System Architecture

## Overall Flow

Software Pulse Generator
        ↓
Pulse Signal Sampling
        ↓
Heartbeat Peak Detection
        ↓
Beat Interval Measurement
        ↓
BPM Calculation
        ↓
Moving Average
        ↓
Threshold Comparison
        ↓
Status Classification
        ↓
LCD + LED + Buzzer

## Processing States

### LOW

BPM < configured low threshold

Output:
- LCD: LOW - ALERT
- Red LED: ON
- Green LED: OFF
- Buzzer: Periodic alert

### NORMAL

BPM within configured demonstration range

Output:
- LCD: STATUS: NORMAL
- Green LED: ON
- Red LED: OFF
- Buzzer: OFF

### HIGH

BPM > configured high threshold

Output:
- LCD: HIGH - ALERT
- Red LED: ON
- Green LED: OFF
- Buzzer: Periodic alert

## BPM Formula

BPM = 60000 / Beat Interval in milliseconds

Example:

Beat interval = 750 ms

BPM = 60000 / 750

BPM = 80