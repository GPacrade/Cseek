#pragma once
#ifndef CSeek_str
#define CSeek_str
#include <cstdlib>
#include "size_t.h"

/// <summary>
/// i love c++ and c# string style manage :)
/// </summary>
struct str {
	char* arr=nullptr;
	size_t siz = 1;
	size_t use = 0;
	size_t use_size();
	str* split(char splitter, size_t& size);
	void add(const char string_s);
	void add(const char string_s[]);
	void add(const str);
	bool realoc(size_t new_size);
	void clear();
	str(void);
	str(char* ch);
	str(const char ch[]);
	bool equal(str);
	bool equal(const char*);
	inline bool empty() { return !arr[0]; }
};
#endif