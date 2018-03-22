#pragma once

// Event Types
#define ES_EVENT_WINDOW 0x0000;
#define ES_EVENT_KEYBOARD 0x0001;
#define ES_EVENT_MOUSE_MOVE 0x0002;
#define ES_EVENT_MOUSE_BUTTON 0x0003;
#define ES_EVENT_MOUSE_WHEEL 0x0004;

// Keyboard Event types/states
#define ES_KEY_UP 0x0100
#define ES_KEY_DOWN 0x0101
#define ES_KEY_PRESSED 0x0102
#define ES_KEY_RELEASED 0x0103

// Keyboard key symbols

// 0 - 9
#define ES_KEYC_0 0x0000
#define ES_KEYC_1 0x0001
#define ES_KEYC_2 0x0002
#define ES_KEYC_3 0x0003
#define ES_KEYC_4 0x0004
#define ES_KEYC_5 0x0005
#define ES_KEYC_6 0x0006
#define ES_KEYC_7 0x0007
#define ES_KEYC_8 0x0008
#define ES_KEYC_9 0x0009
// A - Z
#define ES_KEYC_A 0x000A
#define ES_KEYC_B 0x000B
#define ES_KEYC_C 0x000C
#define ES_KEYC_D 0x000D
#define ES_KEYC_E 0x000E
#define ES_KEYC_F 0x000F
#define ES_KEYC_G 0x0010
#define ES_KEYC_H 0x0011
#define ES_KEYC_I 0x0012
#define ES_KEYC_J 0x0013
#define ES_KEYC_K 0x0014
#define ES_KEYC_L 0x0015
#define ES_KEYC_M 0x0016
#define ES_KEYC_N 0x0017
#define ES_KEYC_O 0x0018
#define ES_KEYC_P 0x0019
#define ES_KEYC_Q 0x001A
#define ES_KEYC_R 0x001B
#define ES_KEYC_S 0x001C
#define ES_KEYC_T 0x001D
#define ES_KEYC_U 0x001E
#define ES_KEYC_V 0x001F
#define ES_KEYC_W 0x0020
#define ES_KEYC_X 0x0021
#define ES_KEYC_Y 0x0022
#define ES_KEYC_Z 0x0023
// F Keys
#define ES_KEYC_F1 0x0024
#define ES_KEYC_F2 0x0025
#define ES_KEYC_F3 0x0026
#define ES_KEYC_F4 0x0027
#define ES_KEYC_F5 0x0028
#define ES_KEYC_F6 0x0029
#define ES_KEYC_F7 0x002A
#define ES_KEYC_F8 0x002B
#define ES_KEYC_F9 0x002C
#define ES_KEYC_F10 0x002D
#define ES_KEYC_F11 0x002E
#define ES_KEYC_F12 0x002F
#define ES_KEYC_F13 0x0030
#define ES_KEYC_F14 0x0031
#define ES_KEYC_F15 0x0032
#define ES_KEYC_F16 0x0033
#define ES_KEYC_F17 0x0034
#define ES_KEYC_F18 0x0035
#define ES_KEYC_F19 0x0036
#define ES_KEYC_F20 0x0037
#define ES_KEYC_F21 0x0038
#define ES_KEYC_F22 0x0039
#define ES_KEYC_F23 0x003A
#define ES_KEYC_F24 0x003B
// NUMPAD numeric
#define ES_KEYC_NUM0 0x0040
#define ES_KEYC_NUM00 0x0041
#define ES_KEYC_NUM000 0x0042
#define ES_KEYC_NUM1 0x0043
#define ES_KEYC_NUM2 0x0044
#define ES_KEYC_NUM3 0x0045
#define ES_KEYC_NUM4 0x0046
#define ES_KEYC_NUM5 0x0047
#define ES_KEYC_NUM6 0x0048
#define ES_KEYC_NUM7 0x0049
#define ES_KEYC_NUM8 0x004A
#define ES_KEYC_NUM9 0x004B

