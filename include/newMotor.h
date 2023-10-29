#ifndef MOTOR_H
#define MOTOR_H

class Motor 
{
protected:
    int speedMotor;
    int prevSpeedMotor;
    int analogLeft;
    int analogRight;

    struct PinMotor{    
        const int PIN_REN;
        const int PIN_LEN;
        const int PIN_RPWM;
        const int PIN_LPWM;

        PinMotor(int ren, int len, int rpwm, int lpwm) : PIN_LEN(len), PIN_REN(ren), PIN_LPWM(lpwm), PIN_RPWM(rpwm){};
    };

public:
    Motor();
};

class PowerWindow : private Motor 
{
private:
    const int PIN_POWERWINDOW_UP   = 2;     // Assign to pin 2
    const int PIN_POWERWINDOW_DOWN = 22;    // Assign to pin 22

public:
    PowerWindow();
    void begin();
    void controlMotor(bool LimitSwitchUP, bool LimitSwitchDown);
};

class MainMotorLeft : private Motor
{
private: 
    PinMotor left;      // ren, len, rpwm, lpwm

public: 
    MainMotorLeft();
    void begin();
    void controlMotor();
};

class MainMotorRight : private Motor
{
private: 
    PinMotor right;      // ren, len, rpwm, lpwm

public: 
    MainMotorRight();
    void begin();
    void controlMotor();
};

#endif