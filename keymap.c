#include QMK_KEYBOARD_H
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0; 
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define CTL_ENT     CTL_T(KC_ENT)               // Tap for Enter, hold for Ctrl
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  TD_ESC_GRV=0,
  TD_J_RPRN=1,
  TD_K_LPRN=2,
  ALT_TAB
};
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
  [TD_J_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_RPRN),
  [TD_K_LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_LPRN)
  
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |  1   |  2   |  3   | 4    |  5   |      |                    |vup   |  6   | 7    | 8    |   9  | 0    |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |  Tab |   Q  |   W  |   E  |   R  |   T  |KC_BRK|                    |vdown |   Y  |   U  |   I  |   O  |   P  |  [   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | alt  |   A  |   S  |   D  |   F  |   G  |   `  |                    | mute |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | !    |   Z  |   X  |   C  |   V  |   B  |||||||| lgui |      |ALT_TB||||||||   N  |   M  |   ,  |   .  |   /  | ?    |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      | del  | enter|  lang||||||||Lower| Space| ctrl ||||||| | Enter|shift |BspRse|||||||| W_C_L| W_C_R|  ]   | Rctrl|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( 
     TD(TD_ESC_GRV),   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   XXXXXXX,                       KC_VOLU, KC_6,    KC_7,     KC_8,    KC_9,    KC_0,       XXXXXXX,
     KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_BRK,                        KC_VOLD, KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,       KC_LBRC,
     KC_LALT,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_GRV,                        KC_MUTE, KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN,    KC_QUOT,
     KC_EXLM,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                    KC_LGUI,     ALT_TAB,  KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH,    KC_QUES,
     XXXXXXX,          XXXXXXX,  XXXXXXX,  LGUI(KC_SPC),   LT(1,KC_DEL),  KC_SPC,  CTL_ENT ,     KC_ENT , OSM(MOD_LSFT), LT(2,KC_BSPC),    LGUI(LCTL(KC_LEFT)), LGUI(LCTL(KC_RGHT)), KC_RBRC,    KC_RCTL
  ),


  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |   (  | )    |      |      |                    |      |      |   }  |  {   |      |      |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Raise|   1  |  2   |  3   |  4   |   5  |      |                    |      |  6   | 7    |  8   |   9  |   0  |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|      |      |      |      |      ||||||||      |      |      ||||||||    - |   +  |    = |   _  |   \  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      |||||||| Lower| Space|  Entr|||||||| entr | shift|  bsp ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT( 
    XXXXXXX,  KC_F1,     KC_F2,   KC_F3,              KC_F4,     KC_F5,      XXXXXXX,                         XXXXXXX,  KC_F6,         KC_F7,          KC_F8,         KC_F9,           KC_F10,         KC_F11, 
    XXXXXXX, XXXXXXX,    XXXXXXX, KC_LPRN,            KC_RPRN,   XXXXXXX,    XXXXXXX,                         XXXXXXX,  XXXXXXX,       KC_RCBR,        KC_LCBR,       XXXXXXX,         XXXXXXX,        KC_F12,
      RAISE, KC_1 ,      KC_2,    KC_3,               KC_4,      KC_5,       XXXXXXX,                         XXXXXXX,  KC_6,          KC_7,           KC_8,          KC_9,            KC_0,           XXXXXXX,
    KC_LSFT, XXXXXXX,XXXXXXX, XXXXXXX,           XXXXXXX,   XXXXXXX,              XXXXXXX,      XXXXXXX,           KC_MINS,       KC_PLUS,        KC_EQUAL,      KC_UNDERSCORE,   KC_BSLS,        KC_RSFT,
    XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,                        LOWER,     KC_SPC ,  KC_ENT,       KC_ENT, KC_RSFT ,  KC_BSPC,       XXXXXXX  ,     XXXXXXX,        XXXXXXX,         XXXXXXX 
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |  C_L |  C_R |      |      |                    |      |      | home | pgup | pgdwn| end  |      |      
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Raise|      |      | C_S_L|C_S_R |      |      |                    |      |  app | left |  up  |down  |right |      | 
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|      |      |      |      |      ||||||||  win |      |      ||||||||      |  C_L | C_R  |C_S_L | C_S_R| Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      |||||||| Lower| Space|Entr  ||||||||Entr  |shift | bsp  ||||||||Raise |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,                      XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,             XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, LCTL(KC_LEFT),             LCTL(KC_RGHT),                XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, KC_HOME,       KC_PGUP,       KC_PGDOWN,           KC_END, XXXXXXX,
      RAISE, XXXXXXX, XXXXXXX, LCTL(LSFT(KC_LEFT)),       LCTL(LSFT(KC_RGHT)),          XXXXXXX, XXXXXXX,                        XXXXXXX, KC_APP, KC_LEFT,       KC_UP  ,       KC_DOWN,             KC_RGHT, XXXXXXX,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,    KC_LGUI,           XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   LOWER,   KC_SPC ,KC_LCTL,     KC_ENT, KC_RSFT ,  KC_BSPC,          RAISE, XXXXXXX, XXXXXXX, XXXXXXX 
  ),

  /* Adjust  (Both Raise and Lower Together)
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | Reset|      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      | cycle|rgbtog|bl_tog|      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Raise|      |rgbhui|rgbsai|rgbvai|bl_inc|      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   *|EEP_RST|      |rgbhud|rgbdec|rgbvad|bl_dec||||||||      |      |      ||||||||      |      |      |      |      | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      |||||||| Lower| Space|      ||||||||      | Space| Raise||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
      RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_TOG, BL_TOGG, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RAISE, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI,  BL_INC, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    EEP_RST, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD,  BL_DEC,           XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
    XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,             LOWER,   KC_SPC ,XXXXXXX,     XXXXXXX,  KC_SPC,   RAISE,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
}; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
	
	break;
    case ALT_TAB:
	if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    }//end switch
  return true;
}//end function

void matrix_scan_user(void) { 
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 500) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }  
}



