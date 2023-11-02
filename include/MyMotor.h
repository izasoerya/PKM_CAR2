#ifndef Ppp_H
#define Ppp_H

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

        PinMotor(int ren, int len, int rpwm, int lpwm) 
            : PIN_LEN(len), PIN_REN(ren), PIN_LPWM(lpwm), PIN_RPWM(rpwm){};
    };

public:
    Motor();
};

class MainMotorLeft : protected Motor
{
private: 
    PinMotor left;      // ren, len, rpwm, lpwm
    const int SEN_LEFT = 5;
    const int SEN_RIGHT = 18;

public: 
    MainMotorLeft();
    void begin();
    void controlMotor(int input);
};

class MainMotorRight : protected Motor
{
private: 
    PinMotor right;      // ren, len, rpwm, lpwm
    const int SEN_LEFT = 5;
    const int SEN_RIGHT = 18;
    
public: 
    MainMotorRight();
    void begin();
    void controlMotor(int input);
};

#endif