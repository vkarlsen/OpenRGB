/*-----------------------------------------*\
|  RGBController_AMDWraithPrism.cpp         |
|                                           |
|  Generic RGB Interface for AMD Wraith     |
|  Prism                                    |
|                                           |
|  Adam Honse (CalcProgrammer1) 12/25/2019  |
\*-----------------------------------------*/

#include "RGBController_AMDWraithPrism.h"

RGBController_AMDWraithPrism::RGBController_AMDWraithPrism(AMDWraithPrismController* controller_ptr)
{
    controller  = controller_ptr;

    name        = "AMD Wraith Prism";
    vendor      = "Cooler Master";
    type        = DEVICE_TYPE_COOLER;
    description = "AMD Wraith Prism Device";
    version     = controller->GetFirmwareVersionString();
    location    = controller->GetLocationString();
    /*-----------------------------------------------------*\
    | Don't use HID serial string, it is inconsistent on my |
    | Wraith Prism                                          |
    \*-----------------------------------------------------*/
    serial      = "";//controller->GetSerialString();

    mode Direct;
    Direct.name                 = "Direct";
    Direct.value                = AMD_WRAITH_PRISM_EFFECT_CHANNEL_STATIC;
    Direct.flags                = MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_BRIGHTNESS;
    Direct.brightness_min       = 0;
    Direct.brightness_max       = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Direct.brightness           = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Direct.color_mode           = MODE_COLORS_PER_LED;
    modes.push_back(Direct);

    mode Breathing;
    Breathing.name              = "Breathing";
    Breathing.value             = AMD_WRAITH_PRISM_EFFECT_CHANNEL_BREATHING;
    Breathing.flags             = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_RANDOM_COLOR | MODE_FLAG_HAS_BRIGHTNESS;
    Breathing.speed_min         = AMD_WRAITH_PRISM_SPEED_SLOWEST;
    Breathing.speed_max         = AMD_WRAITH_PRISM_SPEED_FASTEST;
    Breathing.brightness_min    = 0;
    Breathing.brightness_max    = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Breathing.brightness        = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Breathing.color_mode        = MODE_COLORS_PER_LED;
    Breathing.speed             = AMD_WRAITH_PRISM_SPEED_NORMAL;
    modes.push_back(Breathing);

    mode ColorCycle;
    ColorCycle.name             = "Color Cycle";
    ColorCycle.value            = AMD_WRAITH_PRISM_EFFECT_CHANNEL_COLOR_CYCLE;
    ColorCycle.flags            = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS;
    ColorCycle.speed_min        = AMD_WRAITH_PRISM_SPEED_SLOWEST;
    ColorCycle.speed_max        = AMD_WRAITH_PRISM_SPEED_FASTEST;
    ColorCycle.brightness_min   = 0;
    ColorCycle.brightness_max   = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_CYCLE_MAX;
    ColorCycle.brightness       = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_CYCLE_MAX;
    ColorCycle.color_mode       = MODE_COLORS_NONE;
    ColorCycle.speed            = AMD_WRAITH_PRISM_SPEED_NORMAL;
    modes.push_back(ColorCycle);

    mode Rainbow;
    Rainbow.name                = "Rainbow";
    Rainbow.value               = AMD_WRAITH_PRISM_EFFECT_CHANNEL_RAINBOW;
    Rainbow.flags               = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS;
    Rainbow.speed_min           = AMD_WRAITH_PRISM_SPEED_SLOWEST;
    Rainbow.speed_max           = AMD_WRAITH_PRISM_SPEED_FASTEST;
    Rainbow.brightness_min      = 0;
    Rainbow.brightness_max      = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Rainbow.brightness          = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;    //The Ring zone can not get brighter but Logo / Fan can
    Rainbow.color_mode          = MODE_COLORS_NONE;
    Rainbow.speed               = AMD_WRAITH_PRISM_SPEED_NORMAL;
    modes.push_back(Rainbow);

    mode Bounce;
    Bounce.name                 = "Bounce";
    Bounce.value                = AMD_WRAITH_PRISM_EFFECT_CHANNEL_BOUNCE;
    Bounce.flags                = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS;
    Bounce.speed_min            = AMD_WRAITH_PRISM_SPEED_SLOWEST;
    Bounce.speed_max            = AMD_WRAITH_PRISM_SPEED_FASTEST;
    Bounce.brightness_min       = 0;
    Bounce.brightness_max       = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Bounce.brightness           = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;    //The Ring zone can not get brighter but Logo / Fan can
    Bounce.color_mode           = MODE_COLORS_NONE;
    Bounce.speed                = AMD_WRAITH_PRISM_SPEED_NORMAL;
    modes.push_back(Bounce);

    mode Chase;
    Chase.name                  = "Chase";
    Chase.value                 = AMD_WRAITH_PRISM_EFFECT_CHANNEL_CHASE;
    Chase.flags                 = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_RANDOM_COLOR | MODE_FLAG_HAS_BRIGHTNESS;
    Chase.speed_min             = AMD_WRAITH_PRISM_SPEED_SLOWEST;
    Chase.speed_max             = AMD_WRAITH_PRISM_SPEED_FASTEST;
    Chase.brightness_min        = 0;
    Chase.brightness_max        = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Chase.brightness            = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Chase.color_mode            = MODE_COLORS_PER_LED;
    Chase.speed                 = AMD_WRAITH_PRISM_SPEED_NORMAL;
    modes.push_back(Chase);

    mode Swirl;
    Swirl.name                  = "Swirl";
    Swirl.value                 = AMD_WRAITH_PRISM_EFFECT_CHANNEL_SWIRL;
    Swirl.flags                 = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_RANDOM_COLOR | MODE_FLAG_HAS_BRIGHTNESS;
    Swirl.speed_min             = AMD_WRAITH_PRISM_SPEED_SLOWEST;
    Swirl.speed_max             = AMD_WRAITH_PRISM_SPEED_FASTEST;
    Swirl.brightness_min        = 0;
    Swirl.brightness_max        = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Swirl.brightness            = AMD_WRAITH_PRISM_FAN_BRIGHTNESS_DEFAULT_MAX;
    Swirl.color_mode            = MODE_COLORS_PER_LED;
    Swirl.speed                 = AMD_WRAITH_PRISM_SPEED_NORMAL;
    modes.push_back(Swirl);

    SetupZones();
}

