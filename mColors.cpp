#include "mColors.h"

namespace Common
{

	COLORREF ColorByName(std::string name)
	{
		if (name == "black") { return 0x000000L; }
		if (name == "green") { return 0x008000L; }
		if (name == "silver") { return 0xc0c0c0L; }
		if (name == "lime") { return 0x00ff00L; }
		if (name == "seagreen") { return 0x32CD32L; } //seagreen 0x80CD43L 65B0161C
		if (name == "gray") { return 0x808080L; }
		if (name == "darkslategray") { return 0x2F4F4FL; }
		if (name == "olive") { return 0x008080L; }
		if (name == "white") { return 0xffffffL; }
		if (name == "yellow") { return 0x00CDCDL; } //Yellow //old 0x00ffffL //gold3 0x00ADCDL
		if (name == "maroon") { return 0x000080L; }
		if (name == "navy") { return 0x800000L; }
		if (name == "red") { return 0x0000eeL; }
		if (name == "blue") { return 0xCD5F3AL; } //Blue //0xCD5F3AL //old 0xff0000L (to much blur on a black background)
		if (name == "purple") { return 0x800080L; }
		if (name == "teal") { return 0x808000L; }
		if (name == "fuchsia") { return 0xff00ffL; }
		if (name == "aqua") { return 0xffff00L; }
		if (name == "deeppurple") { return 0xDB7093L; }
		//else no color was found default black
		return (COLORREF)(0x000000L);
	}

}
