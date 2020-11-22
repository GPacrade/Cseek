#pragma once
#pragma once
#ifndef CSeek_modeule_pre_processor
#define CSeek_modeule_pre_processor
#include "str.h"
#include "error.h"
#include "defines.h"
#include "memory_check.h"
#include "behavior.h"
bool pre_processor_convert_vofd(str&, void (*f)(vofd_call), vofd_call);
bool pre_processor_convert_behavior(str&, void (*f)(behavior_agrs), behavior_agrs);
void pre_processor_add(error& err,str name, str args, str mask);
void pre_processor_serial_add(error& err, str string);
#endif