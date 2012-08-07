const char D1_HFVE = 0b00000001;
const char D1_SEVN = 0b00000010;
const char D1_NINE = 0b00000100;
const char D1_ELVN = 0b00001000;
const char D1_OCLK = 0b00010000;
const char D1_SIX = 0b00100000;
const char D1_EGHT = 0b01000000;
const char D1_HTEN = 0b10000000;

const char D2_ONE = 0b00000001;
const char D2_THRE = 0b00000010;
const char D2_TO = 0b00000100;
const char D2_QUAR = 0b00001000;
const char D2_TWLV = 0b00010000;
const char D2_TWO = 0b00100000;
const char D2_FOUR = 0b01000000;
const char D2_PAST = 0b10000000;

const char D3_MTEN = 0b00000001;
const char D3_MFVE = 0b00000010;
const char D3_AB = 0b00000100;
const char D3_AC = 0b00001000;
const char D3_HALF = 0b00010000;
const char D3_TWTY = 0b00100000;
const char D3_ITIS = 0b01000000;
const char D3_AA = 0b10000000;

void initOutput();
void setTime(char reg1, char reg2, char reg3);
