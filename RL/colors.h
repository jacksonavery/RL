#pragma once
#include <BearLibTerminal.h>
namespace colors {
	const color_t black    = 0xff090b0d;
	const color_t white    = 0xffffffff;
	const color_t dkgrey   = 0xff42384d;
	const color_t grey     = 0xff787878;
	const color_t lgrey    = 0xffe3eac9;
	const color_t red      = 0xffff0052;
	const color_t skin     = 0xfffcebcb;
	const color_t parv     = 0xffbefe21;
	const color_t cyan     = 0xff19f6f9;
	const color_t blue     = 0xff2b3ce1;
	const color_t green    = 0xff3dec49;
	const color_t yellow   = 0xffffff3b;
	const color_t skinsh   = 0xffe59883;
	const color_t magenta  = 0xffff5a9b;
	const color_t orange   = 0xfffe9317;
	const color_t fgreen   = 0xff0c6f55;
	const color_t brown    = 0xff825141;
	const color_t lblack   = 0xff292625;
	const color_t dkblue   = 0xff00294c;
	const color_t maroon   = 0xff791839;

	const int numcolors = 20;
	const color_t indexed[numcolors] = { black, white, dkgrey, grey, lgrey, red, yellow, parv, cyan, blue, green, skin, skinsh, magenta, orange, fgreen, brown, lblack, dkblue, maroon };

	//const color_t black = 0xff0e1214;
	//const color_t white = 0xfff6f7f3;
	//const color_t rust = 0xff9c3c31;
	//const color_t lblue = 0xff4fa8bc;
	//const color_t purple = 0xff7d4a9f;
	//const color_t dkgrn = 0xff5d8845;
	//const color_t dkblue = 0xff393ba3;
	//const color_t skin = 0xffe5cd7a;
	//const color_t brown = 0xff996732;
	//const color_t maroon = 0xff4c0c27;
	//const color_t skinsh = 0xffc27765;
	//const color_t dkgray = 0xff444848;
	//const color_t gray = 0xff868986;
	//const color_t foam = 0xffc8be294;
	//const color_t pink = 0xffe279d4;
	//const color_t lgray = 0xffd3d4d2;
	//
	//const int numcolors = 16;
	//
	//const color_t indexed[numcolors] = { black, white, rust, lblue,
	//								purple, dkgrn, dkblue, skin,
	//								brown, maroon, skinsh, dkgray,
	//								gray, foam, pink, lgray };

	//const color_t black = 0xff090b0d;
	//const color_t deepgray = 0xff292725;
	//const color_t dkgray = 0xff444848;
	//const color_t gray = 0xff868986;
	//const color_t lgray = 0xffd3d4d2;
	//const color_t white = 0xfffffefb;
	//const color_t deepblue = 0xff033e5e;
	//const color_t dkblue = 0xff0b789a;
	//const color_t blue = 0xff3bbedb;
	//const color_t lgreenc64 = 0xff7de588;
	//const color_t dkpurple = 0xff4e50a3;
	//const color_t purple = 0xffb371d4;
	//const color_t dkorange = 0xff9c3c31;
	//const color_t orange = 0xffec8a4c;
	//const color_t skin = 0xfffbe1b6;
	//const color_t skinsh = 0xffdc9474;
	//const color_t dkpink = 0xffb34862;
	//const color_t pink = 0xffff8c91;
	//const color_t dkbrown = 0xff4c2829;
	//const color_t brown = 0xff785142;
	//const color_t deepgreen = 0xff273336;
	//const color_t greenbl = 0xff296145;
	//const color_t greenyl = 0xff458239;
	//const color_t lgreen = 0xff9dad34;
	//const color_t yellow = 0xffffd832;
	//const color_t red = 0xffd52b2d;
	//
	//const int numcolors = 26;
	//
	//const color_t indexed[numcolors] = { black, deepgray, dkgray, gray, lgray,
	//									deepblue, dkblue, blue, lgreenc64, white,
	//									dkpurple, purple, dkorange, orange, skin,
	//									dkpink, pink, dkbrown, brown, skinsh,
	//									deepgreen, greenbl, greenyl, lgreen, yellow, red};
}


