// include/tusb_config.h
#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

// Chip/USB port
#define CFG_TUSB_MCU               OPT_MCU_RP2040
#define BOARD_DEVICE_RHPORT_NUM    0
#define BOARD_DEVICE_RHPORT_SPEED  OPT_MODE_FULL_SPEED
#define CFG_TUSB_OS                OPT_OS_NONE

// Control endpoint size
#define CFG_TUD_ENDPOINT0_SIZE     64

// ---- Enable only what we need for now ----
#define CFG_TUD_HID                1
#define CFG_TUD_CDC                0
#define CFG_TUD_MSC                0
#define CFG_TUD_MIDI               0
#define CFG_TUD_VENDOR             0

// HID endpoint buffer size
#define CFG_TUD_HID_EP_BUFSIZE     16

#endif