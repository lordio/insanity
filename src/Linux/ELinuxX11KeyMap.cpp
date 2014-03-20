#define INSANITY_BUILDING_LIBRARY

#include <EKeyMap.hpp>

#if defined(PLATFORM_LINUX)

#define XK_PUBLISHING
#define XK_TECHNICAL
#include <X11/keysym.h>

namespace Insanity
{
	const EKey EKeyMap::A = XK_a;
	const EKey EKeyMap::Add = XK_plus;
	const EKey EKeyMap::Alt = XK_Alt_L;
	const EKey EKeyMap::Applications = 0;
	const EKey EKeyMap::B = XK_b;
	const EKey EKeyMap::Backquote = XK_grave;
	const EKey EKeyMap::Backslash = XK_backslash;
	const EKey EKeyMap::Backspace = XK_BackSpace;
	const EKey EKeyMap::C = XK_c;
	const EKey EKeyMap::CapsLock = XK_Caps_Lock;
	const EKey EKeyMap::Clear = XK_Clear;
	const EKey EKeyMap::Comma = XK_comma;
	const EKey EKeyMap::Control = XK_Control_L;
	const EKey EKeyMap::D = XK_d;
	const EKey EKeyMap::Decimal = XK_decimalpoint;
	const EKey EKeyMap::Delete = XK_Delete;
	const EKey EKeyMap::Divide = XK_KP_Divide;
	const EKey EKeyMap::DownArrow = XK_downarrow;
	const EKey EKeyMap::E = XK_e;
	const EKey EKeyMap::Eight = XK_8;
	const EKey EKeyMap::End = XK_End;
	const EKey EKeyMap::Enter = XK_Return;
	const EKey EKeyMap::Equals = XK_equal;
	const EKey EKeyMap::Escape = XK_Escape;
	const EKey EKeyMap::F = XK_f;
	const EKey EKeyMap::F1 = XK_F1;
	const EKey EKeyMap::F2 = XK_F2;
	const EKey EKeyMap::F3 = XK_F3;
	const EKey EKeyMap::F4 = XK_F4;
	const EKey EKeyMap::F5 = XK_F5;
	const EKey EKeyMap::F6 = XK_F6;
	const EKey EKeyMap::F7 = XK_F7;
	const EKey EKeyMap::F8 = XK_F8;
	const EKey EKeyMap::F9 = XK_F9;
	const EKey EKeyMap::F10 = XK_F10;
	const EKey EKeyMap::F11 = XK_F11;
	const EKey EKeyMap::F12 = XK_F12;
	const EKey EKeyMap::F13 = XK_F13;
	const EKey EKeyMap::F14 = XK_F14;
	const EKey EKeyMap::F15 = XK_F15;
	const EKey EKeyMap::F16 = XK_F16;
	const EKey EKeyMap::F17 = XK_F17;
	const EKey EKeyMap::F18 = XK_F18;
	const EKey EKeyMap::F19 = XK_F19;
	const EKey EKeyMap::F20 = XK_F20;
	const EKey EKeyMap::F21 = XK_F21;
	const EKey EKeyMap::F22 = XK_F22;
	const EKey EKeyMap::F23 = XK_F23;
	const EKey EKeyMap::F24 = XK_F24;
	const EKey EKeyMap::Five = XK_5;
	const EKey EKeyMap::Four = XK_4;
	const EKey EKeyMap::G = XK_g;
	const EKey EKeyMap::H = XK_h;
	const EKey EKeyMap::Home = XK_Home;
	const EKey EKeyMap::I = XK_i;
	const EKey EKeyMap::Insert = XK_Insert;
	const EKey EKeyMap::J = XK_j;
	const EKey EKeyMap::K = XK_k;
	const EKey EKeyMap::L = XK_l;
	const EKey EKeyMap::LeftAlt = XK_Alt_L;
	const EKey EKeyMap::LeftArrow = XK_leftarrow;
	const EKey EKeyMap::LeftControl = XK_Control_L;
	const EKey EKeyMap::LeftShift = XK_Shift_L;
	const EKey EKeyMap::LeftSquareBracket = XK_bracketleft;
	const EKey EKeyMap::LeftSuper = XK_Super_L;
	const EKey EKeyMap::M = XK_m;
	const EKey EKeyMap::Minus = XK_minus;
	const EKey EKeyMap::Multiply = XK_multiply;
	const EKey EKeyMap::N = XK_n;
	const EKey EKeyMap::Nine = XK_9;
	const EKey EKeyMap::NumLock = XK_Num_Lock;
	const EKey EKeyMap::Numpad0 = XK_KP_0;
	const EKey EKeyMap::Numpad1 = XK_KP_1;
	const EKey EKeyMap::Numpad2 = XK_KP_2;
	const EKey EKeyMap::Numpad3 = XK_KP_3;
	const EKey EKeyMap::Numpad4 = XK_KP_4;
	const EKey EKeyMap::Numpad5 = XK_KP_5;
	const EKey EKeyMap::Numpad6 = XK_KP_6;
	const EKey EKeyMap::Numpad7 = XK_KP_7;
	const EKey EKeyMap::Numpad8 = XK_KP_8;
	const EKey EKeyMap::Numpad9 = XK_KP_9;
	const EKey EKeyMap::O = XK_o;
	const EKey EKeyMap::One = XK_1;
	const EKey EKeyMap::P = XK_p;
	const EKey EKeyMap::PageDown = XK_Page_Down;
	const EKey EKeyMap::PageUp = XK_Page_Up;
	const EKey EKeyMap::Pause = XK_Pause;
	const EKey EKeyMap::Period = XK_period;
	const EKey EKeyMap::PrintScreen = XK_Print;
	const EKey EKeyMap::Q = XK_q;
	const EKey EKeyMap::Quote = XK_apostrophe;
	const EKey EKeyMap::R = XK_r;
	const EKey EKeyMap::RightAlt = XK_Alt_R;
	const EKey EKeyMap::RightArrow = XK_rightarrow;
	const EKey EKeyMap::RightControl = XK_Control_R;
	const EKey EKeyMap::RightShift = XK_Shift_R;
	const EKey EKeyMap::RightSquareBracket = XK_bracketright;
	const EKey EKeyMap::RightSuper = XK_Super_R;
	const EKey EKeyMap::S = XK_s;
	const EKey EKeyMap::ScrollLock = XK_Scroll_Lock;
	const EKey EKeyMap::Semicolon = XK_semicolon;
	const EKey EKeyMap::Seven = XK_7;
	const EKey EKeyMap::Shift = XK_Shift_L;
	const EKey EKeyMap::Six = XK_6;
	const EKey EKeyMap::Slash = XK_slash;
	const EKey EKeyMap::Spacebar = XK_space;
	const EKey EKeyMap::Subtract = XK_KP_Subtract;
	const EKey EKeyMap::T = XK_t;
	const EKey EKeyMap::Tab = XK_Tab;
	const EKey EKeyMap::Three = XK_3;
	const EKey EKeyMap::Two = XK_2;
	const EKey EKeyMap::U = XK_u;
	const EKey EKeyMap::UpArrow = XK_uparrow;
	const EKey EKeyMap::V = XK_v;
	const EKey EKeyMap::W = XK_w;
	const EKey EKeyMap::X = XK_x;
	const EKey EKeyMap::Y = XK_y;
	const EKey EKeyMap::Z = XK_z;
	const EKey EKeyMap::Zero = XK_0;
}

#endif
