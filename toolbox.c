#include <windows.h>

#include "constants.h"
#include "toolbox.h"

int roundfloat(double number)
{
    if((number - (int) number) < 0.5) {
        return (1 + (int) number);
    } else {
        return ((int) number);
    }
}
