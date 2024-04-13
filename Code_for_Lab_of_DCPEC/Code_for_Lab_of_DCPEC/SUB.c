
#include "F28x_Project.h"
int main(void)
{
    InitSysCtrl();

    float x,y;
    x=1.5;
    y=2.4;

    while(1)
    {
        y=x+4.5;
    }
    return 0;
}

/* Clock Cycles 5 and Arithmetic Value 6.0 */
