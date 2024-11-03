#include <VirtualWire.h>

// Define motor driver pins
#define MOTOR1_PIN_1 4
#define MOTOR1_PIN_2 5
#define MOTOR2_PIN_3 6
#define MOTOR2_PIN_4 7

#define MOTOR3_PIN_1 9
#define MOTOR3_PIN_2 10
#define MOTOR4_PIN_3 12
#define MOTOR4_PIN_4 11

char ch;
const int max_speed = 255; // Maximum motor speed

void setup()
{
  Serial.begin(115200);
  vw_set_rx_pin(13);
  vw_setup(2000);
  vw_rx_start();

  pinMode(MOTOR1_PIN_1, OUTPUT);
  pinMode(MOTOR1_PIN_2, OUTPUT);
  pinMode(MOTOR2_PIN_3, OUTPUT);
  pinMode(MOTOR2_PIN_4, OUTPUT);

  pinMode(MOTOR3_PIN_1, OUTPUT);
  pinMode(MOTOR3_PIN_2, OUTPUT);
  pinMode(MOTOR4_PIN_3, OUTPUT);
  pinMode(MOTOR4_PIN_4, OUTPUT);
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN; 

  if (vw_get_message(buf, &buflen))
  {
    //Non-Holonomic (L JOY)
    if(buf[0]=='a')
    { //Right Rotate
      ch = 'a';
    }  
    else if(buf[0]=='b')
    { //Left Rotate
      ch = 'b';
    }  
    else if(buf[0]=='c')
    { //Forward
      ch = 'c';
    } 
    else if(buf[0]=='d')
    { //Backward
      ch = 'd';
    }
    //Holonomic (R JOY)
    else if(buf[0]=='f')
    { //
      ch = 'f';
    } 
    else if(buf[0]=='g')
    { //
      ch = 'g';
    } 
    else if(buf[0]=='h')
    { //
      ch = 'h';
    } 
    else if(buf[0]=='i')
    { //
      ch = 'i';
    } 
    else if(buf[0]=='k')
    { //
      ch = 'k';
    } 
    else if(buf[0]=='l')
    { //
      ch = 'l';
    } 
    else if(buf[0]=='m')
    { //
      ch = 'm';
    } 
    else if(buf[0]=='n')
    { //STOP
      ch = 'n';
    } 
    else if(buf[0]=='e')
    { //STOP
      ch = 'e';
    } 
    else
    { //STOP
      Serial.println("INVALID DATA RECEIVED !!");
    }
    Serial.println(ch);
  }

  drive(ch);
}

// Function to set motor speed and direction
void setMotor(int pinA, int pinB, int speed) {
  if (speed > 0) {
    analogWrite(pinA, speed);
    analogWrite(pinB, 0);
  } else if (speed < 0) {
    analogWrite(pinA, 0);
    analogWrite(pinB, -speed);
  } else {
    analogWrite(pinA, 0);
    analogWrite(pinB, 0);
  }
}

// Function to control motors based on direction
void drive(char command) {
  int motor1Speed = 0, motor2Speed = 0, motor3Speed = 0, motor4Speed = 0;

  switch (command) {
    case 'c': // Forward
      motor1Speed = max_speed;
      motor2Speed = max_speed;
      motor3Speed = max_speed;
      motor4Speed = max_speed;
      break;
      
    case 'd': // Backward
      motor1Speed = -max_speed;
      motor2Speed = -max_speed;
      motor3Speed = -max_speed;
      motor4Speed = -max_speed;
      break;

    case 'a': // Rotate right
      motor1Speed = max_speed;
      motor2Speed = max_speed;
      motor3Speed = -max_speed;
      motor4Speed = -max_speed;
      break;

    case 'b': // Rotate left
      motor1Speed = -max_speed;
      motor2Speed = -max_speed;
      motor3Speed = max_speed;
      motor4Speed = max_speed;
      break;

    case 'f': // Slide right
      motor1Speed = -max_speed;
      motor2Speed = max_speed;
      motor3Speed = max_speed;
      motor4Speed = -max_speed;
      break;

    case 'g': // Slide left
      motor1Speed = max_speed;
      motor2Speed = -max_speed;
      motor3Speed = -max_speed;
      motor4Speed = max_speed;
      break;

    case 'h': // diagonal right forward
      motor1Speed = 0;
      motor2Speed = max_speed;
      motor3Speed = max_speed;
      motor4Speed = 0;
      break;

    case 'i': // diagonal right backward
      motor1Speed = 0;
      motor2Speed = -max_speed;
      motor3Speed = -max_speed;
      motor4Speed = 0;
      break;

    case 'k': // diagonal left forward
      motor1Speed = max_speed;
      motor2Speed = 0;
      motor3Speed = 0;
      motor4Speed = max_speed;
      break;

    case 'l': // diagonal right backward
      motor1Speed = -max_speed;
      motor2Speed = 0;
      motor3Speed = 0;
      motor4Speed = -max_speed;
      break;

    case 'm': // rotate 
      motor1Speed = max_speed;
      motor2Speed = 0;
      motor3Speed = -max_speed;
      motor4Speed = 0;
      break;

    case 'n': // rotate
      motor1Speed = 0;
      motor2Speed = -max_speed;
      motor3Speed = 0;
      motor4Speed = max_speed;
      break;

    default: // Stop
      motor1Speed = motor2Speed = motor3Speed = motor4Speed = 0;
      break;
  }

  // Set motor speeds
  setMotor(MOTOR1_PIN_1, MOTOR1_PIN_2, motor1Speed);
  setMotor(MOTOR2_PIN_3, MOTOR2_PIN_4, motor2Speed);
  setMotor(MOTOR3_PIN_1, MOTOR3_PIN_2, motor3Speed);
  setMotor(MOTOR4_PIN_3, MOTOR4_PIN_4, motor4Speed);
}


