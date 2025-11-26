////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       eichen_lib.cpp
//*FILE DESC:       Implementation file for eichen library.
//*FILE VERSION:    0.7.1
//*FILE AUTHOR:     Chimaroke Okwara (chima-okwara)
//*LAST MODIFIED:   Wednesday, 26 November, 2025
//*LICENSE:         GNU LGPL v2.1
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <eichen_lib.h>

float& readVoltage(const uint32_t& pin, const long& _min, const long& _max)
{
    analogReadResolution(12);
    value = 0;
    actualVal = 0.0;
    sum = 0.0;
    avg = 0.0;
    valueAverage = 0.0;

    for(int i = 0; i < AVG; ++i)
    {
        average[i] = 0.0;
    }

    for(int i = 0; i < AVG; ++i)
    {
        value = analogRead(pin);
        long temp = map(value, 0, 4095, 0, 3300);
        long temp2 = map(temp, 0, 3300, _min, _max);
        valueAverage = float (temp2);
        average[i] = valueAverage;
    }

    for(int i = 0; i < AVG; ++i)
    {
        sum = sum + average[i];
    }
    avg = sum / float(AVG);


    return (avg);
}

void convToBase(float *_value)
{
        val = 0.0;
        val = (*_value) / 1000.0;
        *_value = val;
}


void convToMilli(float* _value)
{
    val = 0.0;
    val = (*_value) * 1000.0;
    *_value = val;
}


template <typename T>
    char intToChar(const T& input)
    {
        char result = uint8_t (input) + '0';
        return result;
    }

int charToInt(const char& input)
{
    int result = input - '0';
    return result;
}

long getBatPer(const float& batVoltage, const float& minVoltage, const float& maxVoltage)
{
    long per = 0.0;
    per = map(long(batVoltage), long(minVoltage), long(maxVoltage), 0, 100);

    per = constrain(per, 0, 100);
    return (per);
}

double convPWMtoVoltage(const uint32_t& pwmval, const uint32_t& pwmres, const float& volt)
{
    double maxpwmval = (pow(2, pwmres) - 1.0);      //maximum pwm value

    double convratio = (volt / maxpwmval);          //conversion ratio

    double val = (float(pwmval) * convratio);
    return (val);
}
