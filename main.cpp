#include "msrv_msd6a648_touch.h"
#include <iostream>
using namespace std;

int main()
{
    MSRV_MSD6A648_TOUCH::GetInstance()->start();
    return 0;
}