RGBController_AMDWraithPrism::~RGBController_AMDWraithPrism()
{
    delete controller;
}

void RGBController_AMDWraithPrism::SetupZones()
{
    /*---------------------------------------------------------*\
    | Set up zones                                              |
    \*---------------------------------------------------------*/
    zone logo_zone;
    logo_zone.name          = "Logo";
    logo_zone.type          = ZONE_TYPE_SINGLE;
    logo_zone.leds_min      = 1;
    logo_zone.leds_max      = 1;
    logo_zone.leds_count    = 1;
    logo_zone.matrix_map    = NULL;
    zones.push_back(logo_zone);

    zone fan_zone;
    fan_zone.name           = "Fan";
    fan_zone.type           = ZONE_TYPE_SINGLE;
    fan_zone.leds_min       = 1;
    fan_zone.leds_max       = 1;
    fan_zone.leds_count     = 1;
    fan_zone.matrix_map     = NULL;
    zones.push_back(fan_zone);

    zone ring_zone;
    ring_zone.name          = "Ring";
    ring_zone.type          = ZONE_TYPE_SINGLE;
    ring_zone.leds_min      = 1;
    ring_zone.leds_max      = 1;
    ring_zone.leds_count    = 1;
    ring_zone.matrix_map    = NULL;
    zones.push_back(ring_zone);

    /*---------------------------------------------------------*\
    | Set up LEDs                                               |
    \*---------------------------------------------------------*/
    led logo_led;
    logo_led.name = "Logo LED";
    leds.push_back(logo_led);

    led fan_led;
    fan_led.name = "Fan LED";
    leds.push_back(fan_led);

    led ring_led;
    ring_led.name = "Ring LED";
    leds.push_back(ring_led);

    SetupColors();
}

