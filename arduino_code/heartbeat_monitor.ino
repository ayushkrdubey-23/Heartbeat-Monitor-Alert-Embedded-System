/*
  ============================================================
  HEARTBEAT MONITOR WITH ALERT SYSTEM
  ============================================================

  Platform:
  Arduino UNO

  Simulation:
  Wokwi

  Project Type:
  Educational Embedded Systems Prototype

  IMPORTANT:
  This project is NOT a medical diagnostic device.
  Simulated/hobby-grade readings are approximate and must
  NOT be used for medical decisions.

  Features:
  - Software-generated heartbeat signal
  - Heartbeat peak detection
  - BPM calculation
  - Moving-average smoothing
  - LOW / NORMAL / HIGH status
  - 16x2 LCD
  - Green LED
  - Red LED
  - Periodic buzzer alert
  - Serial Monitor logging
  ============================================================
*/

#include <LiquidCrystal.h>


// ============================================================
// 1. PIN CONFIGURATION
// ============================================================

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int GREEN_LED = 7;
const int RED_LED   = 8;
const int BUZZER    = 9;


// ============================================================
// 2. EDUCATIONAL THRESHOLDS
// ============================================================
//
// These values are only for software demonstration.
// They are NOT clinical thresholds.
//

const float LOW_THRESHOLD  = 60.0;
const float HIGH_THRESHOLD = 100.0;


// ============================================================
// 3. SIMULATION CONFIGURATION
// ============================================================

// Change this value for testing.
//
// 45  -> LOW
// 75  -> NORMAL
// 120 -> HIGH

int simulatedBPM = 120;


// ============================================================
// 4. SIMULATED SENSOR PARAMETERS
// ============================================================

const int BASELINE = 512;

const int PEAK_VALUE = 850;

const int PEAK_THRESHOLD = 700;


// Sampling interval
const unsigned long SAMPLE_INTERVAL = 20;


// Calculate beat interval automatically
unsigned long beatInterval;


// ============================================================
// 5. HEARTBEAT DETECTION PARAMETERS
// ============================================================

bool pulseDetected = false;


// Minimum allowed interval between valid beats.
// Used to reject unrealistically fast noise peaks.
//
// Educational signal-processing filter only.

const unsigned long MIN_BEAT_INTERVAL = 300;


// ============================================================
// 6. TIMING VARIABLES
// ============================================================

unsigned long lastSampleTime = 0;

unsigned long lastBeatTime = 0;

unsigned long currentBeatTime = 0;


// ============================================================
// 7. BPM VARIABLES
// ============================================================

float instantBPM = 0.0;

float averageBPM = 0.0;


// ============================================================
// 8. BPM MOVING AVERAGE
// ============================================================

const int BPM_HISTORY_SIZE = 5;

float bpmHistory[BPM_HISTORY_SIZE];

int historyIndex = 0;

int validBPMCount = 0;


// ============================================================
// 9. HEARTBEAT COUNTER
// ============================================================

unsigned long heartbeatCount = 0;


// ============================================================
// 10. HEART STATUS
// ============================================================

enum HeartStatus {

  STATUS_UNKNOWN,

  STATUS_LOW,

  STATUS_NORMAL,

  STATUS_HIGH
};


HeartStatus currentStatus = STATUS_UNKNOWN;


// ============================================================
// 11. BUZZER CONFIGURATION
// ============================================================

const unsigned long BUZZER_BEEP_DURATION = 200;

const unsigned long BUZZER_REPEAT_INTERVAL = 1000;

unsigned long lastBuzzerTime = 0;

bool buzzerState = false;


// ============================================================
// 12. SETUP
// ============================================================

void setup() {

  // ----------------------------------------
  // Serial communication
  // ----------------------------------------

  Serial.begin(9600);


  // ----------------------------------------
  // LCD initialization
  // ----------------------------------------

  lcd.begin(16, 2);

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("HEARTBEAT");

  lcd.setCursor(0, 1);

  lcd.print("MONITOR START");


  // ----------------------------------------
  // GPIO configuration
  // ----------------------------------------

  pinMode(GREEN_LED, OUTPUT);

  pinMode(RED_LED, OUTPUT);

  pinMode(BUZZER, OUTPUT);


  // ----------------------------------------
  // Initial output state
  // ----------------------------------------

  digitalWrite(GREEN_LED, LOW);

  digitalWrite(RED_LED, LOW);

  noTone(BUZZER);


  delay(1500);


  // ----------------------------------------
  // Calculate simulated beat interval
  // ----------------------------------------

  beatInterval = 60000UL / simulatedBPM;


  // ----------------------------------------
  // Clear BPM history
  // ----------------------------------------

  for (int i = 0; i < BPM_HISTORY_SIZE; i++) {

    bpmHistory[i] = 0.0;
  }


  // ----------------------------------------
  // Startup information
  // ----------------------------------------

  printStartupInformation();


  // ----------------------------------------
  // Ready screen
  // ----------------------------------------

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("System Ready");

  lcd.setCursor(0, 1);

  lcd.print("Monitoring...");

  delay(1000);

  lcd.clear();
}


