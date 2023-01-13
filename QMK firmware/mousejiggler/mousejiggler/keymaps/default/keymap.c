#include "mousejiggler.h" 

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  MOUSEJIGGLERMACRO
};


bool mouse_jiggle_mode = false;
int counter;
int c1;
int c2;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		MOUSEJIGGLERMACRO)

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
    // if (mouse_jiggle_mode) { //Uncomment if you want to add a physical toggle switch to control it via the macro
  SEND_STRING(SS_DELAY(10000));
  tap_code(KC_MS_UP);
  tap_code(KC_MS_DOWN);
  SEND_STRING(SS_DELAY(30000));
  tap_code(KC_MS_LEFT);
  tap_code(KC_MS_RIGHT);
  //} else { //Uncomment if you want to add a physical toggle switch to control it via the macro
  // } //Uncomment if you want to add a physical toggle switch to control it via the macro
  
  // //The purpose of the counter is to try and randomize the movements.
  // counter = counter + 1;
  // SEND_STRING(SS_DELAY(1));
  // c1 = counter % 13;
  // c2 = counter % 37;
  // if (c1 == 0) {
  //   SEND_STRING(SS_DELAY(10000));
  //   tap_code(KC_MS_UP);
  //   tap_code(KC_MS_DOWN);
  // }
  // if (c2 == 0) {
  //   SEND_STRING(SS_DELAY(30000));
  //   tap_code(KC_MS_LEFT);
  //   tap_code(KC_MS_RIGHT);
  // }
  // if (counter == 1000) {
  //   counter = 0;
  // }


}


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

    /*    SEND_STRING("1");
    tap_code(KC_MS_BTN1);
    tap_code(KC_MS_BTN1);
    SEND_STRING(SS_LCTL("c"));
    tap_code(KC_RIGHT);
    SEND_STRING(SS_LCTL("v"));
    SEND_STRING("yaughtyaughtyaught");
    tap_code(KC_MS_BTN1);
    tap_code(KC_MS_BTN1);
    tap_code(KC_MS_BTN1);*/