#ifndef LIVESAMPLE_H
#define LIVESAMPLE_H

#include "quantum.h"

#define LAYOUT_livesample_grid( \
	k00, k01, k02, \
	k03, k04, k05, \
	k06, k07, k08, \
	k09, k0a, k0b \
) \
{ \
	{ k00, k01, k02, }, \
	{ k03, k04, k05, }, \
	{ k06, k07, k08, }, \
	{ k09, k0a, k0b  }  \
}

// Used to create a keymap using only KC_ prefixed keys
#define KC_KEYMAP( \
	k00, k01, k02, \
	k03, k04, k05, \
	k06, k07, k08, \
	k09, k0a, k0b \
	) \
	LAYOUT_sample_grid( \
		KC_##k00, KC_##k01, KC_##k02, \
		KC_##k03, KC_##k04, KC_##k05, \
		KC_##k06, KC_##k07, KC_##k08, \
		KC_##k09, KC_##k0a, KC_##k0b \
    )

#define KEYMAP LAYOUT_livesample_grid
#define LAYOUT_ortho_4x3 LAYOUT_livesample_grid
#define KC_LAYOUT_ortho_4x3 KC_KEYMAP

#endif
