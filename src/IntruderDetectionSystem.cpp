/**
 * @file main.cpp
 * @brief Ultrasonic Intruder Detection System with Haptic Feedback
 * 
 * @details This program implements an intruder detection system using an ultrasonic
 * sensor (HC-SR04 or similar) to measure distance and trigger a buzzer/vibration motor
 * when an object is detected within a specified threshold. The system employs noise
 * reduction through distance averaging and hysteresis-based detection to prevent
 * false triggering.
 * 
 * @author [Akpan Mercy Ekerette]
 * @date September 2025
 * @version 1.0
 * 
 * @hardware
 * - ESP32/Arduino compatible microcontroller
 * - HC-SR04 Ultrasonic Distance Sensor
 * - Buzzer/Vibration Motor
 * 
 * @dependencies
 * - Arduino.h
 */

#include <Arduino.h>
// ============================================================================
// PIN DEFINITIONS
// ============================================================================

/**
 * @brief GPIO pin connected to the ultrasonic sensor's trigger pin
 * @details This pin sends a calculated pulse to initiate distance measurement
 */
const int trigPin = 5;

/**
 * @brief GPIO pin connected to the ultrasonic sensor's echo pin
 * @details This pin receives the reflected ultrasonic pulse for distance calculation
 */
const int echoPin = 18;
/**
 * @brief GPIO pin connected to the buzzer/vibration motor
 * @details Controls the haptic feedback device for intruder alerts
 */
const int buzzerPin = 17;

// ============================================================================
// CONSTANTS
// ============================================================================

/**
 * @brief Speed of sound in air at room temperature
 * @details Value in centimeters per microsecond (cm/µs)
 */
 #define SOUND_SPEED 0.034

/**
 * @brief Conversion factor from centimeters to inches
 */
 #define CM_TO_INCH 0.393701

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

/**
 * @brief Duration of the echo pulse in microseconds
 */
long duration;

/**
 * @brief Measured distance in centimeters
 */
float distanceCm;

/**
 * @brief Measured distance in inches
 */
float distanceInch;

/**
 * @brief Intruder detection state flag
 * @details Maintains the last known detection state to implement hysteresis
 * - true: Intruder currently detected
 * - false: No intruder detected
 */
bool intruder = false;

/**
 * @brief Measures distance using ultrasonic sensor with noise reduction
 * 
 * @details Performs multiple distance measurements and returns their average
 * to reduce sensor noise and improve accuracy. Each measurement cycle:
 * 1. Sends a 10µs trigger pulse
 * 2. Measures the echo pulse duration
 * 3. Applies a 30ms timeout (~5m max range)
 * 4. Averages 5 valid readings
 * 
 * @return float Average distance in centimeters (0 if no valid readings)
 * 
 * @note The function includes a 10ms delay between measurements to allow
 * the sensor to stabilize
 */

float getDistanceCm() {
  long sum = 0;
  for (int i = 0; i < 5; i++) {
    // Trigger pulse
    // Turns off or resets the trigPin of the sensor
    digitalWrite(trigPin, LOW);
    // Waits for a short while
    delayMicroseconds(2);
    // Alerts the trigPin of sensor to send signals.
    digitalWrite(trigPin, HIGH);
    // Sends signals for a longer while 
    delayMicroseconds(10);
    // Stops sending signals.
    digitalWrite(trigPin, LOW);

    // Measure echo
    // PulseIn sets echoPin to High( alerts it to listen to bounced off signals)
    // It records how long the signals were listened to then turns it low
    long d = pulseIn(echoPin, HIGH, 30000); // timeout 30ms (~5m max distance)
    if (d > 0) {
      // Repeat for i times in containing for loop to get an average distance.
      sum += d;
    }
    // Wait a short while for each iteration of sending waves.
    delay(10);
  }
  // Takes a stable average of the i iterations.
  long avg = sum / 5;
  return (avg * SOUND_SPEED) / 2;
}

/**
 * @brief System initialization routine
 * 
 * @details Configures hardware pins, initializes serial communication,
 * and sets the system to a safe initial state. Executed once at startup.
 * 
 * Serial Configuration:
 * - Baud rate: 115200
 * 
 * Pin Configuration:
 * - trigPin: OUTPUT (sensor trigger)
 * - echoPin: INPUT (sensor echo)
 * - buzzerPin: OUTPUT (haptic feedback, initially LOW)
 * 
 * @return void
 */
void setup() {
  Serial.begin(115200);
  //OUTPUT here denotes OUTPUT from the micro-controller
  //INPUT here denotes INPUT from the micro-controller
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  // System starts with the vibrating motor off
  digitalWrite(buzzerPin, LOW);
  Serial.println("System Ready...");
}

/**
 * @brief Main program execution loop
 * 
 * @details Continuously monitors distance and manages intruder detection with
 * hysteresis to prevent oscillation. The system operates as follows:
 * 
 * Detection Logic:
 * - Triggers alert when distance < 6cm (intruder detected)
 * - Clears alert when distance > 8cm (area clear)
 * - 2cm hysteresis gap prevents rapid state changes
 * 
 * Haptic Feedback:
 * - Buzzer/motor activates on detection
 * - Deactivates when intruder leaves detection zone
 * 
 * Update Rate: 2Hz (500ms delay between measurements)
 * 
 * @return void
 * 
 * @note The hysteresis implementation prevents false triggers caused by
 * objects near the detection boundary
 */
void loop() {
  // Get stable distance
  distanceCm = getDistanceCm();
  distanceInch = distanceCm * CM_TO_INCH;

  // Print results
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);

  // Intruder detection with hysteresis
  // If intruder was not present, 
  // and distance is now less than distance limit (6)
  // Intruder is now present and motor vibrates.
  if (!intruder && distanceCm > 0 && distanceCm < 6) {
    intruder = true;
    Serial.println("⚠ Intruder detected!");
    digitalWrite(buzzerPin, HIGH);
  }
  // If intruder remains at distance < 6cm
  // The condition wont check and vibrating pin keeps vibrating.
  // If intruder walks away (> 8cm).
  // Vibrator stops vibrating.
  else if (intruder && distanceCm > 8) {  
    intruder = false;
    Serial.println("Area clear");
    digitalWrite(buzzerPin, LOW);
  }
  // Only runs this loop twice per second to reduce sensor checks.
  delay(500); // half a second between checks
}