void RGBController_AMDWraithPrism::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_AMDWraithPrism::DeviceUpdateLEDs()
{
    unsigned char red = RGBGetRValue(colors[0]);
    unsigned char grn = RGBGetGValue(colors[0]);
    unsigned char blu = RGBGetBValue(colors[0]);
    controller->SetLogoColor(red, grn, blu);

    red = RGBGetRValue(colors[1]);
    grn = RGBGetGValue(colors[1]);
    blu = RGBGetBValue(colors[1]);
    controller->SetFanColor(red, grn, blu);

    red = RGBGetRValue(colors[2]);
    grn = RGBGetGValue(colors[2]);
    blu = RGBGetBValue(colors[2]);
    controller->SetRingColor(red, grn, blu);
}

void RGBController_AMDWraithPrism::UpdateZoneLEDs(int zone)
{
    RGBColor      color = colors[zone];
    unsigned char red   = RGBGetRValue(color);
    unsigned char grn   = RGBGetGValue(color);
    unsigned char blu   = RGBGetBValue(color);

    if(zone == 0)
    {
        controller->SetLogoColor(red, grn, blu);
    }
    else if(zone == 1)
    {
        controller->SetFanColor(red, grn, blu);
    }
    else if(zone == 2)
    {
        controller->SetRingColor(red, grn, blu);
    }
}

void RGBController_AMDWraithPrism::UpdateSingleLED(int led)
{
    UpdateZoneLEDs(led);
}

void RGBController_AMDWraithPrism::SetCustomMode()
{
    active_mode = 0;
}

void RGBController_AMDWraithPrism::DeviceUpdateMode()
{
    bool random = (modes[active_mode].color_mode == MODE_COLORS_RANDOM);

    controller->SetRingMode(modes[active_mode].value, modes[active_mode].speed, modes[active_mode].brightness, modes[active_mode].direction, random);

    switch(modes[active_mode].value)
    {
        case AMD_WRAITH_PRISM_EFFECT_CHANNEL_COLOR_CYCLE:
            controller->SetFanMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_COLOR_CYCLE, modes[active_mode].speed, modes[active_mode].brightness, random);
            controller->SetLogoMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_COLOR_CYCLE, modes[active_mode].speed, modes[active_mode].brightness, random);
            break;

        case AMD_WRAITH_PRISM_EFFECT_CHANNEL_RAINBOW:
        case AMD_WRAITH_PRISM_EFFECT_CHANNEL_BOUNCE:
            controller->SetFanMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_COLOR_CYCLE, modes[active_mode].speed, (modes[active_mode].brightness >> 1), random);
            controller->SetLogoMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_COLOR_CYCLE, modes[active_mode].speed, (modes[active_mode].brightness >> 1), random);
            break;
        
        case AMD_WRAITH_PRISM_EFFECT_CHANNEL_BREATHING:
            controller->SetFanMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_BREATHING, modes[active_mode].speed, modes[active_mode].brightness, random);
            controller->SetLogoMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_BREATHING, modes[active_mode].speed, modes[active_mode].brightness, random);
            break;

        default:
            if(random)
            {
                controller->SetFanMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_COLOR_CYCLE, modes[active_mode].speed, modes[active_mode].brightness, random);
                controller->SetLogoMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_COLOR_CYCLE, modes[active_mode].speed, modes[active_mode].brightness, random);
            }
            else
            {
                controller->SetFanMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_STATIC, modes[active_mode].speed, modes[active_mode].brightness, random);
                controller->SetLogoMode(AMD_WRAITH_PRISM_FAN_LOGO_MODE_STATIC, modes[active_mode].speed, modes[active_mode].brightness, random);
            }
            break;
    }

    DeviceUpdateLEDs();
}
