

/* Begin Error Codes */
#undef UIOHOOK_SUCCESS
#undef UIOHOOK_FAILURE

// System level errors.
#undef UIOHOOK_ERROR_OUT_OF_MEMORY

// Unix specific errors.
#undef UIOHOOK_ERROR_X_OPEN_DISPLAY
#undef UIOHOOK_ERROR_X_RECORD_NOT_FOUND
#undef UIOHOOK_ERROR_X_RECORD_ALLOC_RANGE
#undef UIOHOOK_ERROR_X_RECORD_CREATE_CONTEXT
#undef UIOHOOK_ERROR_X_RECORD_ENABLE_CONTEXT
#undef UIOHOOK_ERROR_X_RECORD_GET_CONTEXT

// Windows specific errors.
#undef UIOHOOK_ERROR_SET_WINDOWS_HOOK_EX
#undef UIOHOOK_ERROR_GET_MODULE_HANDLE

// Darwin specific errors.
#undef UIOHOOK_ERROR_AXAPI_DISABLED
#undef UIOHOOK_ERROR_CREATE_EVENT_PORT
#undef UIOHOOK_ERROR_CREATE_RUN_LOOP_SOURCE
#undef UIOHOOK_ERROR_GET_RUNLOOP
#undef UIOHOOK_ERROR_CREATE_OBSERVER
/* End Error Codes */

/* Begin Virtual Key Codes */
#undef VC_ESCAPE

// Begin Function Keys
#undef VC_F1
#undef VC_F2
#undef VC_F3
#undef VC_F4
#undef VC_F5
#undef VC_F6
#undef VC_F7
#undef VC_F8
#undef VC_F9
#undef VC_F10
#undef VC_F11
#undef VC_F12

#undef VC_F13
#undef VC_F14
#undef VC_F15
#undef VC_F16
#undef VC_F17
#undef VC_F18
#undef VC_F19
#undef VC_F20
#undef VC_F21
#undef VC_F22
#undef VC_F23
#undef VC_F24
// End Function Keys

// Begin Alphanumeric Zone
#undef VC_BACKQUOTE

#undef VC_1
#undef VC_2
#undef VC_3
#undef VC_4
#undef VC_5
#undef VC_6
#undef VC_7
#undef VC_8
#undef VC_9
#undef VC_0

#undef VC_MINUS  // '-'
#undef VC_EQUALS // '='
#undef VC_BACKSPACE

#undef VC_TAB
#undef VC_CAPS_LOCK

#undef VC_A
#undef VC_B
#undef VC_C
#undef VC_D
#undef VC_E
#undef VC_F
#undef VC_G
#undef VC_H
#undef VC_I
#undef VC_J
#undef VC_K
#undef VC_L
#undef VC_M
#undef VC_N
#undef VC_O
#undef VC_P
#undef VC_Q
#undef VC_R
#undef VC_S
#undef VC_T
#undef VC_U
#undef VC_V
#undef VC_W
#undef VC_X
#undef VC_Y
#undef VC_Z

#undef VC_OPEN_BRACKET  // '['
#undef VC_CLOSE_BRACKET // ']'
#undef VC_BACK_SLASH    // '\'

#undef VC_SEMICOLON // ';'
#undef VC_QUOTE
#undef VC_ENTER

#undef VC_COMMA  // ','
#undef VC_PERIOD // '.'
#undef VC_SLASH  // '/'

#undef VC_SPACE
// End Alphanumeric Zone

#undef VC_PRINTSCREEN
#undef VC_SCROLL_LOCK
#undef VC_PAUSE

#undef VC_LESSER_GREATER // '<', '>', '|' on qwertz layout

// Begin Edit Key Zone
#undef VC_INSERT
#undef VC_DELETE
#undef VC_HOME
#undef VC_END
#undef VC_PAGE_UP
#undef VC_PAGE_DOWN
// End Edit Key Zone

// Begin Cursor Key Zone
#undef VC_UP
#undef VC_LEFT
#undef VC_CLEAR
#undef VC_RIGHT
#undef VC_DOWN
// End Cursor Key Zone

