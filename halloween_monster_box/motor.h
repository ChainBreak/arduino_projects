#include <Arduino.h>

class Motor{
  private:
  int pin_1;
  int pin_2;

  public:
  Motor(int pin_1, int pin_2){
    this->pin_1 = pin_1;
    this->pin_2 = pin_2;
  }

  void setup(){
    pinMode(pin_1, OUTPUT);
    pinMode(pin_2, OUTPUT);
    stop();
  }

  void forward() {
    digitalWrite(pin_1, HIGH);
    digitalWrite(pin_2, LOW);
  }

  void reverse(){
    digitalWrite(pin_1, LOW);
    digitalWrite(pin_2, HIGH);
  }

  void stop(){
    digitalWrite(pin_1, LOW);
    digitalWrite(pin_2, LOW);
  }
};