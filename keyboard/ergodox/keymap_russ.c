#include <util/delay.h>
#include "bootloader.h"
#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default Layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |   ESC  |   1  |   2  |   3  |   4  |   5  |   \  |           |   -  |   6  |   7  |   8  |   9  |   0  |   =    |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   [    |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * | Shift  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * | LCtrl  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |   ]    |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |  L1  |      |      | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L1  |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       | VolD | VolU |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       | MUTE |      |      |
   *                                 | BkSp |  ESC |------|       |------| Enter| Space|
   *                                 |      |      |      |       | PLAY |      |      |
   *                                 `--------------------'       `--------------------'
   *
   */

  KEYMAP(
    // left hand
    ESC,  1,   2,   3,   4,   5,   BSLS,
    TAB,  Q,   W,   E,   R,   T,   NO,
    LCTL, A,   S,   D,   F,   G,
    LSFT, Z,   X,   C,   V,   B,   NO,
    FN2,  NO,  NO,  LALT, LGUI,
                                  MPRV, MNXT,
                                        NO,
                             BSPC, ESC, GRV,

    // right hand
         MINS, 6,   7,    8,    9,    0,    EQL,
         NO,   Y,   U,    I,    O,    P,    LBRC,
               H,   J,    K,    L,    SCLN, QUOT,
         NO,   N,   M,    COMM, DOT,  SLSH, RBRC,
                    LEFT, UP,   DOWN, RGHT, NO,
    VOLD, VOLU,
    MUTE,
    MPLY, ENT, SPC
  ),

  /* Layer 1: Numpad
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * | Teensy |      |      |      |      |      |      |           |      |      |Num.Lk|      |   /  |   -  |        |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |           |      |      |  N7  |  N8  |  N9  |   *  |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |------|           |------|      |  N4  |  N5  |  N6  |   +  |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |           |      |      |  N1  |  N2  |  N3  | Enter|        |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |  L0  |      |      |      |      |                                       |  N0  |  N0  |   .  | Enter|      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |      |      |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       |      |      |      |
   *                                 | BkSp | ESC  |------|       |------| Enter| Space|
   *                                 |      |      |      |       |      |      |      |
   *                                 `--------------------'       `--------------------'
   */

  KEYMAP(
    // Left Hand
    FN31,  NO,  NO,  NO,  NO,  NO,  NO,
      NO,  NO,  NO,  NO,  NO,  NO,  NO,
      NO,  NO,  NO,  NO,  NO,  NO,
      NO,  NO,  NO,  NO,  NO,  NO,  NO,
      FN0, NO,  NO,  NO,  NO,
                                  NO, NO,
                                      NO,
                           BSPC, ESC, NO,
    // Right Hand
       NO,  NO,  NO,  NO,   SLSH, MINS, NO,
       NO,  NO,  7,   8,    9,    PAST, NO,
            NO,  4,   5,    6,    EQL,  NO,
       NO,  NO,  1,   2,    3,    ENT,  NO,
                 0,   0,    PDOT, ENT,  NO,
    NO, NO,
    NO,
    NO, ENT, SPC
  ),
};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
};

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    // Layer shifting
    [0] = ACTION_LAYER_SET(0, ON_PRESS),           // Switch to Layer 0
    [1] = ACTION_LAYER_MOMENTARY(1),               // Momentarily switch to layer 1
    [2] = ACTION_LAYER_SET(1, ON_PRESS),           // Switch to Layer 2

    // Teensy
    [31] = ACTION_FUNCTION(TEENSY_KEY),
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}