// NUMPAD operators
#define ES_KEYC_NUM_A 0x004C
#define ES_KEYC_NUM_AMPERSAND 0x004D
#define ES_KEYC_NUM_AT 0x004E
#define ES_KEYC_NUM_B 0x004F
#define ES_KEYC_NUM_BACKSPACE 0x0050
#define ES_KEYC_NUM_BINARY 0x0051
#define ES_KEYC_NUM_C 0x0052
#define ES_KEYC_NUM_CLEAR 0x0053
#define ES_KEYC_NUM_CLEAR_ENTRY 0x0054
#define ES_KEYC_NUM_COLON 0x0055
#define ES_KEYC_NUM_COMMA 0x0056
#define ES_KEYC_NUM_D 0x0057
#define ES_KEYC_NUM_AMP_AND 0x0058
#define ES_KEYC_NUM_VERT_OR 0x0059
#define ES_KEYC_NUM_DECIMAL 0x005A
#define ES_KEYC_NUM_DIVIDE 0x005B
#define ES_KEYC_NUM_E 0x005C
#define ES_KEYC_NUM_ENTER 0x005D
#define ES_KEYC_NUM_EQUALS 0x005E
#define ES_KEYC_NUM_EQUALS_AS400 0x005F
#define ES_KEYC_NUM_EXCLAMATION 0x0060
#define ES_KEYC_NUM_F 0x0061
#define ES_KEYC_NUM_GREATERTHAN 0x0062
#define ES_KEYC_NUM_HASH 0x0063
#define ES_KEYC_NUM_HEXADEC 0x0064
#define ES_KEYC_NUM_LBRACE 0x0065
#define ES_KEYC_NUM_LPARENTHESIS 0x0066
#define ES_KEYC_NUM_LESSTHAN 0x0067
#define ES_KEYC_NUM_MEMADD 0x0068
#define ES_KEYC_NUM_MEMCLR 0x0069
#define ES_KEYC_NUM_MEMDIV 0x006A
#define ES_KEYC_NUM_MEMMULT 0x006B
#define ES_KEYC_NUM_MEMRECALL 0x006C
#define ES_KEYC_NUM_MEMSTORE 0x006D
#define ES_KEYC_NUM_MEMSUB 0x006E
#define ES_KEYC_NUM_MINUS 0x006F
#define ES_KEYC_NUM_MULTIPLY 0x0070
#define ES_KEYC_NUM_OCTAL 0x0071
#define ES_KEYC_NUM_PERCENT 0x0072
#define ES_KEYC_NUM_PERIOD 0x0073
#define ES_KEYC_NUM_PLUS 0x0074
#define ES_KEYC_NUM_PLUSMINUS 0x0075
#define ES_KEYC_NUM_POWER 0x0076
#define ES_KEYC_NUM_RBRACE 0x0077
#define ES_KEYC_NUM_RPARENTHESIS 0x0078
#define ES_KEYC_NUM_SPACE 0x0079
#define ES_KEYC_NUM_TAB 0x007A
#define ES_KEYC_NUM_VERTICALBAR 0x007B
#define ES_KEYC_NUM_XOR 0x007C
// Other
#define ES_KEYC_CANCEL 0x0080
#define ES_KEYC_CAPS 0x0081
#define ES_KEYC_CLEAR 0x0082
#define ES_KEYC_CLEAR_AGAIN 0x0083
#define ES_KEYC_COMMA 0x0084
#define ES_KEYC_COMPUTER 0x0085
#define ES_KEYC_COPY 0x0086
#define ES_KEYC_CR_SEL 0x0087
#define ES_KEYC_CUT 0x0088
#define ES_KEYC_DELETE 0x0089
#define ES_KEYC_DOWN 0x008A
#define ES_KEYC_EJECT 0x008B
#define ES_KEYC_END 0x008C
#define ES_KEYC_EQUALS 0x008D
#define ES_KEYC_ESC 0x008E
#define ES_KEYC_EXE 0x008F
#define ES_KEYC_EX_SEL 0x0090
#define ES_KEYC_FIND 0x0091
#define ES_KEYC_TILDE 0x0092
#define ES_KEYC_HELP 0x0093
#define ES_KEYC_HOME 0x0094
#define ES_KEYC_INSERT 0x0095
#define ES_KEYC_LALT 0x0096
#define ES_KEYC_LCTRL 0x0097
#define ES_KEYC_LEFT 0x0098
#define ES_KEYC_LBRACKET 0x0099
#define ES_KEYC_LGUI 0x009A
#define ES_KEYC_LSHIFT 0x009B
#define ES_KEYC_MAIL 0x009C
#define ES_KEYC_MENU 0x009D
#define ES_KEYC_MINUS 0x009E
#define ES_KEYC_MODE_SWITCH 0x009F
#define ES_KEYC_MUTE 0x00A0
#define ES_KEYC_NUM_LOCK 0x00A1
#define ES_KEYC_PGDOWN 0x00A2
#define ES_KEYC_PGUP 0x00A3
#define ES_KEYC_PASTE 0x00A4
#define ES_KEYC_PAUSE 0x00A5
#define ES_KEYC_PERIOD 0x00A6
#define ES_KEYC_POWER 0x00A7
#define ES_KEYC_PRTSCR 0x00A8
#define ES_KEYC_PRIOR 0x00A9
#define ES_KEYC_RALT 0x00AA
#define ES_KEYC_RCTRL 0x00AB
#define ES_KEYC_RETURN 0x00AC
#define ES_KEYC_RBRACKET 0x00AD
#define ES_KEYC_RSHIFT 0x00AE
#define ES_KEYC_SCROLL_LOCK 0x00AF
#define ES_KEYC_SELECT 0x00B0
#define ES_KEYC_SEMICOLON 0x00B1
#define ES_KEYC_SEPERATOR 0x00B2
#define ES_KEYC_FORWARD_SLASH 0x00B3
#define ES_KEYC_SLEEP 0x00B4
#define ES_KEYC_SPACE 0x00B5
#define ES_KEYC_STOP 0x00B6
#define ES_KEYC_SYSREQ 0x00B7
#define ES_KEYC_TAB 0x00B8
#define ES_KEYC_1000S_SEPERATOR 0x00B9
#define ES_KEYC_UNDO 0x00BA