//#pragma once
//#include <SDL.h>
//namespace cols {
//	const SDL_Color aliceblue = { 240, 248, 255, 255 };
//	const SDL_Color antiquewhite = { 250, 235, 215, 255 };
//	const SDL_Color aqua = { 0, 255, 255, 255 };
//	const SDL_Color aquamarine = { 127, 255, 212, 255 };
//	const SDL_Color azure = { 240, 255, 255, 255 };
//	const SDL_Color bisque = { 255, 228, 196, 255 };
//	const SDL_Color black = { 0, 0, 0, 255 };
//	const SDL_Color blanchedalmond = { 255, 235, 205, 255 };
//	const SDL_Color blue = { 0, 0, 255, 255 };
//	const SDL_Color brown = { 165, 42, 42, 255 };
//	const SDL_Color burlywood = { 222, 184, 135, 255 };
//	const SDL_Color cadetblue = { 95, 158, 160, 255 };
//	const SDL_Color chartreuse = { 127, 255, 0, 255 };
//	const SDL_Color coral = { 255, 127, 80, 255 };
//	const SDL_Color cornflowerblue = { 100, 149, 237, 255 };
//	const SDL_Color cornsilk = { 255, 248, 220, 255 };
//	const SDL_Color crimson = { 220, 20, 60, 255 };
//	const SDL_Color darkblue = { 0, 0, 139, 255 };
//	const SDL_Color darkcyan = { 0, 139, 139, 255 };
//	const SDL_Color darkgoldenrod = { 184, 134, 11, 255 };
//	const SDL_Color darkgray = { 169, 169, 169, 255 };
//	const SDL_Color darkgrey = { 169, 169, 169, 255 };
//	const SDL_Color darkkhaki = { 189, 183, 107, 255 };
//	const SDL_Color darkmagenta = { 139, 0, 139, 255 };
//	const SDL_Color darkolivegreen = { 85, 107, 47, 255 };
//	const SDL_Color darkorchid = { 153, 50, 204, 255 };
//	const SDL_Color darkred = { 139, 0, 0, 255 };
//	const SDL_Color darksalmon = { 233, 150, 122, 255 };
//	const SDL_Color darkseagreen = { 143, 188, 143, 255 };
//	const SDL_Color darkslategray = { 47, 79, 79, 255 };
//	const SDL_Color darkslategrey = { 47, 79, 79, 255 };
//	const SDL_Color darkturquoise = { 0, 206, 209, 255 };
//	const SDL_Color darkviolet = { 148, 0, 211, 255 };
//	const SDL_Color deepskyblue = { 0, 191, 255, 255 };
//	const SDL_Color dimgray = { 105, 105, 105, 255 };
//	const SDL_Color dimgrey = { 105, 105, 105, 255 };
//	const SDL_Color dodgerblue = { 30, 144, 255, 255 };
//	const SDL_Color floralwhite = { 255, 250, 240, 255 };
//	const SDL_Color forestgreen = { 34, 139, 34, 255 };
//	const SDL_Color fuchsia = { 255, 0, 255, 255 };
//	const SDL_Color gainsboro = { 220, 220, 220, 255 };
//	const SDL_Color gold = { 255, 215, 0, 255 };
//	const SDL_Color goldenrod = { 218, 165, 32, 255 };
//	const SDL_Color gray = { 128, 128, 128, 255 };
//	const SDL_Color green = { 0, 128, 0, 255 };
//	const SDL_Color grey = { 128, 128, 128, 255 };
//	const SDL_Color honeydew = { 240, 255, 240, 255 };
//	const SDL_Color hotpink = { 255, 105, 180, 255 };
//	const SDL_Color indianred = { 205, 92, 92, 255 };
//	const SDL_Color ivory = { 255, 255, 240, 255 };
//	const SDL_Color khaki = { 240, 230, 140, 255 };
//	const SDL_Color lavender = { 230, 230, 250, 255 };
//	const SDL_Color lavenderblush = { 255, 240, 245, 255 };
//	const SDL_Color lemonchiffon = { 255, 250, 205, 255 };
//	const SDL_Color lightblue = { 173, 216, 230, 255 };
//	const SDL_Color lightcoral = { 240, 128, 128, 255 };
//	const SDL_Color lightcyan = { 224, 255, 255, 255 };
//	const SDL_Color lightgray = { 211, 211, 211, 255 };
//	const SDL_Color lightgreen = { 144, 238, 144, 255 };
//	const SDL_Color lightgrey = { 211, 211, 211, 255 };
//	const SDL_Color lightpink = { 255, 182, 193, 255 };
//	const SDL_Color lightseagreen = { 32, 178, 170, 255 };
//	const SDL_Color lightskyblue = { 135, 206, 250, 255 };
//	const SDL_Color lightslategray = { 119, 136, 153, 255 };
//	const SDL_Color lightslategrey = { 119, 136, 153, 255 };
//	const SDL_Color lightyellow = { 255, 255, 224, 255 };
//	const SDL_Color lime = { 0, 255, 0, 255 };
//	const SDL_Color limegreen = { 50, 205, 50, 255 };
//	const SDL_Color linen = { 250, 240, 230, 255 };
//	const SDL_Color maroon = { 128, 0, 0, 255 };
//	const SDL_Color mediumaquamarine = { 102, 205, 170, 255 };
//	const SDL_Color mediumblue = { 0, 0, 205, 255 };
//	const SDL_Color mediumorchid = { 186, 85, 211, 255 };
//	const SDL_Color mediumseagreen = { 60, 179, 113, 255 };
//	const SDL_Color mediumslateblue = { 123, 104, 238, 255 };
//	const SDL_Color mediumspringgreen = { 0, 250, 154, 255 };
//	const SDL_Color mediumturquoise = { 72, 209, 204, 255 };
//	const SDL_Color midnightblue = { 25, 25, 112, 255 };
//	const SDL_Color mintcream = { 245, 255, 250, 255 };
//	const SDL_Color mistyrose = { 255, 228, 225, 255 };
//	const SDL_Color moccasin = { 255, 228, 181, 255 };
//	const SDL_Color navy = { 0, 0, 128, 255 };
//	const SDL_Color oldlace = { 253, 245, 230, 255 };
//	const SDL_Color olive = { 128, 128, 0, 255 };
//	const SDL_Color olivedrab = { 107, 142, 35, 255 };
//	const SDL_Color orangered = { 255, 69, 0, 255 };
//	const SDL_Color orchid = { 218, 112, 214, 255 };
//	const SDL_Color palegoldenrod = { 238, 232, 170, 255 };
//	const SDL_Color palegreen = { 152, 251, 152, 255 };
//	const SDL_Color palevioletred = { 219, 112, 147, 255 };
//	const SDL_Color papayawhip = { 255, 239, 213, 255 };
//	const SDL_Color peachpuff = { 255, 218, 185, 255 };
//	const SDL_Color peru = { 205, 133, 63, 255 };
//	const SDL_Color plum = { 221, 160, 221, 255 };
//	const SDL_Color powderblue = { 176, 224, 230, 255 };
//	const SDL_Color purple = { 128, 0, 128, 255 };
//	const SDL_Color red = { 255, 0, 0, 255 };
//	const SDL_Color royalblue = { 65, 105, 225, 255 };
//	const SDL_Color saddlebrown = { 139, 69, 19, 255 };
//	const SDL_Color salmon = { 250, 128, 114, 255 };
//	const SDL_Color sandybrown = { 244, 164, 96, 255 };
//	const SDL_Color seashell = { 255, 245, 238, 255 };
//	const SDL_Color sienna = { 160, 82, 45, 255 };
//	const SDL_Color silver = { 192, 192, 192, 255 };
//	const SDL_Color skyblue = { 135, 206, 235, 255 };
//	const SDL_Color slategray = { 112, 128, 144, 255 };
//	const SDL_Color slategrey = { 112, 128, 144, 255 };
//	const SDL_Color snow = { 255, 250, 250, 255 };
//	const SDL_Color springgreen = { 0, 255, 127, 255 };
//	const SDL_Color tan = { 210, 180, 140, 255 };
//	const SDL_Color teal = { 0, 128, 128, 255 };
//	const SDL_Color thistle = { 216, 191, 216, 255 };
//	const SDL_Color tomato = { 255, 99, 71, 255 };
//	const SDL_Color violet = { 238, 130, 238, 255 };
//	const SDL_Color wheat = { 245, 222, 179, 255 };
//	const SDL_Color white = { 255, 255, 255, 255 };
//	const SDL_Color whitesmoke = { 245, 245, 245, 255 };
//	const SDL_Color yellowgreen = { 154, 205, 50, 255 };
//
//	//these had to be added manually due to site formatting
//	const SDL_Color beige = { 245, 245, 220, 255 };
//	const SDL_Color blueviolet = { 138, 43, 226, 255 };
//	const SDL_Color chocolate = { 210, 105, 30, 255 };
//	const SDL_Color cyan = { 0, 255, 255, 255 };
//	const SDL_Color darkgreen = { 0, 100, 0, 255 };
//	const SDL_Color darkorange = { 255, 140, 0, 255 };
//	const SDL_Color darkslateblue = { 72, 61, 139, 255 };
//	const SDL_Color deeppink = { 255, 20, 147, 255 };
//	const SDL_Color firebrick = { 178, 34, 34, 255 };
//	const SDL_Color ghostwhite = { 248, 248, 255, 255 };
//	const SDL_Color greenyellow = { 173, 255, 47, 255 };
//	const SDL_Color indigo = { 75, 0, 130, 255 };
//	const SDL_Color lawngreen = { 124, 252, 0, 255 };
//	const SDL_Color lightgoldenrodyellow = { 250, 250, 210, 255 };
//	const SDL_Color lightsalmon = { 255, 160, 122, 255 };
//	const SDL_Color lightsteelblue = { 176, 196, 222, 255 };
//	const SDL_Color magenta = { 255, 0, 255, 255 };
//	const SDL_Color mediumpurple = { 147, 112, 219, 255 };
//	const SDL_Color mediumvioletred = { 199, 21, 133, 255 };
//	const SDL_Color navajowhite = { 255, 222, 173, 255 };
//	const SDL_Color orange = { 255, 165, 0, 255 };
//	const SDL_Color paleturquoise = { 175, 238, 238, 255 };
//	const SDL_Color pink = { 255, 192, 203, 255 };
//	const SDL_Color rosybrown = { 188, 143, 143, 255 };
//	const SDL_Color seagreen = { 46, 139, 87, 255 };
//	const SDL_Color slateblue = { 106, 90, 205, 255 };
//	const SDL_Color steelblue = { 70, 130, 180, 255 };
//	const SDL_Color turquoise = { 64, 224, 208, 255 };
//	const SDL_Color yellow = { 255, 255, 0, 255 };
//}