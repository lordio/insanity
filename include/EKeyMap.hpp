#ifndef INSANITY_ENUMERATION_KEY_MAP
#define INSANITY_ENUMERATION_KEY_MAP

#include "Constants.hpp"

namespace Insanity
{
	typedef u16 EKey;

	//this only maps a common English keyboard. Other keyboards might not be laid out the same way.
	//I'd suggest allowing remapping keys in game.
	class INSANITY_API EKeyMap final
	{
	private:
	public:
		EKeyMap() = delete;
		EKeyMap(EKeyMap const&) = delete;
		EKeyMap(EKeyMap &&) = delete;
		~EKeyMap() = delete;
		EKeyMap & operator=(EKeyMap const&) = delete;
		EKeyMap & operator=(EKeyMap &&) = delete;

		static const EKey Backspace;
		static const EKey Tab;
		static const EKey Clear;
		static const EKey Enter;
		static const EKey Shift; //Seems to be received instead of more specific Right/Left
		static const EKey Control; //as Shift
		static const EKey Alt; //as Shift
		static const EKey Pause;
		static const EKey CapsLock;
		static const EKey Escape;
		static const EKey Spacebar;
		static const EKey PageUp;
		static const EKey PageDown;
		static const EKey End;
		static const EKey Home;
		static const EKey LeftArrow;
		static const EKey UpArrow;
		static const EKey RightArrow;
		static const EKey DownArrow;
		static const EKey PrintScreen;
		static const EKey Insert;
		static const EKey Delete;
		// zero through nine are all mapped to numbers equivalent to their ASCII values.
		// catch A through Z using uppercase character literals.
		//could put in enumerations for those, and make this an enum class.
		static const EKey A;
		static const EKey B;
		static const EKey C;
		static const EKey D;
		static const EKey E;
		static const EKey F;
		static const EKey G;
		static const EKey H;
		static const EKey I;
		static const EKey J;
		static const EKey K;
		static const EKey L;
		static const EKey M;
		static const EKey N;
		static const EKey O;
		static const EKey P;
		static const EKey Q;
		static const EKey R;
		static const EKey S;
		static const EKey T;
		static const EKey U;
		static const EKey V;
		static const EKey W;
		static const EKey X;
		static const EKey Y;
		static const EKey Z;
		static const EKey Zero;
		static const EKey One;
		static const EKey Two;
		static const EKey Three;
		static const EKey Four;
		static const EKey Five;
		static const EKey Six;
		static const EKey Seven;
		static const EKey Eight;
		static const EKey Nine;
		static const EKey LeftSuper;
		static const EKey RightSuper;
		//what key is this? The one that looks like an arrow and menu.
		static const EKey Applications;
		static const EKey Numpad0;
		static const EKey Numpad1;
		static const EKey Numpad2;
		static const EKey Numpad3;
		static const EKey Numpad4;
		static const EKey Numpad5;
		static const EKey Numpad6;
		static const EKey Numpad7;
		static const EKey Numpad8;
		static const EKey Numpad9;
		static const EKey Multiply;
		static const EKey Add;
		static const EKey Subtract;
		static const EKey Decimal;
		static const EKey Divide;
		static const EKey F1;
		static const EKey F2;
		static const EKey F3;
		static const EKey F4;
		static const EKey F5;
		static const EKey F6;
		static const EKey F7;
		static const EKey F8;
		static const EKey F9;
		static const EKey F10;
		static const EKey F11;
		static const EKey F12;
		//the only keyboard I've seen with function keys past 12 is a Mac keyboard
		static const EKey F13;
		static const EKey F14;
		static const EKey F15;
		static const EKey F16;
		//even the Mac keyboard I have only goes this far (16)
		static const EKey F17;
		static const EKey F18;
		static const EKey F19;
		static const EKey F20;
		static const EKey F21;
		static const EKey F22;
		static const EKey F23;
		static const EKey F24;
		static const EKey NumLock;
		static const EKey ScrollLock;
		//the following are not used, at least on my keyboard. Pressing either shift key sends only Shift, for instance.
		static const EKey LeftShift;
		static const EKey RightShift;
		static const EKey LeftControl;
		static const EKey RightControl;
		static const EKey LeftAlt;
		static const EKey RightAlt;
		//end unused region
		static const EKey Semicolon;
		static const EKey Equals;
		static const EKey Comma;
		static const EKey Minus;
		static const EKey Period;
		static const EKey Slash;
		static const EKey Backquote;
		static const EKey LeftSquareBracket;
		static const EKey Backslash;
		static const EKey RightSquareBracket;
		static const EKey Quote;
	};
}

#endif