/*----------------------------------------------------------------------*
 * Arduino Button Library v1.0                                          *
 * Jack Christensen Mar 2012                                            *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/
#ifndef Button_h
#define Button_h
#include <Arduino.h> 
#include "../Bounce2/Bounce2.h"

class Button
{ 
    public:
        Button(uint8_t inputPin, uint8_t outputPin = 0, int autoOff = 0);
        bool isFell();
        bool isRise();
        bool getState();
        void update();
        void init();
        void writeState(int state, Button buttons[], bool byButton);
        bool checkCountdown();
        void resetCountdown();
        void startCountdown();
        uint8_t getOutputPin();
        
    private:
        uint8_t _inputPin;  
        uint8_t _outputPin;  
        int _autoOff;
        int _countdown;
        bool _countdownActive;
        bool _state;
        Bounce _bounce;
};
#endif
