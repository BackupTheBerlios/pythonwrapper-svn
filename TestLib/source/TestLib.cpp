#include "TestLib.h"
#include <string.h>

static int gCalled = 0;
String gModuleName = "";

void PW_Init()
{
    gCalled++;
    gModuleName = ModuleName;
}


void PW_Deinit()
{
    gCalled--;
    gModuleName = "";
}


int PW_GetCount()
{
    return gCalled;
}


const String &PW_GetName()
{
    return gModuleName;
}