// ============================================================
// 13. MAIN LOOP
// ============================================================

void loop() {

  unsigned long currentTime = millis();


  // ----------------------------------------
  // Periodic sampling
  // ----------------------------------------

  if (currentTime - lastSampleTime >=
      SAMPLE_INTERVAL) {


    lastSampleTime = currentTime;


    // --------------------------------------
    // Generate simulated sensor signal
    // --------------------------------------

    int signal =
      readPulseSignal(currentTime);


    // --------------------------------------
    // Detect heartbeat
    // --------------------------------------

    bool heartbeatFound =
      detectHeartbeat(signal, currentTime);


    // --------------------------------------
    // Process heartbeat
    // --------------------------------------

    if (heartbeatFound) {


      calculateBPM(currentTime);


      // BPM available?
      if (averageBPM > 0) {


        // Determine status
        currentStatus =
          determineStatus(averageBPM);


        // Update LCD
        updateDisplay();


        // Update LEDs and alert system
        updateAlert(currentTime);


        // Print results
        printMeasurement();
      }
    }


    // --------------------------------------
    // Maintain buzzer timing
    // --------------------------------------

    updateBuzzer(currentTime);
  }
}


// ============================================================
// 14. SOFTWARE PULSE SENSOR
// ============================================================

int readPulseSignal(
  unsigned long currentTime
) {

  unsigned long cyclePosition =
    currentTime % beatInterval;


  // Create simulated heartbeat peak
  if (cyclePosition < 80) {

    return PEAK_VALUE;

  }


  // Baseline
  return BASELINE;
}


// ============================================================
// 15. HEARTBEAT DETECTION
// ============================================================

bool detectHeartbeat(
  int signal,
  unsigned long currentTime
) {


  // ----------------------------------------
  // Threshold crossing
  // ----------------------------------------

  if (signal > PEAK_THRESHOLD &&
      !pulseDetected) {


    // --------------------------------------
    // Noise/refractory protection
    // --------------------------------------

    if (lastBeatTime == 0 ||
        currentTime - lastBeatTime >=
        MIN_BEAT_INTERVAL) {


      pulseDetected = true;

      heartbeatCount++;

      currentBeatTime = currentTime;


      return true;
    }
  }


  // ----------------------------------------
  // Signal returned below threshold
  // ----------------------------------------

  if (signal < PEAK_THRESHOLD) {

    pulseDetected = false;
  }


  return false;
}


// ============================================================
// 16. BPM CALCULATION
// ============================================================

void calculateBPM(
  unsigned long currentTime
) {


  // Need at least two beats
  if (lastBeatTime > 0) {


    // --------------------------------------
    // Time between beats
    // --------------------------------------

    unsigned long interval =
      currentTime - lastBeatTime;


    // --------------------------------------
    // BPM formula
    // --------------------------------------

    instantBPM =
      60000.0 / interval;


    // --------------------------------------
    // Store reading
    // --------------------------------------

    bpmHistory[historyIndex] =
      instantBPM;


    historyIndex++;


    if (historyIndex >=
        BPM_HISTORY_SIZE) {

      historyIndex = 0;
    }


    // --------------------------------------
    // Update valid reading count
    // --------------------------------------

    if (validBPMCount <
        BPM_HISTORY_SIZE) {

      validBPMCount++;
    }


    // --------------------------------------
    // Calculate moving average
    // --------------------------------------

    float total = 0.0;


    for (int i = 0;
         i < validBPMCount;
         i++) {

      total += bpmHistory[i];
    }


    averageBPM =
      total / validBPMCount;
  }


  // Save timestamp
  lastBeatTime = currentTime;
}


// ============================================================
// 17. STATUS DECISION
// ============================================================

HeartStatus determineStatus(
  float bpm
) {


  if (bpm < LOW_THRESHOLD) {

    return STATUS_LOW;
  }


  if (bpm > HIGH_THRESHOLD) {

    return STATUS_HIGH;
  }


  return STATUS_NORMAL;
}


