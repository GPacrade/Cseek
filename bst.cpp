//behavior structure test
#include "behavior.h"
/// <summary>
/// using for lazy naming structures
/// </summary>
str aloc_name;
/// <summary>
/// using for save unique unnamed structures
/// </summary>
unsigned long long unnamed_structures = 0;
/// <summary>
/// queue of space declarations
/// </summary>
struct {
	size_t size = 1;
	size_t used = 0;
	space* tna = (space*)malloc(size * sizeof(space));
	void join(space value) {
		if (size <= used) {
			size *= 2;
			space* new_s = (space*)malloc(size * sizeof(space));
			if (new_s&&tna) {
				for (size_t i = 0; i < size; i++)new_s[i] = tna[i];
				free(tna);
				tna = new_s;
			}
		}
		if (tna) tna[used++] = value;
	}
	void out() {
		if(used) used--;
		if (size/2 >= used) {
			size /= 2;
			if (!size)size = 1;
			space* new_s = (space*)malloc(size * sizeof(space));
			if (new_s&&tna) {
				for (size_t i = 0; i < size; i++)new_s[i] = tna[i];
				free(tna);
				tna = new_s;
			}
		}
	}
	space& get() {
		if (tna) goto try_aloc;
	run:
		if (used)
			return tna[used - 1];
		else join(space());
		return tna[used - 1];
	try_aloc:
		tna = (space*)malloc((size=1) * sizeof(space));
		if (tna) goto run;
	}
} queue_of_declarations;




/// <summary>
/// check exist ';' symboi or not,
/// if not it place error in queue
/// </summary>
void behavior_new_structure_finally_final(behavior_agrs) {
	if (!st.equal(";"))
		err.out("not ended structure declaration");
}

/// <summary>
/// check exist ';' symboi or not,
/// if not it alocate this structure and place finally final behavior in queue
/// </summary>
void behavior_new_structure_final(behavior_agrs) {
	space tmp = queue_of_declarations.get();
	queue_of_declarations.out();
	if (queue_of_declarations.used != 0)
		queue_of_declarations.get().sps->place(tmp);
	else sp.place(tmp);
	if (!st.equal(";")) {

	}
}


/// <summary>
/// reserved for future, 
/// it will be add functions e.t.c. in space for info to need alocate values
/// </summary>
void behavior_new_structure_contain(behavior_agrs) {
	if(st.equal("}"))
		beh.place(behavior_new_structure_final);
	else 
		beh.place(behavior_new_structure_contain);
}

/// <summary>
/// check exist '{' symboi or not if not it place error in queue
/// </summary>
void behavior_new_structure_pre_contain(behavior_agrs) {
	if (st.equal("{")) {
		beh.place(behavior_new_structure_contain);
		return;
	}
	err.out("wrong argument");
}
/// <summary>
/// check exist ';'/'{' symboi or not,
/// if not '{' it set name structure
/// if ';' it place error in queue
/// </summary>
void behavior_new_structure_tname(behavior_agrs) {
	if (st.equal(";"))
		err.out("empty stucture", 0);
	else if (!st.equal("{")) {
		queue_of_declarations.get().name = st;
		beh.place(behavior_new_structure_contain);
	}
	else {
		char bufigigigii[255];
		snprintf(bufigigigii, 255, "%llu", unnamed_structures);
		str tr("unnamed_struct_");
		tr.add(bufigigigii);
		queue_of_declarations.get().name = tr;
		beh.place(behavior_new_structure_pre_contain);
	}
}
void behavior_new_structure(behavior_agrs) {
	beh.place(behavior_new_structure_tname);
	queue_of_declarations.join(space());
}
