#pragma once
#ifndef CSeek_memory_check
#define CSeek_memory_check
#include <cstdlib>
#include "str.h"
#include "size_t.h"

///<summary>default mem types:
/// 0-pointer
/// 1-int
/// 2-real int
/// 3-array
/// 4-struct
/// 5-function
/// 6-pointer type array</summary>
struct L_mem {
	void* value = 0;
	size_t size = 0;
	size_t tsize = 0;
	char type = 0;
	str type_name;
	//2 - out of array
	//1 - this memory not array
	//0 - no err
	L_mem() {}
	L_mem& get(size_t array_point) {
		if (type == 3)
			if (array_point < size)
				return ((L_mem*)value)[array_point];
		return *this;
	}
	L_mem& get() {
		return *this;
	}
};
/// <summary>0-default
/// 1-stacic value
/// 2-const value
/// 3-static pointer
/// 4-const pointer
/// 5-static link
/// 6-const link
/// 7-stacic const value
/// 8-static const pointer
/// 9-static const link</summary>
struct default_mem {
	char type=0;
	L_mem val;
	str name;
};
struct default_mems {
	size_t size = 1;
	size_t used = 0;
	default_mem* tna = (default_mem*)malloc(size * sizeof(default_mem));
	void place(default_mem value) {
		if (size <= used) {
			size *= 2;
			default_mem* new_s = (default_mem*)malloc(size * sizeof(default_mem));
			if (new_s) {
				for (size_t i = 0; i < size; i++)new_s[i] = tna[i];
				free(tna);
				tna = new_s;
			}
		}
		if (tna) tna[used++] = value;
	}
	size_t find_point(str name) {
		if (tna) {
			for (size_t i = 0; i < size; i++)
				if (tna[i].name.equal(name)) {
					return i;
				}
		}
	}
	void aloc(str type_name,str full_name) {

	}
};

struct function_argument {
	str type;
	str name;
};


struct function {
	str* function_arguments;
	str name;
	str space_path;
	unsigned int pos = 0;
	str return_type;
};
struct functions {
	size_t size = 1;
	size_t used = 0;
	function* tna = (function*)malloc(size * sizeof(function));
	void place(function value) {
		if (size <= used) {
			size *= 2;
			function* new_s = (function*)malloc(size * sizeof(function));
			if (new_s) {
				for (size_t i = 0; i < size; i++)new_s[i] = tna[i];
				free(tna);
				tna = new_s;
			}
		}
		if (tna) tna[used++] = value;
	}
	size_t find_point(str name) {
		if (tna) {
			for (size_t i = 0; i < size; i++)
				if (tna[i].name.equal(name)) {
					return i;
				}
		}
	}
};
struct spaces;
struct space {
	functions func;
	default_mems mem;
	str name;
	spaces* sps=nullptr;
	spaces* back = nullptr;
	bool
		allow_aloc_mem,
		allow_commands;
};
struct spaces {
	size_t size = 1;
	size_t used = 0;
	space* tna = (space*)malloc(size * sizeof(space));
	void place(space value) {
		if (size <= used) {
			size *= 2;
			space* new_s = (space*)malloc(size * sizeof(space));
			if (new_s) {
				for (size_t i = 0; i < size; i++)new_s[i] = tna[i];
				free(tna);
				tna = new_s;
			}
		}
		if (tna) tna[used++] = value;
	}
	size_t find_point(str name) {
		if (tna) {
			for (size_t i = 0; i < size; i++)
				if (tna[i].name.equal(name)) {
					return i;
				}
		}
		return 0;
	}
};
/// <summary>
/// reserved for future
/// </summary>
struct tname {
	str name;
	str type;
};

/// <summary>
/// reserved for future
/// </summary>
struct tnames{
	size_t size = 1;
	size_t used = 0;
	tname* tna = (tname*)malloc(size * sizeof(tname));
	void place(tname value) {
		if (size <= used) {
			size *= 2;
			tname* new_s = (tname*)malloc(size * sizeof(tname));
			if (new_s) {
				for (size_t i = 0; i < size; i++)new_s[i] = tna[i];
				free(tna);
				tna = new_s;
			}
		}
		if (tna) tna[used++] = value;
	}
	size_t find_point(str name) {
		if (tna) {
			for (size_t i = 0; i < size; i++)
				if (tna[i].name.equal(name)) {
					return i;
				}
		}
	}
};

#endif