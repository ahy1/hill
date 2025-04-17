#ifndef TYPE_HPP_INCLUDED
#define TYPE_HPP_INCLUDED

#include <string>

namespace hill {

	struct type {
		virtual std::string str() {return "";}
	};

	struct undecided: type {
		static std::string str() {return "@undecided";}
	};

	struct i: type { // Integer literal of unspecified size
		static std::string str() {return "@i";}
	};

	struct u: type { // Unsigned integer literal of unspecified size
		static std::string str() {return "@u";}
	};

	struct f: type { //Floating point literal of unspecified size
		static std::string str() {return "@f";}
	};

	struct i32: type {
		static std::string str() {return "@i32";}
	};

	template<typename T> const type &type_o()
	{
		static T t;
		return t;
	}
}

#endif
