#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0001
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    Microsoft Wired Keyboard
#define PRODUCT         Microsoft Wired Keyboard
#define DESCRIPTION     Microsoft Wired Keyboard

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* key matrix pins */
#define MATRIX_ROW_PINS { B5 }
#define MATRIX_COL_PINS { D7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW




#endif