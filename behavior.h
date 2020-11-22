#pragma once
#ifndef CSeek_behavior
#define CSeek_behavior
#include "error.h"
#include "memory_check.h"
#include "str.h"
#include "defines.h"
#include "points.h"
#include "eatos.h"
struct behavior_t;
#define behavior_agrs error& err,str st, behavior_t beh, spaces sp, default_mems mem,eatos& eatos_data,space& was_space,bool& is_last
#define behavior_call err,st, beh, sp, mem,eatos_data, was_space,is_last

/// <summary>
/// used for easy naming 
/// </summary>
typedef void(*behavior_funct)(behavior_agrs);

/// <summary>
/// behavior queue (first join,last out)
/// </summary>
struct behavior_t {
	size_t size = 40;
	size_t used = 0;
	behavior_funct* behavior_aloc = (behavior_funct*)malloc(size * sizeof(behavior_funct));
	void place(behavior_funct value) {
		if (size <= used) {
			size *= 2;
			behavior_funct* new_s = (behavior_funct*)malloc(size * sizeof(behavior_funct));
			if (new_s) {
				for (size_t i = 0; i < size; i++)new_s[i] = behavior_aloc[i];
				free(behavior_aloc);
				behavior_aloc = new_s;
			}
		}
		if (behavior_aloc) behavior_aloc[used++] = value;
	}
	void call(behavior_agrs) {
		if (used == 0)return;
		behavior_aloc[--used](behavior_call);
	}
};

/// <summary>
/// used for global space behavior checker
/// </summary>
void main_bbt0(str st,all_call);

/// <summary>
/// used start decl structure
/// </summary>
void behavior_new_structure(behavior_agrs);
/// <summary>
/// reserved for future,
/// used for get headers and "#if" e.t.c.
/// </summary>
void behavior_new_define(behavior_agrs);

/// <summary>
/// annouce function in was_space(default global)
/// </summary>
void behavior_annouce_function(behavior_agrs);
#endif