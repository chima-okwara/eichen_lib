/*/////////////////////////////////////////////////////////////////////////////////*
    eichen_lib, A library designed for use with Arduino framework using PlatformIO IDE
    Copyright (C) <2024>  <chima-okwara>
    Email: cokwara82@protonmail.com
           cokwara82@gmail.com
    WhatsApp/Telegram:  +234-708-363-3859

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/////////////////////////////////////////////////////////////////////////////*

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
//The objects below must be declared in main.cpp if the user intends to use the readVoltage() or readVoltageDivider() method:
extern double average[AVG], valueAverage, sum, avg, val, actualVal;
extern uint32_t value;



//Library constants
const float voltageTable[] =        //to be upgraded for each battery type. current values for 4s LFP4 battery packs.
{

    14.40, 100.0,  // Full charge
    14.20,  99.0,
    13.60,  95.0,  // Bulk charging complete
    13.40,  90.0,
    13.32,  80.0,  // Flat region begins
    13.30,  70.0,
    13.28,  60.0,
    13.26,  50.0,
    13.24,  40.0,
    13.20,  30.0,
    13.16,  20.0,
    13.12,  15.0,  // Flat region ends
    13.00,  10.0,
    12.80,   5.0,  // Nominal voltage (low capacity remaining)
    12.00,   2.0,
    11.20,   0.0   // Minimum safe voltage (2.8V per cell)

};

/*
Other lookup tables:
18650/21700 (3s):
    12.60, 100.0,  // Full charge (4.20V per cell)
    12.30,  95.0,
    12.18,  90.0,
    12.06,  80.0,
    11.97,  70.0,
    11.88,  60.0,
    11.79,  50.0,
    11.70,  40.0,
    11.61,  30.0,
    11.52,  20.0,
    11.43,  15.0,
    11.31,  10.0,
    11.19,   5.0,
    11.10,   2.0,  // Nominal voltage
    9.00,   0.0   // Minimum safe voltage (3.00V per cell)

18650/21700 (1s):
     4.20, 100.0,
    4.06,  95.0,
    3.98,  90.0,
    3.92,  85.0,
    3.87,  80.0,
    3.82,  75.0,
    3.79,  70.0,
    3.77,  65.0,
    3.75,  60.0,
    3.73,  55.0,
    3.71,  50.0,
    3.69,  45.0,
    3.61,  40.0,
    3.59,  35.0,
    3.58,  30.0,
    3.56,  25.0,
    3.51,  20.0,
    3.45,  15.0,
    3.41,  10.0,
    3.30,   5.0,
    3.00,   0.0

3.2V LFP4 (1s)




*/

const int voltageTableSize = sizeof(voltageTable) / sizeof(voltageTable[0]) / 2;



//Methods:
double& readVoltage(const uint32_t& pin, const uint32_t& res, const double& maxvoltage);      //Method that measures an analogue voltage. Arguments: Pin, Analogue read resolution, Maximum voltage of adc


double readVoltageDivider(const uint32_t& pin, const long&res, const long& maxvoltage, const double r1, const double r2, const float& offset = 0.0); //Method that measures the analog output voltage at a voltage divider. Arguments: Pin, Analogue read resolution, ADC max voltage, R1, R2, and offset value.

void convToBase(double*);        //Method that divides the argument passed by 1000.

void convToMilli(double*);       //Method that multiplies the argument passed by 1000.

long getBatPer(const double& batVoltage);     //Method to calculate battery SoC based on voltage. Returns battery percentage as a long.

template <typename T>
    char intToChar(const T&);

int charToInt(const char&);

double convPWMtoVoltage(const uint32_t& pwmval, const uint32_t& pwmres, const float& maxvoltage);

long convVoltagetoPWM(const double& voltage, const double& minVoltage, const double& maxVoltage, const uint32_t pwmres);

long getMaxAnalogueValue(const uint32_t& res);



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