// Begin Numeric Zone
#undef VC_NUM_LOCK
#undef VC_KP_DIVIDE
#undef VC_KP_MULTIPLY
#undef VC_KP_SUBTRACT
#undef VC_KP_EQUALS
#undef VC_KP_ADD
#undef VC_KP_ENTER
#undef VC_KP_SEPARATOR

#undef VC_KP_1
#undef VC_KP_2
#undef VC_KP_3
#undef VC_KP_4
#undef VC_KP_5
#undef VC_KP_6
#undef VC_KP_7
#undef VC_KP_8
#undef VC_KP_9
#undef VC_KP_0

#undef VC_KP_END
#undef VC_KP_DOWN
#undef VC_KP_PAGE_DOWN
#undef VC_KP_LEFT
#undef VC_KP_CLEAR
#undef VC_KP_RIGHT
#undef VC_KP_HOME
#undef VC_KP_UP
#undef VC_KP_PAGE_UP
#undef VC_KP_INSERT
#undef VC_KP_DELETE
// End Numeric Zone

// Begin Modifier and Control Keys
#undef VC_SHIFT_L
#undef VC_SHIFT_R
#undef VC_CONTROL_L
#undef VC_CONTROL_R
#undef VC_ALT_L  // Option or Alt Key
#undef VC_ALT_R  // Option or Alt Key
#undef VC_META_L // Windows or Command Key
#undef VC_META_R // Windows or Command Key
#undef VC_CONTEXT_MENU
// End Modifier and Control Keys

// Begin Media Control Keys
#undef VC_POWER
#undef VC_SLEEP
#undef VC_WAKE

#undef VC_MEDIA_PLAY
#undef VC_MEDIA_STOP
#undef VC_MEDIA_PREVIOUS
#undef VC_MEDIA_NEXT
#undef VC_MEDIA_SELECT
#undef VC_MEDIA_EJECT

#undef VC_VOLUME_MUTE
#undef VC_VOLUME_UP
#undef VC_VOLUME_DOWN

#undef VC_APP_MAIL
#undef VC_APP_CALCULATOR
#undef VC_APP_MUSIC
#undef VC_APP_PICTURES

#undef VC_BROWSER_SEARCH
#undef VC_BROWSER_HOME
#undef VC_BROWSER_BACK
#undef VC_BROWSER_FORWARD
#undef VC_BROWSER_STOP
#undef VC_BROWSER_REFRESH
#undef VC_BROWSER_FAVORITES
// End Media Control Keys

// Begin Japanese Language Keys
#undef VC_KATAKANA
#undef VC_UNDERSCORE
#undef VC_FURIGANA
#undef VC_KANJI
#undef VC_HIRAGANA
#undef VC_YEN
#undef VC_KP_COMMA
// End Japanese Language Keys

// Begin Sun keyboards
#undef VC_SUN_HELP

#undef VC_SUN_STOP
#undef VC_SUN_PROPS
#undef VC_SUN_FRONT
#undef VC_SUN_OPEN
#undef VC_SUN_FIND
#undef VC_SUN_AGAIN
#undef VC_SUN_UNDO
#undef VC_SUN_COPY
#undef VC_SUN_INSERT
#undef VC_SUN_CUT
// End Sun keyboards

#undef VC_UNDEFINED // KeyCode Unknown

#undef CHAR_UNDEFINED // CharCode Unknown
/* End Virtual Key Codes */

/* Begin Virtual Modifier Masks */
#undef MASK_SHIFT_L
#undef MASK_CTRL_L
#undef MASK_META_L
#undef MASK_ALT_L

#undef MASK_SHIFT_R
#undef MASK_CTRL_R
#undef MASK_META_R
#undef MASK_ALT_R

#undef MASK_SHIFT
#undef MASK_CTRL
#undef MASK_META
#undef MASK_ALT

#undef MASK_BUTTON1
#undef MASK_BUTTON2
#undef MASK_BUTTON3
#undef MASK_BUTTON4
#undef MASK_BUTTON5

