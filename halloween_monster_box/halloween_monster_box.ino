#include "state_machine.h"

const int pin_motor_a_in1 = 2;
const int pin_motor_a_in2 = 3;
const int pin_motor_b_in3 = 4;
const int pin_motor_b_in4 = 5;

// Instantiate state objects
State state_wakeup_shake;
State state_init_wait;
State state_sleeping;
State state_shaking;


StateMachine main_state_machine("Main", &state_wakeup_shake);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  state_wakeup_shake = {"Wake Up Shake", &state_wakeup_shake_function};
  state_init_wait = {"Init Wait", &state_init_wait_function};
  state_sleeping = {"Sleeping", &state_sleeping_function};
  state_shaking = {"Shaking", &state_shaking_function};

  pinMode(pin_motor_a_in1, OUTPUT);
  pinMode(pin_motor_a_in2, OUTPUT);
  pinMode(pin_motor_b_in3, OUTPUT);
  pinMode(pin_motor_b_in4, OUTPUT);
}

void loop() {
  main_state_machine.update();
}


StatePtr state_wakeup_shake_function( bool first_pass, unsigned long elapsed_millis){
  const long wait_time=1000;
  
  if ((elapsed_millis % 50) > 25)
  {
    digitalWrite(pin_motor_b_in3, HIGH);
    digitalWrite(pin_motor_b_in4, LOW);
  }
  else
  {
    digitalWrite(pin_motor_b_in3, LOW);
    digitalWrite(pin_motor_b_in4, HIGH);
  }


  if (elapsed_millis > wait_time){
    digitalWrite(pin_motor_b_in3, LOW);
    digitalWrite(pin_motor_b_in4, LOW);
    return &state_init_wait;
  }
  return nullptr;
}

StatePtr state_init_wait_function(bool first_pass, unsigned long elapsed_millis){
  const long wait_time=10000;

  if (elapsed_millis > wait_time){
    return &state_shaking;
  }
  return nullptr;
}

StatePtr state_sleeping_function(bool first_pass, unsigned long elapsed_millis){
  static long sleep_time;

  if (first_pass){
    sleep_time = random(5000,15000);
    Serial.print("Sleep Time: ");
    Serial.println(sleep_time);
  }

  digitalWrite(pin_motor_b_in3, LOW);
  digitalWrite(pin_motor_b_in4, LOW);
  
  if (elapsed_millis > sleep_time){
    return &state_shaking;
  }
  return nullptr;
}

StatePtr state_shaking_function(bool first_pass, unsigned long elapsed_millis){
  static long shake_time;
  
  if (first_pass){
    shake_time = random(1000,3000);
    Serial.print("Shake Time: ");
    Serial.println(shake_time);
  }

  digitalWrite(pin_motor_b_in3, HIGH);
  digitalWrite(pin_motor_b_in4, LOW);

  if (elapsed_millis > shake_time){
    digitalWrite(pin_motor_b_in3, LOW);
    digitalWrite(pin_motor_b_in4, LOW);
    return &state_sleeping;
  }
  return nullptr;
}




