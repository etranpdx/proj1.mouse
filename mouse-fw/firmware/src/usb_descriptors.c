#include <string.h>
#include "tusb.h"
#include "usb_descriptors.h"

// VID/PID
#define USB_VID 0xCAFE      // Vendor ID, uniquely identifies maker of device
#define USB_PID 0x4001      // Product ID, uniquely identifies product from vendor
#define USB_BCD 0x0200      // Binary-coded decimal for USB version that the device speaks (USB 2.00)

// Device descriptor
tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),   // (1) size of this descriptor in bytes
    .bDescriptorType    = TUSB_DESC_DEVICE,             // (2) marks this as device descriptor
    .bcdUSB             = USB_BCD,                      // (3) USB specification version the device implements
    .bDeviceClass       = 0x00,                         // (4) device class (0 = no preset/check interface descriptors)
    .bDeviceSubClass    = 0x00,                         // (5) device subclass (unused when class = 0)
    .bDeviceProtocol    = 0x00,                         // (6) device protocol (unused when class = 0)
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,       // (7) max packet size for control endpont 0 (64 bytes)
    .idVendor           = USB_VID,                      // (8) Vendor ID - maker
    .idProduct          = USB_PID,                      // (9) Product ID - model/product
    .bcdDevice          = 0x0100,                       // (10) device version 1.00
    .iManufacturer      = 0x01,                         // (11) index of manufacturer string descriptor
    .iProduct           = 0x02,                         // (12) index of product string descriptor
    .iSerialNumber      = 0x03,                         // (13) index of serial number string descriptor
    .bNumConfiguration  = 0x01,                         // (14) number of configuration descriptor the device offers
}

// Callback TinyUSB calls to get address of device descriptor in bytes
uint8_t const * tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}



// HID Report Descriptor - byte array describing the format of mouse reports sent to host
uint8_t const desc_hid_report[] = {
// Macro builds sequence of bytes that teach the host the format of reports (buttons, X/Y, etc) + Report ID 1 = mouse
    TUD_HID_REPORT_DESC_MOUSE( HID_REPORT_ID(REPORT_ID_MOUSE) ),    
};

// Callback TinyUSB calls to get address of 'HID Report Descriptor' in bytes
uint8_t const * tud_hid_descriptor_report_cb(uint8_t instance) {
    (void)instance;
    return desc_hid_report;
}



enum { ITF_NUM_HID, ITF_NUM_TOTAL };   // Constants: 1st interface index 0 + only one interface
#define EPNUM_HID       0x81           // Define USB EP address: endpoint 1, IN (device -> host)
// Define total bytes of the config block (generic config header + HID interface/endpoint block)
#define CONFIG_TOTAL_LEN    (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

uint8_t const desc_configuration[] = {
    /* Config Number, Total Interfaces, 0 = no string, Total bytes of CONFIG + ITF + EP + HID descriptors, 
    Attributes - REMOTE_WAKEUP lets device signal wake up to host, Max Power in mA*/
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    /* Interface Number, 0 = no string, Mouse HID Protocol, Total bytes of HID report descriptor, EP IN address,
    EP max packet size, Poll Interval for 5 ms */
    TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_MOUSE, sizeof(desc_hid_report), EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 5),
};

// Callback TinyUSB calls to get address of 'Configuration Descriptor' - Config + ITF + HID Class + EP Descriptors
// CFG (#ofITF, total len, attribute, power), ITF (class, protocol), HID (HID Report len), EP (address, attributes, packet size, interval)
uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
    (void)index;
    return desc_configuration;
}



// Strings Data Table - array of pointers to C strings
static char const * string_desc_arr[] = {
    (const char[]){ 0x09, 0x04 },     // 0: English (0x0409)
    "etran"                           // 1: Manufacturer
    "Custom Optical Mouse",           // 2: Product
    "1234456",                        // 3: Serial Number
};

// UTF-16LE buffer for building USB string descriptor - reserves 32 elements array of 16 bit slots
static uint16_t _desc_str[32];

uint16_t const * tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
  (void) langid;
  uint8_t chr_count;

  if (index == 0) {
    memcpy(&_desc_str[1], string_desc_arr[0], 2);
    chr_count = 1;
  } else {
    if (index >= sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) return NULL;
    const char* str = string_desc_arr[index];
    chr_count = (uint8_t) strlen(str);
    if (chr_count > 31) chr_count = 31;
    for (uint8_t i = 0; i < chr_count; i++) _desc_str[1 + i] = str[i];
  }
  _desc_str[0] = (TUSB_DESC_STRING << 8) | (2*chr_count + 2);
  return _desc_str;
}

void usb_descriptor_init_id(void)