#include "Button.h"
#include "../Bounce2/Bounce2.h"

#define ON_STATE 0
#define BUTTONS_COUNT 8

Button::Button(uint8_t inputPin, uint8_t outputPin, int autoOff)
{
    _inputPin = inputPin;
    _outputPin = outputPin;
    
    _autoOff = autoOff;
    _countdown = 0;
    _countdownActive = false;
}

void Button::init(void)
{
    pinMode(_inputPin, INPUT_PULLUP);

    if (_outputPin > 0) {
        pinMode(_outputPin, OUTPUT);
    }
    
    _bounce = Bounce();
    _bounce.attach(_inputPin);
    _bounce.interval(50); 

    writeState(!ON_STATE, {}, false);
}

void Button::update(void)
{
    _bounce.update();
}

bool Button::getState(void) {
    return digitalRead(_outputPin);
}

void Button::writeState(int state, Button buttons[], bool byButton) {
    // when turning off by timer button, keep it on - countdown will handle it
    if (state != ON_STATE && _autoOff > 0 && byButton) {
      // keep turned on
      state = ON_STATE;
    }
    
    if (_outputPin > 0) {
        digitalWrite(_outputPin, state);
    }

    // when just turned on, clear timers of others buttons with same output pin
    if (state == ON_STATE) {
        // TODO replace BUTTONS_COUNT with sizeof (but sizeof(buttons) / sizeof(buttons[0]) doesnt work :( )
        for (int i=0; i<BUTTONS_COUNT; i++) {
          if (buttons[i].getOutputPin() == _outputPin) {
            buttons[i].resetCountdown();
          }
        }
    }

    if (state == ON_STATE && _autoOff > 0)  {
        // start countdown
        startCountdown();
    } else {
        // just turned off -> reset and disable countdown
        resetCountdown();
    }
}

void Button::startCountdown() {
  _countdown = _autoOff;
  _countdownActive = true;
}

void Button::resetCountdown() {
  _countdown = 0;
  _countdownActive = false;
}

bool Button::checkCountdown() {    
    if (_countdownActive) {
        _countdown --;
        if (_countdown <= 0) {
            // countdown done -> disable and turn off output
            _countdownActive = false;
            writeState(!ON_STATE, {}, false);
            return true;
        } 
    }
    return false;
}

uint8_t Button::getOutputPin(void)
{
  return _outputPin;
}

bool Button::isFell(void)
{
    return _bounce.fell();
}

bool Button::isRise(void)
{
    return _bounce.rose();
}