#undef MASK_NUM_LOCK
#undef MASK_CAPS_LOCK
#undef MASK_SCROLL_LOCK
/* End Virtual Modifier Masks */

/* Begin Virtual Mouse Buttons */
#undef MOUSE_NOBUTTON // Any Button
#undef MOUSE_BUTTON1  // Left Button
#undef MOUSE_BUTTON2  // Right Button
#undef MOUSE_BUTTON3  // Middle Button
#undef MOUSE_BUTTON4  // Extra Mouse Button
#undef MOUSE_BUTTON5  // Extra Mouse Button

#undef WHEEL_UNIT_SCROLL
#undef WHEEL_BLOCK_SCROLL

#undef WHEEL_VERTICAL_DIRECTION
#undef WHEEL_HORIZONTAL_DIRECTION
/* End Virtual Mouse Buttons */

/* Begin Error Codes */
constexpr auto UIOHOOK_SUCCESS = 0x00;
constexpr auto UIOHOOK_FAILURE = 0x01;

// System level errors.
constexpr auto UIOHOOK_ERROR_OUT_OF_MEMORY = 0x02;

// Unix specific errors.
constexpr auto UIOHOOK_ERROR_X_OPEN_DISPLAY = 0x20;
constexpr auto UIOHOOK_ERROR_X_RECORD_NOT_FOUND = 0x21;
constexpr auto UIOHOOK_ERROR_X_RECORD_ALLOC_RANGE = 0x22;
constexpr auto UIOHOOK_ERROR_X_RECORD_CREATE_CONTEXT = 0x23;
constexpr auto UIOHOOK_ERROR_X_RECORD_ENABLE_CONTEXT = 0x24;
constexpr auto UIOHOOK_ERROR_X_RECORD_GET_CONTEXT = 0x25;

// Windows specific errors.
constexpr auto UIOHOOK_ERROR_SET_WINDOWS_HOOK_EX = 0x30;
constexpr auto UIOHOOK_ERROR_GET_MODULE_HANDLE = 0x31;

// Darwin specific errors.
constexpr auto UIOHOOK_ERROR_AXAPI_DISABLED = 0x40;
constexpr auto UIOHOOK_ERROR_CREATE_EVENT_PORT = 0x41;
constexpr auto UIOHOOK_ERROR_CREATE_RUN_LOOP_SOURCE = 0x42;
constexpr auto UIOHOOK_ERROR_GET_RUNLOOP = 0x43;
constexpr auto UIOHOOK_ERROR_CREATE_OBSERVER = 0x44;
/* End Error Codes */

/* Begin Virtual Key Codes */
constexpr auto VC_ESCAPE = 0x0001;

// Begin Function Keys
constexpr auto VC_F1 = 0x003B;
constexpr auto VC_F2 = 0x003C;
constexpr auto VC_F3 = 0x003D;
constexpr auto VC_F4 = 0x003E;
constexpr auto VC_F5 = 0x003F;
constexpr auto VC_F6 = 0x0040;
constexpr auto VC_F7 = 0x0041;
constexpr auto VC_F8 = 0x0042;
constexpr auto VC_F9 = 0x0043;
constexpr auto VC_F10 = 0x0044;
constexpr auto VC_F11 = 0x0057;
constexpr auto VC_F12 = 0x0058;

constexpr auto VC_F13 = 0x005B;
constexpr auto VC_F14 = 0x005C;
constexpr auto VC_F15 = 0x005D;
constexpr auto VC_F16 = 0x0063;
constexpr auto VC_F17 = 0x0064;
constexpr auto VC_F18 = 0x0065;
constexpr auto VC_F19 = 0x0066;
constexpr auto VC_F20 = 0x0067;
constexpr auto VC_F21 = 0x0068;
constexpr auto VC_F22 = 0x0069;
constexpr auto VC_F23 = 0x006A;
constexpr auto VC_F24 = 0x006B;
// End Function Keys

