// 4 DC Motors, 4 Wheels
// 2 L298N Motor Drivers
// ESP32 Microcontroller

#include <Bluepad32.h>
#define LEFT_CALIBRATION 0.60

// Front Left
#define IN1_KD 25
#define IN2_KD 26
#define EN_KD  33

// Rear Left
#define IN1_KB 16
#define IN2_KB 17
#define EN_KB  4

// Front Right
#define IN1_KaD 27
#define IN2_KaD 14
#define EN_KaD  12

// Rear Right
#define IN1_KaB 5
#define IN2_KaB 18
#define EN_KaB  19

GamepadPtr gp;
int ly, rx, r1;
int left_pwm, right_pwm;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);

  pinMode(IN1_KD, OUTPUT); pinMode(IN2_KD, OUTPUT); pinMode(EN_KD, OUTPUT);
  pinMode(IN1_KB, OUTPUT); pinMode(IN2_KB, OUTPUT); pinMode(EN_KB, OUTPUT);
  pinMode(IN1_KaD, OUTPUT); pinMode(IN2_KaD, OUTPUT); pinMode(EN_KaD, OUTPUT);
  pinMode(IN1_KaB, OUTPUT); pinMode(IN2_KaB, OUTPUT); pinMode(EN_KaB, OUTPUT);

  BP32.setup(&onConnect, &onDisconnect);
}

void onConnect(GamepadPtr gamepad) {
  gp = gamepad;
  digitalWrite(2, HIGH);
}

void onDisconnect(GamepadPtr gamepad) {
  if (gp == gamepad) gp = nullptr;
  digitalWrite(2, LOW);
  stopMotors();
}

void loop() {
  BP32.update();

  if (!gp || !gp->isConnected()) {
    digitalWrite(2, LOW);
    stopMotors();
    return;
  }

  int ly = gp->axisY();
  int rx = gp->axisRX();
  int r1 = gp->r1();

  int maxSpeed = (r1 == 1) ? 255 : 170;

  // Spinning Mode
  if (abs(ly) < 30 && abs(rx) > 15) {
    int pwm = map(abs(rx), 0, 128, 0, maxSpeed);
    if (rx > 0) {
      left_motor(-pwm);
      right_motor(pwm);
    } else {
      left_motor(pwm);
      right_motor(-pwm);
    }

    return;
  }

  // Turn Left/Right
  if (abs(ly) > 50 && abs(ly) < 100 && abs(rx) > 30) {
    int ly_fix = -ly;
    int baseSpeed = map(abs(ly_fix), 0, 128, 0, maxSpeed);
    int turnAdjust = map(abs(rx), 0, 128, 0, baseSpeed / 2);

    // if (rx > 0) {
    //   // Belok KANAN => kiri cepat, kanan lambat
    //   left_pwm = baseSpeed - turnAdjust;
    //   right_pwm = baseSpeed;
    // } else {
    //   // Belok KIRI => kanan cepat, kiri lambat
    //   left_pwm = baseSpeed;
    //   right_pwm = baseSpeed - turnAdjust;
    // }
    
    if (rx > 0) {
      // Turn Right => fast left, slow right
      left_pwm = baseSpeed;
      right_pwm = baseSpeed - turnAdjust;
    } else {
      // Turn Left => fast right, slow left
      left_pwm = baseSpeed - turnAdjust;
      right_pwm = baseSpeed;
    }

    if (ly_fix < 0) {  // Reverse
      left_pwm = -left_pwm;
      right_pwm = -right_pwm;
    }

    left_motor(left_pwm);
    right_motor(right_pwm);

    return;
  }

  // Forward/Backward
  if (abs(ly) > 100) {
    int ly_fix = -ly;

    float n_ly = ly_fix / 128.0;
    float n_rx = rx / 128.0;

    n_ly = constrain(n_ly, -1.0, 1.0);
    n_rx = constrain(n_rx, -1.0, 1.0);

    float left_speed = n_ly - n_rx;
    float right_speed = n_ly + n_rx;

    float max_val = max(abs(left_speed), abs(right_speed));
    if (max_val > 1.0) {
      left_speed /= max_val;
      right_speed /= max_val;
    }

    left_pwm = left_speed * maxSpeed;
    right_pwm = right_speed * maxSpeed;

    left_motor(left_pwm);
    right_motor(right_pwm);
    return;
  }

  // Stay in Place
  left_motor(0);
  right_motor(0);

  delay(100);
}


// Left Motor (Front and Rear)
void left_motor(int speed) {
  int pwm = abs(speed) * LEFT_CALIBRATION;

  analogWrite(EN_KD, pwm);
  analogWrite(EN_KB, pwm);

  if (speed > 0) {
    digitalWrite(IN1_KD, HIGH); digitalWrite(IN2_KD, LOW);
    digitalWrite(IN1_KB, HIGH); digitalWrite(IN2_KB, LOW);
  } else if (speed < 0) {
    digitalWrite(IN1_KD, LOW); digitalWrite(IN2_KD, HIGH);
    digitalWrite(IN1_KB, LOW); digitalWrite(IN2_KB, HIGH);
  } else {
    digitalWrite(IN1_KD, LOW); digitalWrite(IN2_KD, LOW);
    digitalWrite(IN1_KB, LOW); digitalWrite(IN2_KB, LOW);
  }
}

// Right Motor (Front and Rear)
void right_motor(int speed) {
  int pwm = abs(speed);

  analogWrite(EN_KaD, pwm);
  analogWrite(EN_KaB, pwm);

  if (speed > 0) {
    digitalWrite(IN1_KaD, LOW); digitalWrite(IN2_KaD, HIGH);
    digitalWrite(IN1_KaB, LOW); digitalWrite(IN2_KaB, HIGH);
  } else if (speed < 0) {
    digitalWrite(IN1_KaD, HIGH); digitalWrite(IN2_KaD, LOW);
    digitalWrite(IN1_KaB, HIGH); digitalWrite(IN2_KaB, LOW);
  } else {
    digitalWrite(IN1_KaD, LOW); digitalWrite(IN2_KaD, LOW);
    digitalWrite(IN1_KaB, LOW); digitalWrite(IN2_KaB, LOW);
  }
}

void stopMotors() {
  left_motor(0);
  right_motor(0);
}
