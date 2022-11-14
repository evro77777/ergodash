#include QMK_KEYBOARD_H
bool is_alt_tab_active = false;
bool is_win_active = false;
uint16_t alt_tab_timer = 0;
uint16_t win_timer = 0; 
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _APPS 4
#define CTL_ENT     CTL_T(KC_ENT)               // Tap for Enter, hold for Ctrl
#define OSMLSFT OSM(MOD_LSFT)
enum combos {
	CUT,
	CTRLBSP,
	WINGUI
};
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  APPS,
  TD_ESC_GRV=0,
  TD_J_RPRN=1,	
  TD_K_LPRN=2,
  ALT_TAB,
  WIN
};
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
  [TD_J_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_RPRN),
  [TD_K_LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_LPRN),

  
};

const uint16_t PROGMEM cut_combo[] = {LCTL(KC_C), LCTL(KC_V), COMBO_END};
const uint16_t PROGMEM ctrlbsp_combo[] = {KC_TAB, KC_BSPC, COMBO_END};
const uint16_t PROGMEM wingui_combo[] = {KC_LALT, KC_LCTL, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    [CUT] = COMBO(cut_combo, LCTL(KC_X)),
	[CTRLBSP] = COMBO(ctrlbsp_combo, LCTL(KC_BSPC)),
	[WINGUI] = COMBO(wingui_combo, KC_LGUI),
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |  1   |  2   |  3   | 4    |  5   | del  |                    |vup   |  6   | 7    | 8    |   9  | 0    | ctrlZ|
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | tab  |   Q  |   W  |   E  |   R  |   T  |copy  |                    |vdown |   Y  |   U  |   I  |   O  |   P  |  [   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | bsp  |   A  |   S  |   D  |   F  |   G  | paste|                    | mute |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |   Z  |   X  |   C  |   V  |   B  ||||||||  alt |      |      ||||||||   N  |   M  |   ,  |   .  |   /  | ?   |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |space |      |      |  lang||||||||Lower | Shift| ctrl ||||||| | Enter|space |Raise ||||||| W_C_L| W_C_R  |  ]  |     |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( 
     TD(TD_ESC_GRV),   KC_1,       KC_2,    KC_3,           KC_4,    KC_5,   KC_DEL,                                         KC_VOLU,          KC_6,             KC_7,                KC_8,                KC_9,    KC_0,       LCTL(KC_Z),
     KC_TAB,           KC_Q,       KC_W,    KC_E,           KC_R,    KC_T,   LCTL(KC_C),                                     KC_VOLD,          KC_Y,             KC_U,                KC_I,                KC_O,    KC_P,       KC_LBRC,
     KC_BSPC,          KC_A,       KC_S,    KC_D,           KC_F,    KC_G,   LCTL(KC_V),                                     KC_MUTE,          KC_H,             KC_J,                KC_K,                KC_L,    KC_SCLN,    KC_QUOT,
     XXXXXXX,          KC_Z,       KC_X,    KC_C,           KC_V,    KC_B,               KC_LALT,                XXXXXXX,                 KC_N,             KC_M,                KC_COMM,             KC_DOT,  KC_SLSH,    KC_QUES,
     KC_SPC,           XXXXXXX,    XXXXXXX, LGUI(KC_SPC),   LT(1,KC_ENT),      OSMLSFT,  KC_LCTL ,               KC_ENT,               KC_SPC,        RAISE,    LGUI(LCTL(KC_LEFT)), LGUI(LCTL(KC_RGHT)),          KC_RBRC,    XXXXXXX
  ),


  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |   (  | )    |      |      |                    |      |      |   }  |  {   |      |      |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Raise|   1  |  2   |  3   |  4   |   5  |      |                    |      |  6   | 7    |  8   |   9  |   0  |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|      |      |tb_lft|tb_rgt| winT ||||||||      |      |      ||||||||    - |   +  |    = |   _  |   \  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      |||||||| Lower| Space|  Entr|||||||| entr | shift|  bsp ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT( 
    XXXXXXX,  KC_F1,     KC_F2,   KC_F3,              KC_F4,            KC_F5,      XXXXXXX,                         XXXXXXX,  KC_F6,         KC_F7,          KC_F8,         KC_F9,           KC_F10,         KC_F11, 
    XXXXXXX, XXXXXXX,    XXXXXXX, KC_LPRN,            KC_RPRN,          XXXXXXX,    XXXXXXX,                         XXXXXXX,  XXXXXXX,       KC_RCBR,        KC_LCBR,       XXXXXXX,         XXXXXXX,        KC_F12,
      RAISE, KC_1 ,      KC_2,    KC_3,               KC_4,             KC_5,       XXXXXXX,                         XXXXXXX,  KC_6,          KC_7,           KC_8,          KC_9,            KC_0,           XXXXXXX,
    KC_LSFT, XXXXXXX,    XXXXXXX, LCTL(KC_PGUP),      LCTL(KC_PGDOWN),  LGUI(KC_T),              XXXXXXX,      XXXXXXX,           KC_MINS,       KC_PLUS,        KC_EQUAL,      KC_UNDERSCORE,   KC_BSLS,        KC_RSFT,
    XXXXXXX, XXXXXXX,    XXXXXXX, LCTL(LALT(LSFT(KC_L))),            LOWER,            KC_SPC ,              KC_ENT,       KC_ENT, KC_RSFT ,  KC_BSPC,                       XXXXXXX  ,     XXXXXXX,        XXXXXXX,         XXXXXXX 
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |  C_L |  C_R |      |      |                    |      |      | home | pgup | pgdwn| end  |      |      
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Raise|      |      | C_S_L|C_S_R |      |      |                    |      |  app | left |  up  |down  |right |      | 
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|      |      |      |      |      ||||||||  win |      |      ||||||||      |C_Home|      |      | C_End| Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      |||||||| Lower| Space|Entr  ||||||||Entr  |shift | bsp  ||||||||Raise |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,             XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX,          XXXXXXX,       XXXXXXX,       XXXXXXX,             XXXXXXX,      XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, LCTL(KC_LEFT),             LCTL(KC_RGHT),       XXXXXXX, XXXXXXX,                        XXXXXXX, RCTL(KC_SLSH),    KC_HOME,       KC_PGUP,       KC_PGDOWN,           KC_END,       XXXXXXX,
      RAISE, XXXXXXX, XXXXXXX, LCTL(LSFT(KC_LEFT)),       LCTL(LSFT(KC_RGHT)), XXXXXXX, XXXXXXX,                        XXXXXXX, KC_APP,           KC_LEFT,       KC_UP  ,       KC_DOWN,             KC_RGHT,      XXXXXXX,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,             XXXXXXX,              XXXXXXX,     XXXXXXX,       XXXXXXX,          LCTL(KC_HOME), XXXXXXX,       XXXXXXX,             LCTL(KC_END), XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   LOWER,               KC_SPC , KC_LCTL,     KC_ENT,      KC_RSFT ,      KC_BSPC,          RAISE, XXXXXXX, XXXXXXX,      XXXXXXX 
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
  ),
    /* APPS  
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      | win1 | win2 | win3 | win4 |win5  |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   *|       |      |      |      |      |      ||||||||      |      |      ||||||||      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
    [_APPS] = LAYOUT(
      RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RAISE, LGUI(KC_1),   LGUI(KC_2), LGUI(KC_3), LGUI(KC_4),  LGUI(KC_5), XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,           XXXXXXX,     XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
    XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,             LOWER,   XXXXXXX ,XXXXXXX,     XXXXXXX,  XXXXXXX,   XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
	case APPS:
      if (record->event.pressed) {
        layer_on(_APPS);
      } else {
        layer_off(_APPS);
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
  };

}