// Begin Alphanumeric Zone
constexpr auto VC_BACKQUOTE = 0x0029;

constexpr auto VC_1 = 0x0002;
constexpr auto VC_2 = 0x0003;
constexpr auto VC_3 = 0x0004;
constexpr auto VC_4 = 0x0005;
constexpr auto VC_5 = 0x0006;
constexpr auto VC_6 = 0x0007;
constexpr auto VC_7 = 0x0008;
constexpr auto VC_8 = 0x0009;
constexpr auto VC_9 = 0x000A;
constexpr auto VC_0 = 0x000B;

constexpr auto VC_MINUS = 0x000C;  // '-'
constexpr auto VC_EQUALS = 0x000D; // '='
constexpr auto VC_BACKSPACE = 0x000E;

constexpr auto VC_TAB = 0x000F;
constexpr auto VC_CAPS_LOCK = 0x003A;

constexpr auto VC_A = 0x001E;
constexpr auto VC_B = 0x0030;
constexpr auto VC_C = 0x002E;
constexpr auto VC_D = 0x0020;
constexpr auto VC_E = 0x0012;
constexpr auto VC_F = 0x0021;
constexpr auto VC_G = 0x0022;
constexpr auto VC_H = 0x0023;
constexpr auto VC_I = 0x0017;
constexpr auto VC_J = 0x0024;
constexpr auto VC_K = 0x0025;
constexpr auto VC_L = 0x0026;
constexpr auto VC_M = 0x0032;
constexpr auto VC_N = 0x0031;
constexpr auto VC_O = 0x0018;
constexpr auto VC_P = 0x0019;
constexpr auto VC_Q = 0x0010;
constexpr auto VC_R = 0x0013;
constexpr auto VC_S = 0x001F;
constexpr auto VC_T = 0x0014;
constexpr auto VC_U = 0x0016;
constexpr auto VC_V = 0x002F;
constexpr auto VC_W = 0x0011;
constexpr auto VC_X = 0x002D;
constexpr auto VC_Y = 0x0015;
constexpr auto VC_Z = 0x002C;

constexpr auto VC_OPEN_BRACKET = 0x001A;  // '['
constexpr auto VC_CLOSE_BRACKET = 0x001B; // ']'
constexpr auto VC_BACK_SLASH = 0x002B;    // '\'

constexpr auto VC_SEMICOLON = 0x0027; // ';'
constexpr auto VC_QUOTE = 0x0028;
constexpr auto VC_ENTER = 0x001C;

constexpr auto VC_COMMA = 0x0033;  // ','
constexpr auto VC_PERIOD = 0x0034; // '.'
constexpr auto VC_SLASH = 0x0035;  // '/'

constexpr auto VC_SPACE = 0x0039;
// End Alphanumeric Zone

constexpr auto VC_PRINTSCREEN = 0x0E37;
constexpr auto VC_SCROLL_LOCK = 0x0046;
constexpr auto VC_PAUSE = 0x0E45;

constexpr auto VC_LESSER_GREATER = 0x0E46; // '<', '>', '|' on qwertz layout

// Begin Edit Key Zone
constexpr auto VC_INSERT = 0x0E52;
constexpr auto VC_DELETE = 0x0E53;
constexpr auto VC_HOME = 0x0E47;
constexpr auto VC_END = 0x0E4F;
constexpr auto VC_PAGE_UP = 0x0E49;
constexpr auto VC_PAGE_DOWN = 0x0E51;
// End Edit Key Zone

// Begin Cursor Key Zone
constexpr auto VC_UP = 0xE048;
constexpr auto VC_LEFT = 0xE04B;
constexpr auto VC_CLEAR = 0xE04C;
constexpr auto VC_RIGHT = 0xE04D;
constexpr auto VC_DOWN = 0xE050;
// End Cursor Key Zone

