void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = map(pulse, 0, 180, SERVOMIN, SERVOMAX); // Map the angle to the correct pulse length
  pwm.setPWM(n, 0, pulselength);
}

void detachServo(uint8_t num) {
  pwm.setPWM(num, 0, 0); // This stops sending the PWM signal
}
