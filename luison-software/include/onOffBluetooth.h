#ifndef _on_off_bluetooth_h_
#define _on_off_bluetooth_h_

#if ON_OFF_METHOD == 1 || ON_OFF_METHOD == 2
#include "onOffControl.h"

#include "bluetooth.h"

namespace onOffControl
{
    void setup()
    {
        bluetooth::setup();
        active = false;
    }

    bool loadStart(uint_fast8_t &active)
    {
        return bluetooth::loadStart(active);
    }
}

#endif

#endif