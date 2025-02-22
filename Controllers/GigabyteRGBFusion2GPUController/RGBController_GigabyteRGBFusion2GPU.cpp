/*-----------------------------------------*\
|  RGBController_GigabyteRGBFusion2GPU.cpp  |
|                                           |
|  Generic RGB Interface for OpenRGB        |
|  Gigabyte RGB Fusion2 GPU Driver          |
|                                           |
|  based on original by                     |
|  Adam Honse (CalcProgrammer1)             |
\*-----------------------------------------*/

#include "RGBController_GigabyteRGBFusion2GPU.h"

static const char* gigabyte_fusion2_gpu_zone[] =
{
    "gpu zone 1",
    "gpu zone 2",
    "gpu zone 3",
    "gpu zone 4"
};

RGBController_RGBFusion2GPU::RGBController_RGBFusion2GPU(RGBFusion2GPUController* controller_ptr)
{
    controller  = controller_ptr;

    name        = "Gigabyte GPU";
    vendor      = "Gigabyte";
    description = "Gigabyte RGB Fusion 2 GPU";
    location    = controller->GetDeviceLocation();

    type = DEVICE_TYPE_GPU;

    mode Direct;
    Direct.name                 = "Direct";
    Direct.value                = RGB_FUSION2_GPU_MODE_STATIC;
    Direct.flags                = MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_MANUAL_SAVE;
    Direct.color_mode           = MODE_COLORS_PER_LED;
    Direct.brightness_min       = RGB_FUSION2_GPU_BRIGHTNESS_MIN;
    Direct.brightness_max       = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    Direct.brightness           = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    modes.push_back(Direct);

    mode Breathing;
    Breathing.name              = "Pulse";
    Breathing.value             = RGB_FUSION2_GPU_MODE_BREATHING;
    Breathing.flags             = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_MANUAL_SAVE;
    Breathing.speed_min         = RGB_FUSION2_GPU_SPEED_SLOWEST;
    Breathing.speed_max         = RGB_FUSION2_GPU_SPEED_FASTEST;
    Breathing.speed             = RGB_FUSION2_GPU_SPEED_NORMAL;
    Breathing.color_mode        = MODE_COLORS_PER_LED;
    Breathing.brightness_min    = RGB_FUSION2_GPU_BRIGHTNESS_MIN;
    Breathing.brightness_max    = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    Breathing.brightness        = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    modes.push_back(Breathing);

    mode Flashing;
    Flashing.name               = "Flash";
    Flashing.value              = RGB_FUSION2_GPU_MODE_FLASHING;
    Flashing.flags              = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_MANUAL_SAVE;
    Flashing.speed_min          = RGB_FUSION2_GPU_SPEED_SLOWEST;
    Flashing.speed_max          = RGB_FUSION2_GPU_SPEED_FASTEST;
    Flashing.speed              = RGB_FUSION2_GPU_SPEED_NORMAL;
    Flashing.color_mode         = MODE_COLORS_PER_LED;
    Flashing.brightness_min     = RGB_FUSION2_GPU_BRIGHTNESS_MIN;
    Flashing.brightness_max     = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    Flashing.brightness         = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    modes.push_back(Flashing);

    mode DualFlashing;
    DualFlashing.name           = "Double Flash";
    DualFlashing.value          = RGB_FUSION2_GPU_MODE_DUAL_FLASHING;
    DualFlashing.flags          = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_MANUAL_SAVE;
    DualFlashing.speed_min      = RGB_FUSION2_GPU_SPEED_SLOWEST;
    DualFlashing.speed_max      = RGB_FUSION2_GPU_SPEED_FASTEST;
    DualFlashing.speed          = RGB_FUSION2_GPU_SPEED_NORMAL;
    DualFlashing.color_mode     = MODE_COLORS_PER_LED;
    DualFlashing.brightness_min = RGB_FUSION2_GPU_BRIGHTNESS_MIN;
    DualFlashing.brightness_max = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    DualFlashing.brightness     = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    modes.push_back(DualFlashing);

    mode SpectrumCycle;
    SpectrumCycle.name              = "Color Cycle";
    SpectrumCycle.value             = RGB_FUSION2_GPU_MODE_COLOR_CYCLE;
    SpectrumCycle.flags             = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS;;
    SpectrumCycle.speed_min         = RGB_FUSION2_GPU_SPEED_SLOWEST;
    SpectrumCycle.speed_max         = RGB_FUSION2_GPU_SPEED_FASTEST;
    SpectrumCycle.speed             = RGB_FUSION2_GPU_SPEED_NORMAL;
    SpectrumCycle.color_mode        = MODE_COLORS_NONE;
    SpectrumCycle.brightness_min    = RGB_FUSION2_GPU_BRIGHTNESS_MIN;
    SpectrumCycle.brightness_max    = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    SpectrumCycle.brightness        = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    modes.push_back(SpectrumCycle);

    mode Gradient;
    Gradient.name               = "Gradient";
    Gradient.value              = RGB_FUSION2_GPU_MODE_GRADIENT;
    Gradient.flags              = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_MANUAL_SAVE;
    Gradient.speed_min          = RGB_FUSION2_GPU_SPEED_SLOWEST;
    Gradient.speed_max          = RGB_FUSION2_GPU_SPEED_FASTEST;
    Gradient.speed              = RGB_FUSION2_GPU_SPEED_NORMAL;
    Gradient.color_mode         = MODE_COLORS_PER_LED;
    Gradient.brightness_min     = RGB_FUSION2_GPU_BRIGHTNESS_MIN;
    Gradient.brightness_max     = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    Gradient.brightness         = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    modes.push_back(Gradient);

    mode Wave;
    Wave.name                   = "Wave";
    Wave.value                  = RGB_FUSION2_GPU_MODE_WAVE;
    Wave.flags                  = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_MANUAL_SAVE;
    Wave.speed_min              = RGB_FUSION2_GPU_SPEED_SLOWEST;
    Wave.speed_max              = RGB_FUSION2_GPU_SPEED_FASTEST;
    Wave.speed                  = RGB_FUSION2_GPU_SPEED_NORMAL;
    Wave.color_mode             = MODE_COLORS_NONE;
    Wave.brightness_min         = RGB_FUSION2_GPU_BRIGHTNESS_MIN;
    Wave.brightness_max         = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    Wave.brightness             = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    modes.push_back(Wave);

    mode Shift;
    Shift.name                  = "Color Shift";
    Shift.value                 = RGB_FUSION2_GPU_MODE_COLOR_SHIFT;
    Shift.flags                 = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_MANUAL_SAVE; 
    Shift.speed_min             = RGB_FUSION2_GPU_SPEED_SLOWEST;
    Shift.speed_max             = RGB_FUSION2_GPU_SPEED_FASTEST;
    Shift.speed                 = RGB_FUSION2_GPU_SPEED_NORMAL;
    Shift.color_mode            = MODE_COLORS_MODE_SPECIFIC;
    Shift.colors_min            = 1;
    Shift.colors_max            = 8;
    Shift.colors.resize(8);
    Shift.brightness_min        = RGB_FUSION2_GPU_BRIGHTNESS_MIN;
    Shift.brightness_max        = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    Shift.brightness            = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    modes.push_back(Shift);

    mode Tricolor;
    Tricolor.name               = "Tricolor";
    Tricolor.value              = RGB_FUSION2_GPU_MODE_TRICOLOR;
    Tricolor.flags              = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_MANUAL_SAVE;
    Tricolor.speed_min          = RGB_FUSION2_GPU_SPEED_SLOWEST;
    Tricolor.speed_max          = RGB_FUSION2_GPU_SPEED_FASTEST;
    Tricolor.speed              = RGB_FUSION2_GPU_SPEED_NORMAL;
    Tricolor.color_mode         = MODE_COLORS_MODE_SPECIFIC;
    Tricolor.colors.resize(3);
    Tricolor.brightness_min     = RGB_FUSION2_GPU_BRIGHTNESS_MIN;
    Tricolor.brightness_max     = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    Tricolor.brightness         = RGB_FUSION2_GPU_BRIGHTNESS_MAX;
    modes.push_back(Tricolor);
    SetupZones();
}

