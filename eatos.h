#pragma once
#ifndef CSeek_eatos
#define CSeek_eatos

#include "str.h"
/// <summary>
/// enternal annouced types or structures,
/// used for headers
/// </summary>
struct eatos {
	str* main_ = (str*)malloc(1 * sizeof(str));
	size_t size = 1;
	size_t used = 0;


	bool realoc(size_t new_size = 1) {
		size_t i = 0;
		str* narr = (str*)malloc(new_size * sizeof(str));
		if (narr) {
			while (i < size && i < new_size && !main_[i].empty()) {
				narr[i] = main_[i];
				i++;
			}
			size = new_size;
			free(main_);
			main_ = narr;
			return 1;
		}
		return 0;
	}
	void declaration_add(const str string_s) {
		size_t s = 0;
		size_t inter = used;
		while (string_s.arr[s]) {
			if (inter >= size) { size *= 2; realoc(size); }
			main_[inter++] = string_s;
		}
	}
	void declaration_add(const char string_s[]) {
		str s;
		s.add(string_s);
	}
};

#endif