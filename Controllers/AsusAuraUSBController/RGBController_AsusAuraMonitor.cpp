/*-----------------------------------------*\
|  RGBController_AsusAuraMonitor.cpp        |
|                                           |
|  Generic RGB Interface for Asus Aura      |
|  USB controller driver                    |
|                                           |
|  Mola19 08/03/2022                        |
\*-----------------------------------------*/

#include "RGBController_AsusAuraMonitor.h"

RGBController_AuraMonitor::RGBController_AuraMonitor(AuraMonitorController* controller_ptr)
{
    controller  = controller_ptr;

    name        = "ASUS Aura Monitor";
    vendor      = "ASUS";
    type        = DEVICE_TYPE_LEDSTRIP;
    description = "ASUS Aura Monitor Device";
    location    = controller->GetDeviceLocation();
    serial      = controller->GetSerialString();

    mode Direct;
    Direct.name       = "Direct";
    Direct.value      = 0;
    Direct.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Direct.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Direct);

    SetupZones();
}

RGBController_AuraMonitor::~RGBController_AuraMonitor()
{
    delete controller;
}

void RGBController_AuraMonitor::SetupZones()
{
    zone underglow_zone;

    underglow_zone.name         = "Backlight";
    underglow_zone.type         = ZONE_TYPE_LINEAR;
    underglow_zone.leds_min     = 3;
    underglow_zone.leds_max     = 3;
    underglow_zone.leds_count   = 3;
    underglow_zone.matrix_map   = NULL;

    zones.push_back(underglow_zone);

    for(unsigned int i = 0; i < 3; i++)
    {
        led underglow_led;

        underglow_led.name      = "Backlight LED " + std::to_string(i + 1);

        leds.push_back(underglow_led);
    }

    SetupColors();
}

void RGBController_AuraMonitor::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_AuraMonitor::DeviceUpdateLEDs()
{
    for (int i = 0; i < 3; i++)
    {
        unsigned char red   = RGBGetRValue(colors[i]);
        unsigned char green = RGBGetGValue(colors[i]);
        unsigned char blue  = RGBGetBValue(colors[i]);

        controller->UpdateLed(i, red, green, blue);
    }

    controller->ApplyChanges();
}

void RGBController_AuraMonitor::UpdateZoneLEDs(int /*zone*/)
{
    DeviceUpdateLEDs();
}

void RGBController_AuraMonitor::UpdateSingleLED(int led)
{
    unsigned char red   = RGBGetRValue(colors[led]);
    unsigned char green = RGBGetGValue(colors[led]);
    unsigned char blue  = RGBGetBValue(colors[led]);

    controller->UpdateLed(led, red, green, blue);

    controller->ApplyChanges();
}

void RGBController_AuraMonitor::SetCustomMode()
{
    active_mode = 0;
}


void RGBController_AuraMonitor::DeviceUpdateMode()
{
    /*---------------------------------------------------------*\
    | This device does not support Mode changing                |
    \*---------------------------------------------------------*/
}

void RGBController_AuraMonitor::DeviceSaveMode()
{
    /*---------------------------------------------------------*\
    | This device does not support Mode saving                  |
    \*---------------------------------------------------------*/
}
