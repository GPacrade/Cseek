//behavior brackets type 0
#include "behavior.h"
#include <cstring>
#include "pre_processor.h"
#include "error.h"
#include "declaration.h"
behavior_t beh;
spaces sp;
default_mems mem;
str bef_st;
bool after_start_page=0;


void main_bbt0(str st,all_call){
	if (st.equal("#") &&( bef_st.equal("\n")|| !after_start_page))behavior_new_define(behavior_call);
	else if (st.equal("#")) err.out("define not matched here");
	if (beh.used == 0) 
		return vofd(mem,sp,err, bef_st, st, sp.tna[0], is_last,eatos_data,beh);
	beh.call(behavior_call);
	after_start_page = 1;
}