#include <Arduino.h>

// Forward declare the State struct and its pinter
struct State;
using StatePtr = State*;

// Define a function pointer type that takes bool and returns int
using StateFunctionPtr = StatePtr(*)(bool, unsigned long);

// Define the State struct
struct State {
  public:
  //States have a name
  const char* name;
  // And a pointer to a function that implements the state
  StateFunctionPtr function;  
};

class StateMachine {
  private:
  char* name;
  StatePtr current_state;
  StatePtr last_state;
  unsigned long state_start_millis;

  public:
  StateMachine(char* name, StatePtr start_state){
    this->name = name;
    current_state = start_state;
    last_state = nullptr;
  }

  void update(){

    // Detect if this is a first pass
    bool first_pass = current_state != last_state;
    last_state = current_state;

    if (first_pass) {

      state_start_millis = millis();

      // Print out the state transition
      Serial.print(name);
      Serial.print(": ");
      Serial.println(current_state->name);
    }
    
    unsigned long millis_in_state = millis() - state_start_millis;

    // Call the state function and get the output state
    StatePtr output_state = current_state->function(first_pass, millis_in_state);
    
    // Ignore nullptr output states.
    if (output_state != nullptr && output_state != 0){
      current_state = output_state;
    }

  }

  StatePtr get_state(){
    return current_state;
  }

};

