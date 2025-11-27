////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       eichen_lib.h
//*FILE DESC:       Header file for eichen library.
//*FILE VERSION:    0.7.1
//*FILE AUTHOR:     Chimaroke Okwara (chima-okwara)
//*LAST MODIFIED:   Wednesday, 26 November, 2025
//*LICENSE:         GNU LGPL v2.1
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __EICHEN__LIB__
#define __EICHEN__LIB__

#include <Arduino.h>
#include <math.h>

#ifndef AVG
    #define AVG 500
#endif // AVG

#define MinBatVoltage   9.5
#define MaxBatVoltage   12.6

#define hour 1
#define minute 2

//Attributes:

//********************************PLEASE NOTE************************************
//The objects below must be declared in main.cpp:
extern double average[AVG], valueAverage, sum, avg, val, actualVal;
extern uint32_t value;



//Methods:
double& readVoltage(const uint32_t&, const long&, const long&);      //Method that measures an analogue voltage. Arguments: Pin, Minimum expected voltage value, Maximum expected voltage value.

void convToBase(double*);        //Method that divides the argument passed by 1000.

void convToMilli(double*);       //Method that multiplies the argument passed by 1000.

long getBatPer(const double& batVoltage, const double& minVoltage, const double& maxVoltage);     //Method to calculate battery SoC based on voltage. Returns battery percentage as a long.

template <typename T>
    char intToChar(const T&);

int charToInt(const char&);

double convPWMtoVoltage(const uint32_t& pwmval, const uint32_t& pwmres, const float& maxvoltage);

long convVoltagetoPWM(const double& voltage, const double& minVoltage, const double& maxVoltage, const uint32_t pwmres);



//FUnction to convert milliseconds to hours or minutes..
//Arguments: mode (hour, minute), ms (value in milliseconds to convert to hours or minutes)
//Returns time value in hours or minutes as integer
template<typename t1>
    long convertMstoHrMn(const uint8_t& mode, const t1& ms)
    {
        long buf = 0;
        long output = 0;
        switch(mode)
        {
            case hour:
            {
                buf = ms / 1000;
                output = buf / (60 * 60);
                return output;
                break;
            }

            case minute:
            {
                buf = ms / 1000;
                output = buf / 60;
                return output;
                break;
            }

            default:
            {
                return 0;
                break;
            }
        }
    }


//Function to map a value to a range of values.
//Arguments: pwmValue = value to be mapped
//           minValue = mimimum possible value of pwmValue
//           maxValue = maximum possible value for pwmValue
//           outputMin = minimum value to map to
//           outputMax = maximum value to map to
//Returns same type as pwmValue
template <typename t1, typename t2>
    t1 mapValueToRange(t1 pwmValue, const t2& minValue, const t2& maxValue, const t2& outputMin, const t2& outputMax)
    {
        t1 output;
        output = map(pwmValue, minValue, maxValue, outputMin, outputMax);
        output = constrain(output, outputMin, outputMax);
        return output;
    }



#endif
