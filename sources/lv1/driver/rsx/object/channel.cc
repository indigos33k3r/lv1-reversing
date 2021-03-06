/**
 * (c) 2016 The LV1RE Project.
 * Released under MIT license. Read LICENSE for more details.
 */

#include "channel.h"

S64 rsx_object_channel_t::get_dma_control_lpar_address() {
	rsx_core_device_t *core = NULL;
	rsx_device_fifo_t *fifo = NULL;
	
	
	// get RSX device core
	core = rsx_core_device_get_core_object_by_id(g_rsx_core_id);
    if(core == NULL) {
	    printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
        return 0;
    }
	
	// get RSX device core FIFO object
	fifo = (void*)core->fifo;
	 
	return rsx_device_fifo_get_channel_dma_control_lpar_address((void*)fifo, id);
}

/***********************************************************************
* 
***********************************************************************/
S32 rsx_object_channel_get_id()
{
	return ch_obj->id;
}

/***********************************************************************
* 
***********************************************************************/
void rsx_object_channel_t::create_sw_object_hash_table_entry(rsx_object_sw_class_t *sw_obj)
{
	U32 class;
	S64 bar2_addr;
	S32 bar2_offset;
	rsx_core_device_t *core = NULL;
	rsx_core_memory_t *core_mem = NULL;
	rsx_hash_tbl_obj_t *hash_tbl = NULL;
	
	
	// if no sw object, error
	if(sw_obj == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
	
	// get RSX device core
	core = rsx_core_device_get_core_object_by_id(g_rsx_core_id);
  if(core == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
  
  // get RSX device core memory object
	core_mem = (void*)core->core_mem;
	
	// get RSX device core hash table object
	hash_tbl = (void*)core->obj_hash_tbl_obj;
	
	// get sw object class
  class = rsx_object_sw_class_get_object_class((void*)sw_obj);
	
	// get sw object BAR2 address
	bar2_addr = rsx_object_sw_class_get_BAR2_address((void*)sw_obj);
	//printf("bar2_addr: 0x%016llX\n", bar2_addr); // missing
	
	// get sw object offset into BAR2
	bar2_offset = rsx_core_memory_get_BAR2_offset_by_address((void*)core_mem, bar2_addr);
	
	// create sw object hash table entry
	rsx_object_hash_table_create_entry((void*)hash_tbl, id, class, bar2_offset, 2);
	
	return;
}

/***********************************************************************
* 
***********************************************************************/
void rsx_object_channel_t::create_nv_object_hash_table_entry(rsx_object_nv_class_t* nv_obj)
{
	U32 class;
	S64 bar2_addr;
	S32 bar2_offset;
	rsx_core_device_t *core = NULL;
	rsx_core_memory_t *core_mem = NULL;
	rsx_hash_tbl_obj_t *hash_tbl = NULL;
	
	
	// if no nv object, error
	if(nv_obj == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
	
	// get RSX device core
	core = rsx_core_device_get_core_object_by_id(g_rsx_core_id);
  if(core == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
  
  // get RSX device core memory object
	core_mem = (void*)core->core_mem;
	
	// get RSX device core hash table object
	hash_tbl = (void*)core->obj_hash_tbl_obj;
	
	// get nv object class
  class = rsx_object_nv_class_get_object_class((void*)nv_obj);
	
	// get dma object BAR2 address
	bar2_addr = rsx_object_nv_class_get_BAR2_address((void*)nv_obj);
	
	// get nv object offset into BAR2
	bar2_offset = rsx_core_memory_get_BAR2_offset_by_address((void*)core_mem, bar2_addr);
	
	// create nv object hash table entry
	rsx_object_hash_table_create_entry((void*)hash_tbl, ch_obj->id, class, bar2_offset, 1);
	
	return;
}


/***********************************************************************
* 
***********************************************************************/
void rsx_object_channel_create_dma_object_hash_table_entry(rsx_object_context_dma_t *dma_obj)
{
	U32 class;
	S64 bar2_addr;
	S32 bar2_offset;
	rsx_core_device_t *core = NULL;
	rsx_core_memory_t *core_mem = NULL;
	rsx_hash_tbl_obj_t *hash_tbl = NULL;
	
	
	// if no dma object, error
	if(dma_obj == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
  
  // get RSX device core
	core = rsx_core_device_get_core_object_by_id(g_rsx_core_id);
  if(core == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
  
  // get RSX device core memory object
	core_mem = (void*)core->core_mem;
	
	// get RSX device core hash table object
	hash_tbl = (void*)core->obj_hash_tbl_obj;
  
  // get dma object class
  class = rsx_object_context_dma_get_object_class((void*)dma_obj);
	
  // get dma object BAR2 address
	bar2_addr = rsx_object_context_dma_object_get_BAR2_address((void*)dma_obj);
	
	// get dma object offset into BAR2
	bar2_offset = rsx_core_memory_get_BAR2_offset_by_address((void*)core_mem, bar2_addr);
	
	// create dma object hash table entry
	rsx_object_hash_table_create_entry((void*)hash_tbl, ch_obj->id, class, bar2_offset, 1);
  
	return;
}


/***********************************************************************
* 
***********************************************************************/
static S32 rsx_object_channel_t::sub2209B0() {
	rsx_core_device_t *core = NULL;
	rsx_device_fifo_t *fifo = NULL;
	
	
	// get RSX device core
	core = rsx_core_device_get_core_object_by_id(g_rsx_core_id);
  if(core == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return 0;
  }
	
	// get device core FIFO object
	fifo = (void*)core->fifo;
	if(fifo == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return 0;
  }
	
	/**/
	S64 ret1, ret2, ret3;
	S64 r11 = 0, r31 = 0, r3 = 0, r9 = 0;
	
	// ?
	ret1 = rsx_device_fifo_21B7DC((void*)fifo, 1);  // ? ret 0x80
	ret2 = rsx_device_fifo_21B7DC((void*)fifo, 2);  // ? ret 0x80
	ret3 = rsx_device_fifo_21B7DC((void*)fifo, 3);  // ? ret 8
	
	
	printf("TODO: nested loop... [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
	
	
	if(ret1 > 7)
	{
		r11 = 0xF8;
		
		if(ret1 <= 0x100)
		{
      goto loc_220A3C;
		}
		else                            // ret1 > 0x100
		{
			r3 = ret2;
			if(ret2 <= 0x1F)
			{
				
			}
		}
	}
	else
	{
		r31 = 8;
		goto loc_220A3C;
	}
	
	
	
	
loc_220A3C:
	r9 = r31 <<3;
	r9--;
	r3 = ret2;
	r11 = (r9 & 0x3F) <<3;
	
	if(ret2 > 0x1F)
	{
		goto loc_220AB8;
	}
	else                // ret2 <= 0x1F
	{
		r3 = 0x20;
		goto loc_220A58;
	}
	
	
loc_220AB8:
	r9 = 0xE000;
	if(ret2 <= 0x100)
	{
		r3 = 0x20;
		goto loc_220A58;
	}
	
	
	
loc_220A58:
  r9 = r3 >>5;
  r9--;
  r9 = (r9 & 7) <<13;
	
loc_220A64:
	r3 = ret3;
  r9 = r9 | r11;
	
	
	if(ret3 <= 0xF)
	  r3 = 0xF;
	
	
	r3 = (r3 & 0x7F) <<16;
	r3 = r9 | r3;
	
	//printf("r3: 0x%08X\n", r3);
	return (S32)r3;
}

/***********************************************************************
* 
***********************************************************************/
static void rsx_object_channel_220B00()
{
	S32 i, fc1_offset, fc2_offset, value, tmp, offset;
	S64 addr;
	rsx_core_device_t *core = NULL;
	rsx_core_memory_t *core_mem = NULL;
	rsx_device_graph_t *graph = NULL;
	
	
	// get RSX device core
	core = rsx_core_device_get_core_object_by_id(g_rsx_core_id);
  if(core == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
	
	// get core memory object
	core_mem = (void*)core->core_mem;
	
	// get channel fc1 and fc2 offset
	fc1_offset = rsx_core_memory_get_BAR2_offset_by_address((void*)core_mem, fc1_addr);
	fc2_offset = rsx_core_memory_get_BAR2_offset_by_address((void*)core_mem, fc2_addr);
	
	// init channel fc2 with 0, e.g. channel 0 (start: 0x28002030000 size: 0x1000(4 KB))
	for (i = 0; i < 512; i++)
	{
		DDR_write32(0, g_rsx_bar2_addr + fc2_offset + (i * 8));
		DDR_write32(0, g_rsx_bar2_addr + fc2_offset + (i * 8) + 4);
	}
	
	// init channel fc1 with 0, e.g. channel 0 (start: 0x28002020000 size: 0x80(128 byte))
	for (i = 0; i < 32; i++)
		DDR_write32(0, g_rsx_bar2_addr + fc1_offset + (i * 4));
	
	
	
	
	
	// TODO: nested loop...
	tmp = rsx_object_channel_2209B0((void*)ch_obj);
	
	
	
	
	
	addr = rsx_object_context_dma_object_get_BAR2_address((void*)ch_obj->dma_obj);
	//printf("addr: 0x%016llX\n", addr);
	
	offset = rsx_core_memory_get_BAR2_offset_by_address((void*)core_mem, addr);
	//printf("offset: 0x%08X\n", offset);
	
	// ? init channel fc1
	DDR_write32(tmp | 0x80000000, g_rsx_bar2_addr + fc1_offset + 0x18);
	
	value = DDR_read32(g_rsx_bar2_addr + fc1_offset + 0x3C);
	value &= 0xFFFE0000;
	value |= 0x0001FFFF;
	DDR_write32(value, g_rsx_bar2_addr + fc1_offset + 0x3C);
  
	value = DDR_read32(g_rsx_bar2_addr + fc1_offset + 0x2C);
	value &= 1;
	value |= 0x7FFFFFFF;
	DDR_write32(value, g_rsx_bar2_addr + fc1_offset + 0x3C);
	
	value = DDR_read32(g_rsx_bar2_addr + fc1_offset + 4);
	value &= 3;
	DDR_write32(value, g_rsx_bar2_addr + fc1_offset + 4);
	
	value = DDR_read32(g_rsx_bar2_addr + fc1_offset);
	value &= 3;
	DDR_write32(value, g_rsx_bar2_addr + fc1_offset);
	
	value = DDR_read32(g_rsx_bar2_addr + fc1_offset + 0x34);
	value &= 3;
	DDR_write32(value, g_rsx_bar2_addr + fc1_offset + 0x34);
	
	// ?
	tmp = rsx_core_memory_value_div_by_16((void*)core_mem, offset);
	//printf("addr: 0x%08X\n", rsx_core_memory_value_div_by_16((void*)core_mem, offset));
	
	value = DDR_read32(g_rsx_bar2_addr + fc1_offset + 0xC);
	value &= 0xFF000000;
	value |= tmp;
	DDR_write32(value, g_rsx_bar2_addr + fc1_offset + 0xC);
	
	
	
	// ?
	graph = (void*)core->dev_graph_obj;
	rsx_device_graph_21DA04((void*)graph, ch_obj->id);
	
	return;
}


/***********************************************************************
* 
***********************************************************************/
void rsx_object_channel_220D0C(S32 channel_id, rsx_object_context_dma_t *dma_obj)
{
	S32 offset;
	rsx_core_device_t *core = NULL;
	rsx_device_fifo_t *fifo = NULL;
	rsx_device_graph_t *graph = NULL;
	rsx_core_memory_t *core_mem = NULL;
	
	
	ch_obj->id = channel_id;               // set channel ID
	ch_obj->dma_obj = (void*)dma_obj;      // set cannel DMA object 
	
	// get RSX device core
	core = rsx_core_device_get_core_object_by_id(g_rsx_core_id);
  if(core == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
	
	// get device core FIFO object
	fifo = (void*)core->fifo;
	if(fifo == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
	
	// get and set channel FIFO cache addresses
	ch_obj->fc1_addr = rsx_device_fifo_get_fc1_channel_address_by_id(fifo, ch_obj->id);
	ch_obj->fc2_addr = rsx_device_fifo_get_fc2_channel_address_by_id(fifo, ch_obj->id);
	
	// get device core GRAPH object
	graph = (void*)core->dev_graph_obj;
	if(graph == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return;
  }
	
	// get and set channel GRAPH address
	ch_obj->graph_addr = rsx_device_graph_get_graph_channel_address_by_id(graph, channel_id);
	
	// ?
	rsx_object_channel_220B00(ch_obj);
	
	// ?
	core_mem = (void*)core->core_mem;
	offset = rsx_core_memory_get_BAR2_offset_by_address((void*)core_mem, ch_obj->graph_addr);
	//printf("ch_obj->graph_addr: 0x%016llX addr: 0x%08X\n", ch_obj->graph_addr, offset);
	
	rsx_device_fifo_21CCC0((void*)fifo, ch_obj->id, offset);
	
	// TODO: not finished, many unknow values...
	rsx_device_fifo_21C234((void*)fifo, ch_obj->id);
	
	return;
}


/***********************************************************************
* 
***********************************************************************/
rsx_object_channel_t *rsx_object_channel_create_object(rsx_object_context_dma_t *dma_obj)
{
	S32 ret = -1;
	S64 channel_id;
	rsx_core_device_t* core = NULL;
	rsx_utils_bitmap_t* bm_channels = NULL;
	 = NULL;
	
	
	// get RSX device core
	core = rsx_core_device_get_core_object_by_id(g_rsx_core_id);
  if(core == NULL)
  {
	  printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
    return NULL;
  }
	
	// get device core memory object channels bitmap
	bm_channels = (void*)core->bm_obj_channels;
	
	// allocate new channel object into bitmap
	ret = rsx_utils_bitmap_allocate((void*)bm_channels, 1, &channel_id);
	if(ret == 0)  // allocation fails
	  return NULL;
	
	// allocate new channel object
	ch_obj = lv1_kmalloc(sizeof(rsx_object_channel_t));
	if(ch_obj == NULL)
	{
		printf("rsx driver assert failed. [%s : %04d : %s()]\n", __FILE__, __LINE__, __func__);
		return NULL;
	}
	
	// init channel object
	// TODO: not finished
	rsx_object_channel_220D0C((void*)ch_obj, (S32)channel_id, (void*)dma_obj);
	
	
	
	return (void*)ch_obj;
}
