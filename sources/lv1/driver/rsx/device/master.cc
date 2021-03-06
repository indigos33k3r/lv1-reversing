/**
 * (c) 2016 The LV1RE Project.
 * Released under MIT license. Read LICENSE for more details.
 */

#include "master.h"

#include "lv1/driver/rsx/assert.h"
#include "lv1/driver/rsx/mmio.h"

/***********************************************************************
* 
***********************************************************************/
void rsx_device_master_init() {
    U64 rsx_rdcy_2 = 0;
    S32 flags;
    
    
    // get repo node value
    get_param_value("rsx.rdcy.2", &rsx_rdcy_2);
    
    
    rsx_wr32(RSX_PMC_ENABLE, 0xFFFFFFFF);
    
    flags = rsx_rd32(0x00001098);
    flags |= 0x20;                         // set flags[26:26]
    rsx_wr32(flags, 0x28000001098);
    
    flags = rsx_rd32(0x00001098);
    flags |= 0x40;                         // set flags[25:25]
    rsx_wr32(flags, 0x28000001098);
    
    flags = rsx_rd32(0x00001098);
    flags &= 0xFFFFFFF;                    // unset flags[00:03] 
    flags |= 0x20000000;                   // set flags[02:02]
    rsx_wr32(flags, 0x28000001098);
  
    flags = rsx_rd32(0x00001580);
    flags &= 0xCFFFFFFF;                   // unset flags[02:03]
    rsx_wr32(flags, 0x28000001580);
    
    flags = rsx_rd32(0x00001580);
    flags &= 0x30000000;                   // get flags[02:03]
  
    // if flags[02:03] not 0, error
    if (flags != 0) {
        printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
        return;
    }
  
    // based on repo node value "rsx.rdcy.2"
    if ((rsx_rdcy_2 & 1) == 0) {                 // "rsx.rdcy.2" == 0("clock gate: DISABLE") 
    flags = rsx_rd32(0x00001588);
        flags &= 0xFFFFFFFC;                   // unset flags[30:30] and flags[31:31]
        rsx_wr32(flags, 0x28000001588);
        
        flags = rsx_rd32(0x00001588);
        flags &= 0xFFFFFFF3;                   // unset flags[28:28] and flags[29:29]
        rsx_wr32(flags, 0x28000001588);
        
        flags = rsx_rd32(0x00001588);
        flags &= 0xFFFFFFCF;                   // unset flags[26:26] and flags[27:27]
        rsx_wr32(flags, 0x28000001588);
        
        flags = rsx_rd32(0x00001590);
        flags &= 0xFFFFFFFC;                   // unset flags[30:30] and flags[31:31]
        rsx_wr32(flags, 0x28000001590);
    }
    else  {                                  // "rsx.rdcy.2" == 1("clock gate: ENABLE")
        flags = rsx_rd32(0x00001588);
        flags &= 0xFFFFFFFC;                   // unset flags[30:30] and flags[31:31]
        flags |= 1;                            // set flags[31:31]
        rsx_wr32(flags, 0x28000001588);
        
        flags = rsx_rd32(0x00001588);
        flags &= 0xFFFFFFF3;                   // unset flags[28:28] and flags[29:29]
        flags |= 4;                            // set flags[29:29]
        rsx_wr32(flags, 0x28000001588);
        
        flags = rsx_rd32(0x00001588);
        flags &= 0xFFFFFFCF;                   // unset flags[26:26] and flags[27:27]
        flags |= 0x10;                         // set flags[27:27]
        rsx_wr32(flags, 0x28000001588);
        
        flags = rsx_rd32(0x00001590);
        flags &= 0xFFFFFFFC;                   // unset flags[30:30] and flags[31:31]
        flags |= 1;                            // set flags[31:31]
        rsx_wr32(flags, 0x28000001590);
    }
  
  
    flags = rsx_rd32(0x00001588);
    flags &= 0xFFFFFCFF;                     // unset flags[22:22] and flags[23:23]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xFFFFF3FF;                     // unset flags[20:20] and flags[21:21]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xFFFFCFFF;                     // unset flags[18:18] and flags[19:19]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xFFFF3FFF;                     // unset flags[16:16] and flags[17:17]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xFFFCFFFF;                     // unset flags[14:14] and flags[15:15]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xFFF3FFFF;                     // unset flags[12:12] and flags[13:13]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xFFCFFFFF;                     // unset flags[10:10] and flags[11:11]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xFF3FFFFF;                     // unset flags[08:08] and flags[09:09]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xFCFFFFFF;                     // unset flags[06:06] and flags[07:07]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xF3FFFFFF;                     // unset flags[04:04] and flags[05:05]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0xCFFFFFFF;                     // unset flags[02:02] and flags[03:03]
    rsx_wr32(flags, 0x28000001588);
    
    flags = rsx_rd32(0x00001588);
    flags &= 0x3FFFFFFF;                     // unset flags[00:00] and flags[01:01]
    rsx_wr32(flags, 0x28000001588);
    
    
    flags = rsx_rd32(0x0000158C);
    flags &= 0xFFFFFFFC;                     // unset flags[30:30] and flags[31:31]
    rsx_wr32(flags, 0x2800000158C);
    
    flags = rsx_rd32(0x0000158C);
    flags &= 0xFFF0FFFF;                     // unset flags[12:15]
    flags |= 0x40000;                        // set flags[13:13]
    rsx_wr32(flags, 0x2800000158C);
    
    flags = rsx_rd32(0x0000158C);
    flags &= 0xC00FFFFF;                     // unset flags[02:11]
    flags |= 0x400000;                       // set flags[09:09]
    rsx_wr32(flags, 0x2800000158C);
    
    flags = rsx_rd32(0x00001530);
    flags &= 0xFFFFFFF0;                     // unset flags[28:31]
    flags |= 7;                              // set flags[29:31]
    rsx_wr32(flags, 0x28000001530);
    
    flags = rsx_rd32(RSX_PMC_INTR_EN_0);
    flags &= 0xFFFFFFFC;                     // unset flags[30:30] and flags[31:31]
    flags |= 1;                              // set flags[31:31]
    rsx_wr32(RSX_PMC_INTR_EN_0, flags);
}
