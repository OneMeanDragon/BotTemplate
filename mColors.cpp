#include "mColors.h"

namespace Common
{

	COLORREF ColorByName(const char* cname)
	{
		std::string name = std::string(cname);
		//Most common colors up top.
		if (name == "black")			{ return (COLORREF)0x000000L; }
		if (name == "white")			{ return (COLORREF)0xffffffL; }
		if (name == "red")				{ return (COLORREF)0x0000eeL; }
		if (name == "blue")				{ return (COLORREF)0xCD5F3AL; } //Blue //0xCD5F3AL //old 0xff0000L (to much blur on a black background)
		if (name == "green")			{ return (COLORREF)0x008000L; }
		if (name == "yellow")			{ return (COLORREF)0x00CDCDL; } //Yellow //old 0x00ffffL //gold3 0x00ADCDL
		//not so common colors below.
		if (name == "deeppurple")		{ return (COLORREF)0xDB7093L; }
		if (name == "silver")			{ return (COLORREF)0xc0c0c0L; }
		if (name == "lime")				{ return (COLORREF)0x00ff00L; }
		if (name == "seagreen")			{ return (COLORREF)0x32CD32L; } //seagreen 0x80CD43L 65B0161C
		if (name == "gray")				{ return (COLORREF)0x808080L; }
		if (name == "darkslategray")	{ return (COLORREF)0x2F4F4FL; }
		if (name == "olive")			{ return (COLORREF)0x008080L; }
		if (name == "maroon")			{ return (COLORREF)0x000080L; }
		if (name == "navy")				{ return (COLORREF)0x800000L; }
		if (name == "purple")			{ return (COLORREF)0x800080L; }
		if (name == "teal")				{ return (COLORREF)0x808000L; }
		if (name == "fuchsia")			{ return (COLORREF)0xff00ffL; }
		if (name == "aqua")				{ return (COLORREF)0xffff00L; }
		//else no color was found default black
		return (COLORREF)(0x000000L);
	}

}
