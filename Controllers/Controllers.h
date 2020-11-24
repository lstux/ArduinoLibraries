#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <Arduino.h>
#include <stdint.h>

#define CONTROLLER_UNCHANGED 0
#define CONTROLLER_PRESSED   1
#define CONTROLLER_RELEASED  2
#define CONTROLLER_CHANGED   3

struct joystate {
  uint16_t x;
  uint16_t y;
};


class ControllerJoystick {
  public:
    ControllerJoystick(uint8_t x_axis_pin, uint8_t y_axis_pin);
    uint8_t check();
    joystate getState();
    uint16_t getX();
    uint16_t getY();
  private:
    uint8_t x_axis;
    uint8_t y_axis;
    joystate state;
};

class ControllerButton {
  public:
    ControllerButton(uint8_t pin);
    uint8_t check();
    uint8_t getState();
  private:
    uint8_t pin;
    uint8_t state;
};

ControllerJoystick::ControllerJoystick(uint8_t x_axis_pin, uint8_t y_axis_pin) {
  this->x_axis = x_axis_pin;
  pinMode(x_axis_pin, INPUT);
  this->y_axis = y_axis_pin;
  pinMode(y_axis_pin, INPUT);
  this->state = { analogRead(x_axis_pin), analogRead(y_axis_pin) };
}

uint8_t ControllerJoystick::check() {
  uint16_t x = analogRead(this->x_axis);
  uint16_t y = analogRead(this->y_axis);
  uint8_t c;
  if ((x != this->state.x) || (y != this->state.y)) c = CONTROLLER_CHANGED;
  else c = CONTROLLER_UNCHANGED;
  this->state = { x, y };
  return c;
}

joystate ControllerJoystick::getState() {
  return this->state;
}

uint16_t ControllerJoystick::getX() {
  return this->state.x;
}

uint16_t ControllerJoystick::getY() {
  return this->state.y;
}



ControllerButton::ControllerButton(uint8_t pin) {
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
  this->state = digitalRead(pin);
}

uint8_t ControllerButton::check() {
  uint8_t v = digitalRead(this->pin);
  if (v == this->state) return CONTROLLER_UNCHANGED;
  if (v) {
    this->state = v;
    return CONTROLLER_RELEASED;
  }
  this->state = v;
  return CONTROLLER_PRESSED;
}

uint8_t ControllerButton::getState() {
  return !this->state;
}

#endif
