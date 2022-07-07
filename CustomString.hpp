#pragma once
#include <string>
#include <cwctype>
#include <algorithm>


namespace extstd {
	
	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	class Basic_String : public std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> {

	public:

		using std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>>::basic_string;

		inline bool StartsWith(Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> subStr) {
			if (this->rfind(subStr, 0) == 0) {
				return true;
			}
			return false;
		}
		inline bool StartsWith(Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> subStr[]) {
			if (this->rfind(subStr, 0) == 0) {
				return true;
			}
			return false;
		}
		inline bool EndsWith(Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> subStr) {
			if (this->length() >= subStr.length()) {
				return (this->compare(this->length() - subStr.length(), subStr.length(), subStr) == 0);
			} else {
				return false;
			}
		}
		inline void prepend(Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> PrepString) {
			this->insert(0, PrepString);
		}
		inline Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> toLower() {
			Basic_String<_Elem, char_traits<_Elem>, allocator<_Elem>> __copy(*this);
			std::transform(
				(__copy.begin()),
				(__copy.end()),
				(__copy.begin()),
				tolower
			);
			return __copy;
		}
		inline Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> toUpper() {
			Basic_String<_Elem, char_traits<_Elem>, allocator<_Elem>> __copy(*this);
			std::transform(
				(__copy.begin()),
				(__copy.end()),
				(__copy.begin()),
				toupper
			);
			return __copy;
		}
		inline std::string toGenericString(bool DeleteCharacters) {
			std::string out;
			for (int i = 0; i < this->length(); i++) {
				if (static_cast<unsigned char>((*this)[i]) > 127) {
					if (!DeleteCharacters) out.push_back('?');
				} else {
					out.push_back((*this)[i]);
				}
			}

			return out;
		}
		Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> operator=(Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> a) {
			this->clear();
			this->append(a);
			return *this;
		}
		
		inline Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> ToLower() {
			Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> temp;
			for (const char& c : *this) {
				temp.push_back(std::tolower(c));
			}
		}

		inline Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> ToUpper() {
			Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> temp;
			for (const char& c : *this) {
				temp.push_back(std::toupper(c));
			}
		}

		
	};

	using String = Basic_String<char, std::char_traits<char>, std::allocator<char>>;
	using wString = Basic_String<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;
}