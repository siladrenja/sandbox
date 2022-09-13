#pragma once
#include <string>
#include <cwctype>
#include <algorithm>


namespace extstd {
	
	template <class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
	class Basic_String : public std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> {

	public:

		using std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>>::basic_string;

		inline bool StartsWith(std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> subStr) {
#if _HAS_CXX20
			return this->starts_with(subStr);

#else
			if (this->rfind(subStr, 0) == 0) {
				return true;
			}
			return false;
#endif
		}
		inline bool StartsWith(std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> subStr[]) {
#if _HAS_CXX20
			return this->starts_with(subStr);

#else
			if (this->rfind(subStr, 0) == 0) {
				return true;
			}
			return false;
#endif
			
		}
		inline bool EndsWith(std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> subStr) {
#if _HAS_CXX20
			return this->ends_with(subStr);
#else
			if (this->length() >= subStr.length()) {
				return (this->compare(this->length() - subStr.length(), subStr.length(), subStr) == 0);
			} else {
				return false;
			}
#endif
		}

		inline void prepend(std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> PrepString) {
			this->insert(0, PrepString);
			std::string st;
			
		}

		using push_front = this->prepend;

		inline std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> toLower() {
			Basic_String<_Elem, char_traits<_Elem>, allocator<_Elem>> __copy(*this);
			std::transform(
				(__copy.begin()),
				(__copy.end()),
				(__copy.begin()),
				tolower
			);
			return __copy;
		}
		inline std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> toUpper() {
			Basic_String<_Elem, char_traits<_Elem>, allocator<_Elem>> __copy(*this);
			std::transform(
				(__copy.begin()),
				(__copy.end()),
				(__copy.begin()),
				toupper
			);
			return __copy;
		}
		inline std::string toGenericString(char ReplaceWith = 0) {
			std::string out;
			for (int i = 0; i < this->length(); i++) {
				if (static_cast<unsigned char>((*this)[i]) > 127) {
					if (ReplaceWith) out.push_back(ReplaceWith);
				} else {
					out.push_back((*this)[i]);
				}
			}

			return out;
		}
		
		Basic_String<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> operator=(std::basic_string<_Elem, std::char_traits<_Elem>, std::allocator<_Elem>> a) {
			this->clear();
			this->append(a);
			return *this;
		}
		

		
	};

	using String = Basic_String<char, std::char_traits<char>, std::allocator<char>>;
	using wString = Basic_String<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;
}