#include "str.h"
#include <cstdlib>
#include <cstring>
size_t str::use_size() {
	if (use)return use;
	size_t i = 0;
	while (arr[i++]);
	return i;
}


str* str::split(char splitter, size_t& size) {
	size_t i = 0;
	size_t strs = 0;
	str* res = (str*)malloc(size * sizeof(str));
	size_t used = 0;
	str tmp;
	if (res) {
		while (arr[i] && i<siz) {
			if (arr[i] == splitter) {
				if (used + 1 >= size) {
					size *= 2;
					str* narr = (str*)malloc(size * sizeof(str));
					if (narr) {
						while (i < used && i < size) {
							narr[i] = res[i];
							i++;
						}
						free(res);
						res = narr;
					}
				}
				if (res)res[used++] = str(tmp);
				tmp.clear();
			}
			tmp.add(arr[i++]);
		}
	}
	return res;
}


void str::add(const char string_s[]) {
	size_t s = 0;
	while (string_s[s]) {
		if (use+1 >= siz)realoc(siz * 2);
		arr[use++] = string_s[s++];
	}
	if (use + 1 >= siz)realoc(siz * 2);
	arr[use] = 0;
}
void str::add(const char string_s) {
	if (use + 1 >= siz)realoc(siz * 2);
	arr[use] = string_s;
	if (use + 1 >= siz)realoc(siz * 2);
	arr[use] = 0;
}
void str::add(const str string_s) {
	size_t s = 0;
	while (string_s.arr[s]) {
		if (use >= siz)realoc(siz * 2);
		arr[use++] = string_s.arr[s++];
	}
	if (use + 1 >= siz)realoc(siz * 2);
	arr[use] = 0;
}
bool str::realoc(size_t new_size=1) {
	size_t i = 0;
	char* narr = (char*)malloc(new_size+1 * sizeof(char));
	if (narr) {
		while (i < use && i < new_size && arr[i]) {
			narr[i] = arr[i];
			i++;
		}
		narr[use] = 0;

		siz = new_size;
		free(arr);
		arr = narr;
		return 1;
	}
	return 0;
}
void str::clear() {
	free(arr);
	arr = (char*)malloc(1 * sizeof(char));
	siz = 1;
	use = 0;
}
str::str(void) {
	arr = (char*)malloc(1 * sizeof(char));
	if (arr)arr[0] = '\0';
}

str::str(char* ch) {
	arr = ch;
	siz = use_size();
	use = siz;
}
str::str(const char ch[]) {
	arr = (char*)malloc(1 * sizeof(char));
	add(ch);
}
bool str::equal(const char* st) {
	if (arr && st)
		return !strcmp(arr, st);
	return false;
}
bool str::equal(str st) {
	if (arr && st.arr)
		return !strcmp(arr, st.arr);
	return false;
}