RGBController_RGBFusion2GPU::~RGBController_RGBFusion2GPU()
{
    delete controller;
}

uint8_t RGBController_RGBFusion2GPU::getModeIndex(uint8_t mode_value)
{
    for (uint8_t mode_index = 0; mode_index < modes.size(); mode_index++)
    {
        if (modes[mode_index].value == mode_value)
        {
            return mode_index;
        }
    }
    return 0;
}

void RGBController_RGBFusion2GPU::SetupZones()
{
    /*---------------------------------------------------------*\
    | This device only allows setting the entire zone for all   |
    | LED's in the zone and does not allow per LED control.     |
    \*---------------------------------------------------------*/

    //controller->GetDeviceModes();

    for(uint8_t zone_idx = 0; zone_idx < 4; zone_idx++)
    {
        if(controller->zone_led_count[zone_idx] > 0)
        {
            zone* new_zone = new zone();
            led*  new_led  = new led();

            new_zone->name          = gigabyte_fusion2_gpu_zone[zone_idx];
            new_zone->type          = ZONE_TYPE_SINGLE;
            new_zone->leds_min      = controller->zone_led_count[zone_idx];
            new_zone->leds_max      = new_zone->leds_min;
            new_zone->leds_count    = new_zone->leds_min;
            new_zone->matrix_map    = NULL;

            new_led->name           = gigabyte_fusion2_gpu_zone[zone_idx];
            /*---------------------------------------------------------*\
            | Push the zone and LED on to device vectors                |
            \*---------------------------------------------------------*/
            leds.push_back(*new_led);
            zones.push_back(*new_zone);
            zoneIndexMap.push_back(zone_idx);
        }
    }
    SetupColors();
}

void RGBController_RGBFusion2GPU::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_RGBFusion2GPU::DeviceUpdateLEDs()
{
    fusion2_config zone_config;

    zone_config.brightness = modes[active_mode].brightness;
    zone_config.speed = modes[active_mode].speed;
    zone_config.direction = modes[active_mode].direction;
    zone_config.numberOfColors = (uint8_t)modes[active_mode].colors.size();

    for (uint8_t zone_idx = 0; zone_idx < zoneIndexMap.size(); zone_idx++)
    {
        zone_config.colors[0] = colors[zone_idx];

        if (modes[active_mode].color_mode == MODE_COLORS_MODE_SPECIFIC)
        {
            for (uint8_t i = 0; i < zone_config.numberOfColors; i++)
            {
                zone_config.colors[i] = modes[active_mode].colors[i];
            }
        }

        controller->SetZone(zoneIndexMap[zone_idx], modes[active_mode].value, zone_config);
    }
}

void RGBController_RGBFusion2GPU::UpdateZoneLEDs(int zone)
{
    DeviceUpdateLEDs();
}

void RGBController_RGBFusion2GPU::UpdateSingleLED(int led)
{
    DeviceUpdateLEDs();
}

void RGBController_RGBFusion2GPU::SetCustomMode()
{
    active_mode = 0;
}

void RGBController_RGBFusion2GPU::DeviceUpdateMode()
{
    DeviceUpdateLEDs();
}

void RGBController_RGBFusion2GPU::DeviceSaveMode()
{
    controller->SaveConfig();
}
