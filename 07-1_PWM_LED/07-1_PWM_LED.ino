#include <string.h>

#define LED_PIN       25    // GPIO pin of LED
#define PWM_CHANNEL   0     // PWM channel (0~15)
#define PWM_FREQ      5000  // PWM frequency
#define PWM_BITS      12    // PWM resolution bits of duty
#define PWM_MAX_DUTY  4095  // The maximum value of duty

void setup() {
  // Initialize LED pin as output
  pinMode(LED_PIN, OUTPUT);
  // PWM channel setup
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_BITS);
  // Attach LED pin to PWM channel
  ledcAttachPin(LED_PIN, PWM_CHANNEL);
  // Open serial port, set data rate to 115200 bps
  Serial.begin(115200);
  while(!Serial); // wait until serial port is ready
  Serial.println("Program Start!!");      
}

void loop() {
  static char buf[200];
  static int  length = 0;
  int incoming_byte;
  int value; 

  // If there is any data incoming, read a byte and put it on string buffer
  if(Serial.available() > 0) { // check if there is incoming data
    incoming_byte = Serial.read();  // read the incoming byte
    buf[length++] = incoming_byte;  // put the incoming byte to string buffer
    if(incoming_byte == '\n') { // check if LF is incoming
      // append '\0' to buf[] as the end of the string
      buf[length++] = '\0';
      // do job
      value = atoi(buf);
      Serial.print("I got: ");
      Serial.println(value);
      if(value >= 0 && value <=PWM_MAX_DUTY) ledcWrite(PWM_CHANNEL, value);
      length = 0; // reset the length for receiving next string
    }
  }
}
