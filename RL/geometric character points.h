//binaries
#define CHAR_EMPTY	0xE000
#define CHAR_FULL	0xE010

//centered lines
#define CHAR_CENTERED_LINE_VERTICAL			0xE02E
#define CHAR_CENTERED_LINE_HORIZONTAL		0xE02F

#define CHAR_CENTERED_LINE_L_TOP_LEFT		0xE00B
#define CHAR_CENTERED_LINE_L_TOP_RIGHT		0xE00D
#define CHAR_CENTERED_LINE_L_BOTTOM_LEFT	0xE02B
#define CHAR_CENTERED_LINE_L_BOTTOM_RIGHT	0xE02D
#define CHAR_CENTERED_LINE_T_NOTOP			0xE00C
#define CHAR_CENTERED_LINE_T_NOBOTTOM		0xE02C
#define CHAR_CENTERED_LINE_T_NOLEFT			0xE01B
#define CHAR_CENTERED_LINE_T_NORIGHT		0xE01D
#define CHAR_CENTERED_LINE_CROSS			0xE01C


////rotation handler class
//enum shapeType {
//	checker, half, centeredSharp, centeredRound, centeredDiag
//};
//
//typedef struct charpointset_ {
//	int p[9];
//} charpointset;
//
//class charPointHandler {
//public:
//	static int getChatRotVar(int rotVar, shapeType type) {
//		rotVar -= 1;
//		return;
//	}
//private:
//	charpointset centL = { 0xE02B, 0xE02F, 0xE02D, 0xE02E, CHAR_EMPTY, 0xE02F, 0xE00B, 0xE02E, 0xE00D };
//	vector<charpointset>;
//};