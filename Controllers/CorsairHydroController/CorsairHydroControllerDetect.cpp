#include "Detector.h"
#include "CorsairHydroController.h"
#include "RGBController.h"
#include "RGBController_CorsairHydro.h"
#include <vector>
#ifdef __FreeBSD__
#include <libusb.h>
#else
#include <libusb-1.0/libusb.h>
#endif

/*-----------------------------------------------------*\
| Corsair vendor ID                                     |
\*-----------------------------------------------------*/
#define CORSAIR_VID                     0x1B1C

/*-----------------------------------------------------*\
| Keyboard Hydro Series product IDs                     |
\*-----------------------------------------------------*/
#define CORSAIR_H115I_PRO_RGB_PID       0x0C13
#define CORSAIR_H100I_PRO_RGB_PID       0x0C15
#define CORSAIR_H150I_PRO_RGB_PID       0x0C12

typedef struct
{
    unsigned short  usb_vid;
    unsigned short  usb_pid;
    unsigned char   usb_interface;
    const char *    name;
} corsair_hydro_device;

#define CORSAIR_NUM_DEVICES (sizeof(device_list) / sizeof(device_list[ 0 ]))

static const corsair_hydro_device device_list[] =
{
    /*-----------------------------------------------------------------------------------------------------*\
    | Coolers                                                                                               |
    \*-----------------------------------------------------------------------------------------------------*/
    { CORSAIR_VID,          CORSAIR_H100I_PRO_RGB_PID,          0,      "Corsair H100i PRO RGB"             },
    { CORSAIR_VID,          CORSAIR_H115I_PRO_RGB_PID,          0,      "Corsair H115i PRO RGB"             },
    { CORSAIR_VID,          CORSAIR_H150I_PRO_RGB_PID,          0,      "Corsair H150i PRO RGB"             },
};

/******************************************************************************************\
*                                                                                          *
*   DetectCorsairHydroControllers                                                          *
*                                                                                          *
*       Tests the USB address to see if a Corsair RGB Cooler controller exists there.      *
*                                                                                          *
\******************************************************************************************/

void DetectCorsairHydroControllers(std::vector<RGBController*>& rgb_controllers)
{
    libusb_init(NULL);

    #ifdef _WIN32
    libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);
    #endif

    for(std::size_t device_idx = 0; device_idx < CORSAIR_NUM_DEVICES; device_idx++)
    {
        libusb_device_handle * dev = libusb_open_device_with_vid_pid(NULL, device_list[device_idx].usb_vid, device_list[device_idx].usb_pid);

        //Look for Corsair RGB Peripheral
        if(dev)
        {
            libusb_detach_kernel_driver(dev, 0);
            libusb_claim_interface(dev, 0);

            CorsairHydroController*     controller     = new CorsairHydroController(dev);
            RGBController_CorsairHydro* rgb_controller = new RGBController_CorsairHydro(controller);

            rgb_controller->name = device_list[device_idx].name;
            
            rgb_controllers.push_back(rgb_controller);
        }
    }
}   /* DetectCorsairHydroControllers() */

REGISTER_DETECTOR("Corsair Hydro Series", DetectCorsairHydroControllers);