// Media Keys
#define ES_KEYC_MEDIA_MUTE 0x0180
#define ES_KEYC_MEDIA_NEXT 0x0181
#define ES_KEYC_MEDIA_PLAY 0x0182
#define ES_KEYC_MEDIA_PREV 0x0183
#define ES_KEYC_MEDIA_STOP 0x0184
#define ES_KEYC_MEDIA_SELECT 0x0185
#define ES_KEYC_VOLUME_UP 0x0186
#define ES_KEYC_VOLUME_DOWN 0x0187
#define ES_KEYC_BRIGHTNESS_UP 0x0188
#define ES_KEYC_BRIGHTNESS_DOWN 0x0189


// Application control keypad??
#define ES_KEYC_AC_BACK 0x0190
#define ES_KEYC_AC_BOOK 0x0191
#define ES_KEYC_AC_FORWARD 0x0192
#define ES_KEYC_AC_HOME 0x0193
#define ES_KEYC_AC_REFRESH 0x0194
#define ES_KEYC_AC_SEARCH 0x0195
#define ES_KEYC_AC_STOP 0x0196

// Never heard of these either
#define ES_KEYC_AGAIN 0x0200
#define ES_KEYC_ALT_ERASE 0x0201
#define ES_KEYC_APPLICATION 0x0202
#define ES_KEYC_CALCULATOR 0x0203
#define ES_KEYC_CURRENCY_UNIT 0x0204
#define ES_KEYC_CURRENCY_SUBUNIT 0x0205
#define ES_KEYC_DISPLAY_SWITCH 0x0206
#define ES_KEYC_DECIMAL_SEPERATOR 0x0207
#define ES_KEYC_KBD_ILLUMINATION_DOWN 0x0208
#define ES_KEYC_KBD_ILLUMINATION_UP 0x0209
#define ES_KEYC_KBD_ILLUMINATION_TOGGLE 0x020A
#define ES_KEYC_OPER 0x020B
#define ES_KEYC_WWW 0x020C
