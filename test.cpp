#include "str.h"
#include "pre_processor.h"
#include <string.h>
#include "declaration.h"
#include "behavior.h"
//enternal annouced types or structures
str type_name_full;
bool can_check = 0;
bool start = 1;
bool try_annouce = 0;
bool after_annouce = 0;
bool need_value = 0;
#define is_type st.equal("long") || st.equal("float") || st.equal("double") || st.equal("bool") || st.equal("char") || st.equal("short") || st.equal("int") 
bool first_check_module(error& err,str &s) {
	can_check = 1;
	if (start) {
		start = 0;
		type_name_full.clear();
		if (s.equal("unsigned"))  {type_name_full.add("unsigned");return 1;}
		else if (s.equal("long")) {type_name_full.add("long");return 1;}
		else if (s.equal("short")){type_name_full.add("short");return 1;}
		else if (s.equal("char")) {type_name_full.add("char");return 1;}
		else if (s.equal("int")) { type_name_full.add("int");  return 1; }
		else if (s.equal("double")) { type_name_full.add("double");  return 1; }
		else if (s.equal("float")) { type_name_full.add("float");  return 1; }
		else if (s.equal("void")) { type_name_full.add("void");  return 1; }
		else { can_check = 0; start = 1; }
	}
	else if (type_name_full.equal("unsigned")) {
		if (s.equal("long")) { type_name_full.clear(); type_name_full.add("unsigned long"); return 1;}
		else if (s.equal("short")) { type_name_full.clear(); type_name_full.add("unsigned short"); return 1;}
		else if (s.equal("char")) { type_name_full.clear(); type_name_full.add("unsigned char"); return 1;}
		else if (s.equal("int")) { type_name_full.clear(); type_name_full.add("unsigned int"); return 1;}
		else can_check = 0;
	}
	else if (type_name_full.equal("unsigned long long")) {
		if (s.equal("int")) { type_name_full.clear(); type_name_full.add("unsigned long long int"); return 1; }
		else can_check = 0;
	}
	else if (type_name_full.equal("unsigned long")) {
		if (s.equal("long")) { type_name_full.clear(); type_name_full.add("unsigned long long"); return 1;}
		else if (s.equal("int")) { type_name_full.clear(); type_name_full.add("unsigned long int");  return 1; }
		else can_check = 0;
	}
	else if (type_name_full.equal("unsigned short")) {
		if (s.equal("int")) { type_name_full.clear(); type_name_full.add("unsigned short int");  return 1;}
		else can_check = 0;
	}
	else if (type_name_full.equal("unsigned char")) {
		if (s.equal("int")) { type_name_full.clear(); type_name_full.add("unsigned char int");  return 1; }
		else can_check = 0;
	}
	else if (type_name_full.equal("long")) {
		if (s.equal("long")) { 
			type_name_full.clear(); 
			type_name_full.add("long long"); 
			return 1;}
		else if (s.equal("double")) { type_name_full.clear(); type_name_full.add("long double");  return 1; }
		else if (s.equal("float")) { type_name_full.clear(); type_name_full.add("long float");  return 1; }
		else if (s.equal("int")) { type_name_full.clear(); type_name_full.add("long int");  return 1;}
		else can_check = 0;
	}
	else if (type_name_full.equal("long long")) {
		if (s.equal("int")) { type_name_full.clear(); type_name_full.add("long long int");  return 1; }
		else can_check = 0;
	}
	else if (type_name_full.equal("short")) {
		if (s.equal("int")) { type_name_full.clear(); type_name_full.add("short int");  return 1;}
		else can_check = 0;
	}
	else if (type_name_full.equal("char")) {
		if (s.equal("int")) { type_name_full.clear(); type_name_full.add("char int");  return 1; }
		else can_check = 0;
	}
	else if (type_name_full.equal("void")){
		if (s.equal("*")) {
			type_name_full.add("*");
		}
		can_check = 0;
		return 0;
	}
	else can_check = 0;
	if (!can_check) {
		if (s.equal("&")) type_name_full.add("&");
		else if (s.equal("*")) {
			if (type_name_full.arr[type_name_full.use_size() - 1] == '&')err.out("Pointer of links not allowed by std");
			type_name_full.add("*");
		}
		else return 0;
		can_check = 1;
	}
	return 0;
}


void vofd(vofd_call) {
	if (st.equal("\n") || st.equal("\t") || st.equal(" ")) goto end;
	if (pre_processor_convert_vofd(st, vofd,vofd_send));
	else{
		if (st.equal("struct"));
		else if (st.equal("(")) {
			if (after_annouce)
				behavior_annouce_function(behavior_call);
			else err.out("that not function, remove '(' for fix");
		}
		else if (first_check_module(err, st));
		else if (st.equal("=")) {
			if (after_annouce) {need_value = 1; after_annouce = 0; return;}
			else err.out("that not value, remove '=' for fix");
		}
		else if (st.equal(";")|| st.equal("}")) {
			if (try_annouce) err.out("incomplete expression");
			if(need_value)err.out("missing number");
			type_name_full.clear();
			start = 1;
			after_annouce = 0;
			try_annouce = 0;
			need_value = 0;
			start = 1;
			if (st.equal("}") && !before_st.equal(";") && !before_st.equal("{"))
				err.out("incomplete command");
		}
		else if(is_last){ if (st.equal("}") && ((!before_st.equal(";")))) err.out("incomplete command"); }
		else if (need_value) {
			long long r;
			if(!st.to_number(r))err.out("missing number");
			need_value = 0;
		}
		else {
			if (!can_check) try_annouce = 1;
			if (type_name_full.empty())
				for (size_t i = 0; i < eatos_data.size; i++) {
					if (eatos_data.main_[i].equal(st))try_annouce = 1;
				}
			if (try_annouce) {
				if(is_type){ err.out("type name cannont be named like type, fail initalize value"); type_name_full.clear();}
				else {
					was_space.mem.aloc(type_name_full, st);
					type_name_full.clear();
					try_annouce = 0;
					after_annouce = 1;
					goto end;
				}
			}
		}
	}
end:
	before_st.clear();
	before_st.add(st);
}