const int pin_led_out = 12;

void setup() {
  pinMode(pin_led_out, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    int recived_char = Serial.read();

    if(recived_char == 'a'){
      digitalWrite(pin_led_out, HIGH);
      Serial.println("Led on");
    }else if(recived_char == 'b'){
      digitalWrite(pin_led_out, LOW);
      Serial.println("Led off");
    }else{
      Serial.println("Write only a or b please.");
    }
  }
}
