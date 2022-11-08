#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <locale>

using std::vector;
using std::string;
using std::size_t;
using std::allocator;
using std::back_inserter;
using std::find;
using std::distance;
using std::copy_if;

class TextHelper {
private:
	static inline void ltrim(string& s) {
		s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));
	}

	static inline void rtrim(string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	static inline void trim(string& s) {
		ltrim(s);
		rtrim(s);
	}
public:
	static int getIndex(vector<string> elements, string target) {
		vector<string>::iterator it;
		it = find(elements.begin(), elements.end(), target);
		return it != elements.end()
			? distance(elements.begin(), it)
			: -1;
	}

	template< template<typename, typename> class Container, typename Separator >
	static Container<string, allocator<string> > split(const string& line, Separator sep) {
		size_t pos = 0;
		size_t next = 0;
		Container<string, allocator<string> > fields;
		while (next != string::npos) {
			next = line.find_first_of(sep, pos);
			string field = next == string::npos ? line.substr(pos) : line.substr(pos, next - pos);
			fields.push_back(field);
			pos = next + 1;
		}
		return fields;
	}

	template <typename Cont, typename Pred>
	Cont filter(const Cont& container, Pred predicate) {
		Cont result;
		copy_if(container.begin(), container.end(), back_inserter(result), predicate);
		return result;
	}

	static inline string trim_copy(string s) {
		trim(s);
		return s;
	}

	static inline bool contains(vector<string> v, const string& element) {
		return (find(v.begin(), v.end(), element) != v.end());
	}

	void ReplaceStringInPlace(string& subject, const string& search, const string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
	}
};