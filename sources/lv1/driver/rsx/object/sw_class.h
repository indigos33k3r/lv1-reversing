/**
 * (c) 2016 The LV1RE Project.
 * Released under MIT license. Read LICENSE for more details.
 */

#pragma once

#include "common/types.h"


U32 rsx_object_sw_class_get_object_class(rsx_sw_class_obj_t* sw_obj);
S64 rsx_object_sw_class_get_BAR2_address(rsx_sw_class_obj_t* sw_obj);
void rsx_object_sw_class_create_object(rsx_sw_class_obj_t* sw_obj, U32 type, S64 *opd);


#endif // __RSX_OBJECT_SW_CLASS_H__
