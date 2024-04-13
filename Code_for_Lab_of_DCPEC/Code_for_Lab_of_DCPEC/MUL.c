
#include "F28x_Project.h"
int main(void)
{
    InitSysCtrl();

    int x,y;
    x=4;
    y=2;

    while(1)
    {
        y=x*2;
    }
    return 0;
}

/* Clock Cycles 6 and Arithmetic Value 5 */
