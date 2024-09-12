#include QMK_KEYBOARD_H
#include <stdio.h>

enum layers {
    _DEFAULT,
    _VALORANT,
    _GENSHIN
};

static uint8_t current_layer = _DEFAULT;

void cycle_layers(void) {
    // Increment the layer
    current_layer++;
    if (current_layer > _GENSHIN) {
        current_layer = _DEFAULT;
    }
    layer_move(current_layer);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DEFAULT] = LAYOUT(
         
                          KC_1,  KC_2,  KC_3,    KC_4, 
        KC_ESC,  KC_CAPS, KC_Q,  KC_W,  KC_E,    KC_R,
        KC_TAB,  KC_LSFT, KC_A,  KC_S,  KC_D,    KC_F,  
        KC_LGUI, KC_LALT, KC_Z,  KC_X,  KC_C,    KC_V,  KC_SPC,
                                        KC_LCTL, KC_LSFT
                                                        ),



[_VALORANT] = LAYOUT(
         
                           KC_1,  KC_2,  KC_3,    KC_4, 
        KC_ESC,   KC_CAPS, KC_Q,  KC_W,  KC_E,    KC_R,
        KC_B,     KC_LSFT, KC_A,  KC_S,  KC_D,    KC_F,  
        QK_LOCK,  KC_LCTL, KC_Z,  KC_X,  KC_C,    KC_V,  KC_SPC,
                                         KC_LSFT, KC_LCTL
                                                        ),



[_GENSHIN] = LAYOUT(
         
                          KC_2,  KC_NO,  KC_5,    KC_T, 
        KC_ESC,  KC_1,    KC_2,  KC_W,   KC_3,    KC_R,
        KC_TAB,  KC_LSFT, KC_A,  KC_S,   KC_D,    KC_F,  
        KC_L,   KC_LALT, KC_Z,  KC_X,   KC_C,    KC_V,  KC_SPC,
                                         KC_LCTL, KC_4
                                                        )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_esc_pressed = false;

    if (record->event.pressed) {
        if (keycode == KC_ESC) {
            is_esc_pressed = true;
        }
        if (keycode == KC_SPC && is_esc_pressed) {
            cycle_layers();
            wait_ms(200);
            return false;
        }
    } else {
        if (keycode == KC_ESC) {
            is_esc_pressed = false;
        }
    }
    return true;
}

#ifdef OLED_ENABLE

bool oled_task_user() {
    oled_set_cursor(0,1);
    oled_write("hello nyan", false);
    return false;
}

#endif
