#include <VirtualWire.h>

// Define joystick pins
#define JOYSTICK_LEFT_X A7
#define JOYSTICK_LEFT_Y A6
#define JOYSTICK_RIGHT_X A4
#define JOYSTICK_RIGHT_Y A3

#define JOYSTICK_LEFT_KEY 2
#define JOYSTICK_RIGHT_KEY 5

#define tx_pin 9

int lx = 0;
int ly = 0;
int rx = 0;
int ry = 0;

int rs = 0;
int ls = 0;

// Threshold for joystick deadzone
const int deadzone = 50;
char *data;

// Function to map joystick input (-512 to 512) to motor speed (-255 to 255)
int mapJoystick(int val) {
  return map(val, 0, 1023, -512, 512);
}

void setup() 
{
  Serial.begin(115200);
  vw_set_tx_pin(tx_pin);
  vw_setup(2000);
  pinMode(JOYSTICK_LEFT_X, INPUT);
  pinMode(JOYSTICK_LEFT_Y, INPUT);
  pinMode(JOYSTICK_RIGHT_X, INPUT);
  pinMode(JOYSTICK_RIGHT_Y, INPUT);

  pinMode(JOYSTICK_RIGHT_KEY, INPUT_PULLUP);
  pinMode(JOYSTICK_LEFT_KEY, INPUT_PULLUP);
}

void loop()
{
  lx = mapJoystick(analogRead(JOYSTICK_LEFT_X));
  ly = mapJoystick(analogRead(JOYSTICK_LEFT_Y));
  rx = mapJoystick(analogRead(JOYSTICK_RIGHT_X));
  ry = mapJoystick(analogRead(JOYSTICK_RIGHT_Y));

  rs = digitalRead(JOYSTICK_RIGHT_KEY);
  ls = digitalRead(JOYSTICK_LEFT_KEY);

  // Serial.println("LX = " + String(lx));
  // Serial.println("LY = " + String(ly));
  // Serial.println("RX = " + String(rx));
  // Serial.println("RY = " + String(ry));

  if(lx == -512 && rs == 1)
  {
    data="a";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(lx == 512 && rs == 1)
  {
    data="b";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  if(lx == -512 && rs == 0)
  {
    data="m";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(lx == 512 && rs == 0)
  {
    data="n";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(ly == 512)
  {
    data="c";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(ly == -512)
  {
    data="d";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(rx == 512)
  {
    data="f";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(rx == -512)
  {
    data="g";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(ry == -512 && ls == 1)
  {
    data="h";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(ry == 512 && ls == 1)
  {
    data="i";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(ry == 512 && ls == 0)
  {
    data="l";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else if(ry == -512 && ls == 0)
  {
    data="k";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  else
  {
    data="e";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }

  delay(50);
}