// ============================================================
// 18. LCD DISPLAY
// ============================================================

void updateDisplay() {

  lcd.clear();


  // ----------------------------------------
  // First line
  // ----------------------------------------

  lcd.setCursor(0, 0);

  lcd.print("BPM: ");

  lcd.print(averageBPM, 1);


  // ----------------------------------------
  // Second line
  // ----------------------------------------

  lcd.setCursor(0, 1);


  switch (currentStatus) {


    case STATUS_LOW:

      lcd.print("LOW - ALERT");

      break;


    case STATUS_NORMAL:

      lcd.print("STATUS: NORMAL");

      break;


    case STATUS_HIGH:

      lcd.print("HIGH - ALERT");

      break;


    default:

      lcd.print("WAITING...");
  }
}


// ============================================================
// 19. ALERT OUTPUT CONTROL
// ============================================================

void updateAlert(
  unsigned long currentTime
) {


  // ----------------------------------------
  // NORMAL
  // ----------------------------------------

  if (currentStatus ==
      STATUS_NORMAL) {


    digitalWrite(GREEN_LED, HIGH);

    digitalWrite(RED_LED, LOW);

    noTone(BUZZER);

    buzzerState = false;

    return;
  }


  // ----------------------------------------
  // LOW or HIGH
  // ----------------------------------------

  digitalWrite(GREEN_LED, LOW);

  digitalWrite(RED_LED, HIGH);


  // Start periodic alert
  if (currentTime - lastBuzzerTime >=
      BUZZER_REPEAT_INTERVAL) {


    lastBuzzerTime = currentTime;

    buzzerState = true;

    tone(BUZZER, 1000);
  }
}


// ============================================================
// 20. BUZZER TIMING
// ============================================================

void updateBuzzer(
  unsigned long currentTime
) {


  // Normal state
  if (currentStatus ==
      STATUS_NORMAL) {


    noTone(BUZZER);

    buzzerState = false;

    return;
  }


  // Stop current beep
  if (buzzerState &&
      currentTime - lastBuzzerTime >=
      BUZZER_BEEP_DURATION) {


    noTone(BUZZER);

    buzzerState = false;
  }
}


// ============================================================
// 21. SERIAL MEASUREMENT OUTPUT
// ============================================================

void printMeasurement() {

  Serial.println();

  Serial.println("------------------------------");

  Serial.print("Heartbeat Count: ");

  Serial.println(heartbeatCount);


  Serial.print("Instant BPM: ");

  Serial.println(instantBPM, 1);


  Serial.print("Average BPM: ");

  Serial.println(averageBPM, 1);


  Serial.print("Status: ");


  switch (currentStatus) {


    case STATUS_LOW:

      Serial.println("LOW");

      Serial.println("Alert: ACTIVE");

      break;


    case STATUS_NORMAL:

      Serial.println("NORMAL");

      Serial.println("Alert: OFF");

      break;


    case STATUS_HIGH:

      Serial.println("HIGH");

      Serial.println("Alert: ACTIVE");

      break;


    default:

      Serial.println("UNKNOWN");
  }


  Serial.println("------------------------------");
}


// ============================================================
// 22. STARTUP INFORMATION
// ============================================================

void printStartupInformation() {

  Serial.println();

  Serial.println("======================================");

  Serial.println(" HEARTBEAT MONITOR WITH ALERT SYSTEM");

  Serial.println("======================================");

  Serial.println("Platform: Arduino UNO");

  Serial.println("Simulation: Wokwi");

  Serial.println("Mode: Software Heartbeat Simulation");


  Serial.print("Simulated BPM: ");

  Serial.println(simulatedBPM);


  Serial.print("Beat Interval: ");

  Serial.print(beatInterval);

  Serial.println(" ms");


  Serial.println();

  Serial.println("Educational Thresholds:");

  Serial.print("LOW: < ");

  Serial.println(LOW_THRESHOLD);


  Serial.print("NORMAL: ");

  Serial.print(LOW_THRESHOLD);

  Serial.print(" - ");

  Serial.println(HIGH_THRESHOLD);


  Serial.print("HIGH: > ");

  Serial.println(HIGH_THRESHOLD);


  Serial.println();

  Serial.println("WARNING:");

  Serial.println(
    "Educational prototype only."
  );

  Serial.println(
    "Not a medical diagnostic device."
  );

  Serial.println("======================================");

  Serial.println();
}