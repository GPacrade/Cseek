#include "pre_processor.h"
#include "behavior.h"
bool pre_process_session = 0;
char pre_process_add_session = 0;


struct ppc {
	str name, agr, mask;
	ppc(str n,str a,str m) {
		name = n;
		agr = a;
		mask = m;
	}
	ppc() {

	}
}tmp;
size_t ppc_size = 2;
size_t ppc_used = 1;
ppc* ppca = (ppc*)malloc(ppc_size * sizeof(ppc));
size_t find(str& name) {
	if (ppca) {
		for (size_t i = 1; i < ppc_used; i++)
			if (ppca[i].name.equal(name)) 
				return i;
	}
	return 0;
}
bool convert(str& in, str*& ou,size_t siz) {
	ppca[0] = ppc();
	str tmp0 = ppca[find(in)].mask;
	ou = tmp0.split(' ',siz);
	size_t po;
	bool changed = 0;
repeart:
	for (size_t i = 0; i < siz; i++) {
		if (po=find(ou[i])) {
			changed = 1;
			size_t sizn = 0;
			tmp0 = ppca[po].mask;
			str* pou = tmp0.split(' ', sizn);

			siz += sizn;
			str* nou = (str*)malloc(siz* sizeof(str));
			for (size_t j = 0; j < i; j++) 
				 nou[j] = ou[j];
			for(size_t j = 0; j < sizn; j++)
				nou[j+i] = pou[j+i];
			for (size_t j = i+sizn; j < siz; j++)
				nou[j] = ou[j];
		}
	}
	if (changed)goto repeart;
	if (siz == 1) return 1;
	return changed;
}
void pre_processor_add(error& err,str name, str agr, str mask) {
	if (ppc_size <= ppc_used) {
		ppc_size *= 2;
		ppc* new_s = (ppc*)malloc(ppc_size * sizeof(ppc));
		if (new_s) {
			for (size_t i = 0; i < ppc_size; i++)new_s[i] = ppca[i];
			free(ppca);
			ppca = new_s;
		}
	}
	if (ppc_size) ppca[ppc_used++] = ppc(name, agr, mask);
}
void pre_processor_serial_add(error& err,str string) {
	if (0 == pre_process_add_session)tmp.name = string;
	else if (1 == pre_process_add_session)tmp.agr = string;
	else if (2 == pre_process_add_session)tmp.mask = string;
	else {
		pre_processor_add(err,tmp.name, tmp.agr, tmp.mask); 
		pre_process_add_session = 0;
		return;
	}
	pre_process_add_session++;
}


bool pre_processor_convert_vofd(str& s, void (*f)(vofd_call), vofd_call) {
	str* output;
	size_t siz=0;
	bool res = convert(s, output, siz);
	for (size_t i = 0; i < siz; i++) {
		st = output[i];
		f(vofd_send);
	}
	return res;
}

bool pre_processor_convert_behavior(str& s, void (*f)(behavior_agrs), behavior_agrs) {
	str* output;
	size_t siz = 0;
	bool res=convert(s,output,siz);
	for (size_t i = 0; i < siz; i++) {
		st = output[i];
		f(behavior_call);
	}
	return res;
}





void pre_process_include(behavior_agrs) {

}

void pre_process_type(behavior_agrs) {
	if (st.equal("include"))beh.place(pre_process_include);
}
void behavior_new_define(behavior_agrs) {
	beh.place(pre_process_type);
}

