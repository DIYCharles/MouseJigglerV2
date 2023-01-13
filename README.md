MouseJiggler V2
=========

This is a build of a HID emulating device that will continuously move the mouse to keep the computer from sleeping as well as preserve the online status of applications. It uses an Arduino Pro Micro and QMK Firmware. 

### New Features
This second version has no buttons and will always run when plugged in. The new code makes it so the movements are so small that you can use your computer with the MouseJiggler running and it is impossible to notice.

[Here is a link to V1 with a physical toggle switch instead of always on](https://github.com/DIYCharles/MouseJiggler)

<!-- ![alt text](https://raw.githubusercontent.com/DIYCharles/MouseJigglerV2/main/photos/pic4.JPG "img3.jpg") -->

 <img src="https://raw.githubusercontent.com/DIYCharles/MouseJigglerV2/main/photos/pic4.JPG" style="max-width:49%;" />  <img src="https://raw.githubusercontent.com/DIYCharles/MouseJigglerV2/main/photos/pic3.JPG" style="max-width:49%;" />


Table of contents
=================

<!--ts-->
   * [Why](#Why)
   * [Build](#Build)
   * [QMK Firmware](#QMK-Firmware)
   * [Randomizing Input work in progress](#Randomizing-Input-work-in-progress)
   * [Compile And Flash](#Compile-And-Flash)
<!--te-->

Why
============
Q: Why not just use a shell script, ahk, or an existing program to do this? </br>

A: Some people do not have the ability to run scripts as cmd and powershell is blocked on their computers. Also IT may be monitoring or blocking additional programs added to the computer without approval. If you don't have these issues I strongly suggest mousejiggler or caffeine.

Q: Why not just buy a premade mouse mover usb dongle online? </br>

A: All USB products have hardware identification parameters so they can show up as a suspect usb device. With this solution you can spoof all the device identification parameters and it is recognized as a generic keyboard. For all intents and purposes after it is flashed it is a keyboard and acts exactly like it. 


QMK Firmware
============

The important part of this project is the code as it can be added to any other keyboard using QMK. All the code can be found in the [MouseJigglerV2/QMK firmware/mousejiggler/mousejiggler/](https://github.com/DIYCharles/MouseJigglerV2/tree/main/QMK%20firmware/mousejiggler/mousejiggler) folder. Also in there I a premade hex you can use in [MouseJigglerV2/QMK firmware/](https://github.com/DIYCharles/MouseJigglerV2/blob/main/QMK%20firmware/mousejiggler_mousejiggler_minimalauto.hex) if you just want to copy the project exactly or don't want to learn QMK.

 Here's a quick breakdown of the code

 This code works on a by piggybacking onto a mostly unused function that scans the keyboard repetitively on a loop. By placing macro commands in this function we are able to run commands on loop continuously. In the code below I have commented out the if statement that checks a boolean set to true normally when a macro is pressed and held down (toggle switch flipped to on) then back to false when it is released. That allows a macro to execute commands continuously where as the normal functionality of a macro is one set of commands per a press. By commenting out the if statement the commands are always running when plugged in.  
```c
void matrix_scan_user(void) {
  // if (mouse_jiggle_mode) { //Uncomment if you want to add a physical toggle switch to control it via the macro
  SEND_STRING(SS_DELAY(10000)); //10s
  tap_code(KC_MS_UP);
  tap_code(KC_MS_DOWN);
  SEND_STRING(SS_DELAY(30000)); //30s
  tap_code(KC_MS_LEFT);
  tap_code(KC_MS_RIGHT);
  // } else {
  // }
}
```

 ### *NOTE In version 2 I included the functionality of a physical toggle switch but disabled it by commenting out the if statement looking for the boolean that is set by the micro. This way the mousejiggle function will always run regardless of the macro. [If you would like to use that check out the original version](https://github.com/DIYCharles/MouseJiggler). That guide has the guide for wiring the switch too.*
 

Here I declare the macro MOUSEJIGGLERMACRO and then I put it where I want it on the keymap. Since this is just a 1x1 board it is the only key. 
```c
 enum custom_keycodes {
  MOUSEJIGGLERMACRO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	KEYMAP(
		MOUSEJIGGLERMACRO)
};
```
Here I set a value mouse_jiggle_mode to false
```c
bool mouse_jiggle_mode = false;
```
Here is where the macro is registered. When the switch is down or closed the value of mouse_jiggle_mode is set to true. When it is released it is set back to false.
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MOUSEJIGGLERMACRO:
      if (record->event.pressed) {
        mouse_jiggle_mode = true;
      } else {
        mouse_jiggle_mode = false;
      }
      break;
  }
  return true;
}
```

Randomizing Input work in progress
=====
Currently trying to find a way to randomize the code. My thoughts are to use a counter and only execute that code when the counter is divisable by small prime numbers. If anyone wants to help please do.
```c
int counter;
int c1;
int c2;

void matrix_scan_user(void) {
  //The purpose of the counter is to try and randomize the movements. If you do not want random movements comment this out and uncomment the part out below. 
  counter = counter + 1;
  SEND_STRING(SS_DELAY(1));
  c1 = counter % 13;
  c2 = counter % 37;
  if (c1 == 0) {
    SEND_STRING(SS_DELAY(10000));
    tap_code(KC_MS_UP);
    tap_code(KC_MS_DOWN);
  }
  if (c2 == 0) {
    SEND_STRING(SS_DELAY(30000));
    tap_code(KC_MS_LEFT);
    tap_code(KC_MS_RIGHT);
  }
  if (counter == 1000) {
    counter = 0;
  }
}
```


Compile And Flash
=====
I put a guide for this in my other repo [here](https://github.com/DIYCharles/DIYKeyboards) 

Build
============

The pro-micro I am using has a USB type C port and I got it for $5 on aliexpress. This code works on all pro micro 5V boards regardless of ports.

The 3D printing files for the case are incredibly thin and are designed for the type c pro micro. 
 <img src="https://raw.githubusercontent.com/DIYCharles/MouseJigglerV2/main/photos/pic1.JPG" style="max-width:49%;" /> <img src="https://raw.githubusercontent.com/DIYCharles/MouseJigglerV2/main/photos/pic2.JPG" style="max-width:49%;" />