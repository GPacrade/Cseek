#pragma once
#ifndef CSeek_defines
#define CSeek_defines
#include "eatos.h"
#include "memory_check.h"
#define all_call char symboi, points*& stack, size_t& size, size_t& used, bool& t_symboi, bool& in_str,bool change_space,error& err,bool& is_last,eatos& eatos_data,space&was_space
#define all_send symboi,stack,size,used,t_symboi,in_str,change_space,err,is_last,eatos_data,was_space

#define vofd_call default_mems& mem,spaces& sp,error& err,str&before_st,str &st,space& was_space,bool& is_last,eatos& eatos_data,behavior_t& beh
#define vofd_send mem,sp,err,before_st,st,was_space,is_last,eatos_data,beh

#define open_bracket symboi == '{' || symboi == '('
#define close_bracket symboi == '}' || symboi == ')'
#define not_word  symboi == '#' || symboi == '@' || symboi == '%'|| symboi == '^' || symboi == '?' || symboi == '='|| symboi == '-'|| symboi == '!'|| symboi == '~'|| symboi == '`'|| symboi == ':'|| symboi == ';'|| symboi == ','|| symboi == '.'|| symboi == '|'|| symboi == ' ' || symboi =='\r' || symboi =='\t'|| symboi =='\0'|| symboi == '{'|| symboi == '('|| symboi == '}'|| symboi == ')'||symboi == '\n'
#define once_word  symboi == '#' || symboi == '%'|| symboi == '^'|| symboi == '='|| symboi == '-'|| symboi == '!'|| symboi == '~'|| symboi == ':'|| symboi == ';'|| symboi == ','|| symboi == '.'|| symboi == '{'|| symboi == '('|| symboi == '}'|| symboi == ')'
#endif