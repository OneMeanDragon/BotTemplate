#ifndef _MCOLORS_H
#define _MCOLORS_H

#include "includes.h"

namespace Common
{

	enum DefColors {
		BLACK = 0x000000L,
		WHITE = 0xffffffL,
		RED = 0x0000eeL,
		BLUE = 0xCD5F3AL,
		GREEN = 0x008000L,
		YELLOW = 0x00CDCDL,
		DEEPPURPLE = 0xDB7093L,
		SILVER = 0xc0c0c0L,
		LIME = 0x00ff00L,
		SEAGREEN = 0x32CD32L,
		GRAY = 0x808080L,
		DARKSLATEGRAY = 0x2F4F4FL,
		OLIVE = 0x008080L,
		MAROON = 0x000080L,
		NAVY = 0x800000L,
		PURPLE = 0x800080L,
		TEAL = 0x808000L,
		FUCHSIA = 0xff00ffL,
		AQUA = 0xffff00L
	};

	COLORREF ColorByName(const char* cname);

}

#endif
