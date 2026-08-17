# Circuit Connection Description

## Microcontroller

Arduino UNO is used as the central embedded controller.

## LCD 16x2

| LCD Pin | Arduino |
|---|---|
| RS | D12 |
| E | D11 |
| D4 | D5 |
| D5 | D4 |
| D6 | D3 |
| D7 | D2 |
| VSS | GND |
| VDD | 5V |

## Green LED

| Component | Arduino |
|---|---|
| Green LED Anode | D7 through resistor |
| Green LED Cathode | GND |

The green LED indicates the NORMAL software status.

## Red LED

| Component | Arduino |
|---|---|
| Red LED Anode | D8 through resistor |
| Red LED Cathode | GND |

The red LED indicates LOW or HIGH alert status.

## Buzzer

| Buzzer | Arduino |
|---|---|
| Positive | D9 |
| Negative | GND |

The buzzer generates a periodic alert when the simulated BPM is outside the configured demonstration range.

## Pulse Signal

The current Wokwi implementation generates a software pulse waveform inside the Arduino program.

This allows the BPM detection and alert algorithm to be tested without physical hardware.
