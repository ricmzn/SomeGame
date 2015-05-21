#include "Input.h"
using namespace System;

int Input::KeyArray::operator[](const int& code) const
{
    return keys[code] == 1;
}

Input::KeyArray::KeyArray()
{
    for(int& key : keys) {
        key = 0;
    }
}