// Begin Numeric Zone
constexpr auto VC_NUM_LOCK = 0x0045;
constexpr auto VC_KP_DIVIDE = 0x0E35;
constexpr auto VC_KP_MULTIPLY = 0x0037;
constexpr auto VC_KP_SUBTRACT = 0x004A;
constexpr auto VC_KP_EQUALS = 0x0E0D;
constexpr auto VC_KP_ADD = 0x004E;
constexpr auto VC_KP_ENTER = 0x0E1C;
constexpr auto VC_KP_SEPARATOR = 0x0053;

constexpr auto VC_KP_1 = 0x004F;
constexpr auto VC_KP_2 = 0x0050;
constexpr auto VC_KP_3 = 0x0051;
constexpr auto VC_KP_4 = 0x004B;
constexpr auto VC_KP_5 = 0x004C;
constexpr auto VC_KP_6 = 0x004D;
constexpr auto VC_KP_7 = 0x0047;
constexpr auto VC_KP_8 = 0x0048;
constexpr auto VC_KP_9 = 0x0049;
constexpr auto VC_KP_0 = 0x0052;

constexpr auto VC_KP_END = 0xEE00 | VC_KP_1;
constexpr auto VC_KP_DOWN = 0xEE00 | VC_KP_2;
constexpr auto VC_KP_PAGE_DOWN = 0xEE00 | VC_KP_3;
constexpr auto VC_KP_LEFT = 0xEE00 | VC_KP_4;
constexpr auto VC_KP_CLEAR = 0xEE00 | VC_KP_5;
constexpr auto VC_KP_RIGHT = 0xEE00 | VC_KP_6;
constexpr auto VC_KP_HOME = 0xEE00 | VC_KP_7;
constexpr auto VC_KP_UP = 0xEE00 | VC_KP_8;
constexpr auto VC_KP_PAGE_UP = 0xEE00 | VC_KP_9;
constexpr auto VC_KP_INSERT = 0xEE00 | VC_KP_0;
constexpr auto VC_KP_DELETE = 0xEE00 | VC_KP_SEPARATOR;
// End Numeric Zone

// Begin Modifier and Control Keys
constexpr auto VC_SHIFT_L = 0x002A;
constexpr auto VC_SHIFT_R = 0x0036;
constexpr auto VC_CONTROL_L = 0x001D;
constexpr auto VC_CONTROL_R = 0x0E1D;
constexpr auto VC_ALT_L = 0x0038;  // Option or Alt Key
constexpr auto VC_ALT_R = 0x0E38;  // Option or Alt Key
constexpr auto VC_META_L = 0x0E5B; // Windows or Command Key
constexpr auto VC_META_R = 0x0E5C; // Windows or Command Key
constexpr auto VC_CONTEXT_MENU = 0x0E5D;
// End Modifier and Control Keys

// Begin Media Control Keys
constexpr auto VC_POWER = 0xE05E;
constexpr auto VC_SLEEP = 0xE05F;
constexpr auto VC_WAKE = 0xE063;

constexpr auto VC_MEDIA_PLAY = 0xE022;
constexpr auto VC_MEDIA_STOP = 0xE024;
constexpr auto VC_MEDIA_PREVIOUS = 0xE010;
constexpr auto VC_MEDIA_NEXT = 0xE019;
constexpr auto VC_MEDIA_SELECT = 0xE06D;
constexpr auto VC_MEDIA_EJECT = 0xE02C;

constexpr auto VC_VOLUME_MUTE = 0xE020;
constexpr auto VC_VOLUME_UP = 0xE030;
constexpr auto VC_VOLUME_DOWN = 0xE02E;

constexpr auto VC_APP_MAIL = 0xE06C;
constexpr auto VC_APP_CALCULATOR = 0xE021;
constexpr auto VC_APP_MUSIC = 0xE03C;
constexpr auto VC_APP_PICTURES = 0xE064;

constexpr auto VC_BROWSER_SEARCH = 0xE065;
constexpr auto VC_BROWSER_HOME = 0xE032;
constexpr auto VC_BROWSER_BACK = 0xE06A;
constexpr auto VC_BROWSER_FORWARD = 0xE069;
constexpr auto VC_BROWSER_STOP = 0xE068;
constexpr auto VC_BROWSER_REFRESH = 0xE067;
constexpr auto VC_BROWSER_FAVORITES = 0xE066;
// End Media Control Keys

