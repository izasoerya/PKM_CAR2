#ifndef POWER_WINDOW_H
#define POWER_WINDOW_H

class PowerWindow
{
private:
    const int PIN_POWERWINDOW_UP   = 2;     // Assign to pin 2
    const int PIN_POWERWINDOW_DOWN = 22;    // Assign to pin 22

public:
    PowerWindow();
    void begin();
    void controlMotor(bool LimitSwitchUP, bool LimitSwitchDown);
};

#endif