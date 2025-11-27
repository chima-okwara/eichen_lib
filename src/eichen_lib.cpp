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
*/////////////////////////////////////////////////////////////////////////////*/

#include <eichen_lib.h>

double& readVoltage(const uint32_t& pin, const long& _min, const long& _max)
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
        valueAverage = double (temp2);
        average[i] = valueAverage;
    }

    for(int i = 0; i < AVG; ++i)
    {
        sum = sum + average[i];
    }
    avg = sum / double(AVG);


    return (avg);
}

void convToBase(double *_value)
{
        val = 0.0;
        val = (*_value) / 1000.0;
        *_value = val;
}


void convToMilli(double* _value)
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

long getBatPer(const double& batVoltage, const double& minVoltage, const double& maxVoltage)
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

long convVoltagetoPWM(const double& voltage, const double& minvoltage, const double& maxvoltage, const uint32_t pwmres)
{
    double maxpwmval =(pow(2, pwmres) - 1.0);
    double v = voltage, minV = minvoltage, maxV = maxvoltage;
    convToMilli(&v);
    convToMilli(&minV);
    convToMilli(&maxV);

    long vlong = long(v), minVLong = long(minV), maxVLong = long(maxV);

    long pwmval = map(vlong, minVLong, maxVLong, 0, maxpwmval);
    return (pwmval);
}