// Begin Japanese Language Keys
constexpr auto VC_KATAKANA = 0x0070;
constexpr auto VC_UNDERSCORE = 0x0073;
constexpr auto VC_FURIGANA = 0x0077;
constexpr auto VC_KANJI = 0x0079;
constexpr auto VC_HIRAGANA = 0x007B;
constexpr auto VC_YEN = 0x007D;
constexpr auto VC_KP_COMMA = 0x007E;
// End Japanese Language Keys

// Begin Sun keyboards
constexpr auto VC_SUN_HELP = 0xFF75;

constexpr auto VC_SUN_STOP = 0xFF78;
constexpr auto VC_SUN_PROPS = 0xFF76;
constexpr auto VC_SUN_FRONT = 0xFF77;
constexpr auto VC_SUN_OPEN = 0xFF74;
constexpr auto VC_SUN_FIND = 0xFF7E;
constexpr auto VC_SUN_AGAIN = 0xFF79;
constexpr auto VC_SUN_UNDO = 0xFF7A;
constexpr auto VC_SUN_COPY = 0xFF7C;
constexpr auto VC_SUN_INSERT = 0xFF7D;
constexpr auto VC_SUN_CUT = 0xFF7B;
// End Sun keyboards

constexpr auto VC_UNDEFINED = 0x0000; // KeyCode Unknown

constexpr auto CHAR_UNDEFINED = 0xFFFF; // CharCode Unknown
/* End Virtual Key Codes */

/* Begin Virtual Modifier Masks */
constexpr auto MASK_SHIFT_L = 1 << 0;
constexpr auto MASK_CTRL_L = 1 << 1;
constexpr auto MASK_META_L = 1 << 2;
constexpr auto MASK_ALT_L = 1 << 3;

constexpr auto MASK_SHIFT_R = 1 << 4;
constexpr auto MASK_CTRL_R = 1 << 5;
constexpr auto MASK_META_R = 1 << 6;
constexpr auto MASK_ALT_R = 1 << 7;

constexpr auto MASK_SHIFT = MASK_SHIFT_L | MASK_SHIFT_R;
constexpr auto MASK_CTRL = MASK_CTRL_L | MASK_CTRL_R;
constexpr auto MASK_META = MASK_META_L | MASK_META_R;
constexpr auto MASK_ALT = MASK_ALT_L | MASK_ALT_R;

constexpr auto MASK_BUTTON1 = 1 << 8;
constexpr auto MASK_BUTTON2 = 1 << 9;
constexpr auto MASK_BUTTON3 = 1 << 10;
constexpr auto MASK_BUTTON4 = 1 << 11;
constexpr auto MASK_BUTTON5 = 1 << 12;

constexpr auto MASK_NUM_LOCK = 1 << 13;
constexpr auto MASK_CAPS_LOCK = 1 << 14;
constexpr auto MASK_SCROLL_LOCK = 1 << 15;
/* End Virtual Modifier Masks */

/* Begin Virtual Mouse Buttons */
constexpr auto MOUSE_NOBUTTON = 0; // Any Button
constexpr auto MOUSE_BUTTON1 = 1;  // Left Button
constexpr auto MOUSE_BUTTON2 = 2;  // Right Button
constexpr auto MOUSE_BUTTON3 = 3;  // Middle Button
constexpr auto MOUSE_BUTTON4 = 4;  // Extra Mouse Button
constexpr auto MOUSE_BUTTON5 = 5;  // Extra Mouse Button

constexpr auto WHEEL_UNIT_SCROLL = 1;
constexpr auto WHEEL_BLOCK_SCROLL = 2;

constexpr auto WHEEL_VERTICAL_DIRECTION = 3;
constexpr auto WHEEL_HORIZONTAL_DIRECTION = 4;
/* End Virtual Mouse Buttons */