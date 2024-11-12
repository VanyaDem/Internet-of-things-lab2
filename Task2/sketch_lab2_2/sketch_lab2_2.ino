const int pin_first_led_out = 12;
const int pin_second_led_out = 13;

const float hz_for_first_mod = 3;
const float hz_for_second_mod = 2;

const int first_mod_cycle_number = 7;
const int second_mod_cycle_number = 6;

const float first_mod_duty_cycle_coefficient = 0.5;
const float second_mod_duty_cycle_coefficient = 0.3;

void setup() {
  pinMode(pin_first_led_out, OUTPUT);
  pinMode(pin_second_led_out, OUTPUT);
  Serial.begin(9600);
  Serial.println("Press '1' to start the first LED operation mode.");
  Serial.println("Press '2' to start the second LED operation mode.");
}

void loop() {
  if(Serial.available() > 0){
    int received_char = Serial.read();
    if(received_char == '1'){
      Serial.println("First LED operation mode");
      doFirstMod();
    }else if(received_char == '2'){
      Serial.println("Second LED operation mode");
      doSecondMod();
    }else{
      Serial.println("Press only 1 or 2 please.");
    }
  }
}

void doFirstMod(){
  doCycle(
    hz_for_first_mod,
    first_mod_cycle_number,
    first_mod_duty_cycle_coefficient,
    HIGH, LOW);
} 

void doSecondMod(){
  doCycle(
    hz_for_second_mod, 
    second_mod_cycle_number, 
    second_mod_duty_cycle_coefficient, 
    HIGH, HIGH);
}

void doCycle(float hz, int cycles, float duty_cycle_coefficient, int initState, int initState2){
  int on_duration = (int)calculateLedOnDuration(hz, duty_cycle_coefficient); 
  int off_duration = (int)calculateLedOffDuration(hz, duty_cycle_coefficient); 
  for(int i = 0; i < cycles; i++ ){

    blink(initState1,initState2);
    delay(on_duration);
    blink(invertValue(initState1),invertValue(initState2));
    delay(off_duration);
  }
  offBlink();
}

void blink(int first_pin_state, int second_pin_state){
  digitalWrite(pin_first_led_out, first_pin_state);
  digitalWrite(pin_second_led_out, second_pin_state);
}

int invertValue(int value){
  if(value == HIGH){
    return LOW;
  }else if(value == LOW){
    return HIGH;
  }else{
    return -1;
  }
}

void offBlink(){
  digitalWrite(pin_first_led_out, LOW);
  digitalWrite(pin_second_led_out, LOW);
}

float calculateLedOnDuration(float hz, float duty_cycle_coefficient){
  return 1000/hz*duty_cycle_coefficient;
}

float calculateLedOffDuration(float hz, float duty_cycle_coefficient){
  return 1000/hz*(1 - duty_cycle_coefficient);
}
