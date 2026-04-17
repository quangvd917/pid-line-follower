// Motor pins
#define ENA 9
#define IN1 8
#define IN2 7
#define ENB 10
#define IN3 12
#define IN4 13

// Sensor pins
#define S1 2
#define S2 3
#define S3 4
#define S4 5
#define S5 6

int baseSpeed = 65;
int minSpeed = 0;
int maxSpeed = 255;

float Kp = 5.4;
float Ki = 0.001;
float Kd = 0.99;

float integralLimit = 30.0;

float lastError = 0;
float integral = 0;

unsigned long lastTime = 0;
unsigned long samplingRate = 50; // ms

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(5000);
  lastTime = millis();
}

float getError() {
  int activeCount = 0;
  float weightedSum = 0;

  if (digitalRead(S5) == LOW) { weightedSum += -7; activeCount++; }
  if (digitalRead(S4) == LOW) { weightedSum += -3; activeCount++; }
  if (digitalRead(S3) == LOW) { weightedSum +=  0; activeCount++; }
  if (digitalRead(S2) == LOW) { weightedSum +=  3; activeCount++; }
  if (digitalRead(S1) == LOW) { weightedSum +=  7; activeCount++; }

  return (activeCount > 0) ? (weightedSum / activeCount) : lastError;
}

float PID(float error, float dt) {
  integral += error * dt;
  integral = constrain(integral, -integralLimit, integralLimit);
  float derivative = (error - lastError) / dt;

  return (Kp * error) + (Ki * integral) + (Kd * derivative);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastTime < samplingRate) {
    return;
  }

  float dt = (currentTime - lastTime) / 1000.0;
  float error = getError();
  float correction = PID(error, dt);

  int maxSteeringVal = maxSpeed - baseSpeed;
  int steeringVal = constrain(round(correction), -maxSteeringVal, maxSteeringVal);

  int leftSpeed = constrain(baseSpeed + steeringVal, minSpeed, maxSpeed);
  int rightSpeed = constrain(baseSpeed - steeringVal, minSpeed, maxSpeed);

  moveForward(leftSpeed, rightSpeed);

  lastError = error;
  lastTime = currentTime;
}

void moveForward(int leftSpeed, int rightSpeed) {
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
