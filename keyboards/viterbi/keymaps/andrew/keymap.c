#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  Ins |   `  |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  | Bksp | Del  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   -  | Tab  |   Q  |   W  |   E  |   R  |   T  |      |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   =  | Esc  |   A  |   S  |   D  |   F  |   G  |      |   H  |   J  |   K  |   L  |   ;  |   "  |Enter |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Pg Up| Shift|   Z  |   X  |   C  |   V  |   B  |      |   N  |   M  |   ,  |   .  |   /  | Home | End  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Pg Dn|Adjust| Ctrl | Alt  | GUI  |Lower |Space |      |Space |Raise | Left | Down |  Up  | Right|   \  |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  , 6  ,      7  , 8  , 9  , 0  ,MINS,EQL ,DEL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     BSLS,TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,LBRC,RBRC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     ESC ,CAPS, A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,ENT ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     PGDN,LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,RSFT,PGUP,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     LCTL,LALT,LEFT,DOWN,LOWR,LGUI,BSPC,     SPC ,RGUI,RASE, UP ,RGHT,RALT,RCTL
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

/* Lower
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |   ~  |  F1  |  F3  |  F3  |  F4  |  F5  |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   _  |      |   !  |   @  |   #  |   $  |   %  |      |   ^  |   &  |   *  |   (  |   )  |   {  |   }  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   +  |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |  F6  |   _  |   +  |   {  |   }  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |  F12 |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
      NO , NO , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
      NO,  NO , NO , NO , NO , NO , NO ,      NO ,  , NO ,WH_U,WH_D, NO , NO ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
      NO , NO , NO , NO ,BTN2,BTN1, NO ,      NO ,MS_U,MS_D,MS_L,MS_R, NO , NO ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    , F7 , F8 , F9 ,F10 ,F11 ,     F12 ,  ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,VOLD,VOLU,MPLY,MUTE
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

/* Raise
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |   ~  |  F1  |  F3  |  F3  |  F4  |  F5  |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   _  |      |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   {  |   }  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   +  |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |  F6  |   -  |   =  |   [  |   ]  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |  F12 |ISO # |ISO / |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,TILD, F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     UNDS,    , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,LCBR,RCBR,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     PLUS,    , F1 , F2 , F3 , F4 , F5 ,      F6 ,MINS,EQL ,LBRC,RBRC,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    , F7 , F8 , F9 ,F10 ,F11 ,     F12 ,NUHS,NUBS,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,VOLD,VOLU,MPLY,MUTE
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
