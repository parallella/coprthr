/* coprthr_device.h 
 *
 * Copyright (c) 2009-2013 Brown Deer Technology, LLC.  All Rights Reserved.
 *
 * This software was developed by Brown Deer Technology, LLC.
 * For more information contact info@browndeertechnology.com
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3 (LGPLv3)
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* DAR */

#ifndef _coprthr_device_h
#define _coprthr_device_h

#include "imp_structs.h"

/* XXX temporarily put this here */

/*
struct coprthr_command_queue {
   pthread_t td;
   pthread_mutex_t mtx;
   pthread_cond_t sig;
   unsigned int qstat;
   struct _cl_event* cmd_submitted;
   struct _cl_event* cmd_running;
   TAILQ_HEAD(tailhead_cmds_queued,_cl_event) cmds_queued;
   TAILQ_HEAD(tailhead_cmds_complete,_cl_event) cmds_complete;
};
*/

struct coprthr_device_info {

	cl_device_type devtype;
	cl_uint vendorid;
	cl_uint max_compute_units;
	cl_uint max_wi_dim;
	size_t max_wi_sz[4];
	size_t max_wg_sz;
	cl_uint pref_charn;
	cl_uint pref_shortn;
	cl_uint pref_intn;
	cl_uint pref_longn;
	cl_uint pref_floatn;
	cl_uint pref_doublen;
	cl_uint max_freq;
	cl_uint addr_bits;
	cl_ulong max_mem_alloc_sz;
	cl_bool supp_img;
	cl_uint img_max_narg_r;
	cl_uint img_max_narg_w;
	size_t img2d_max_width;
	size_t img2d_max_height;
	size_t img3d_max_width;
	size_t img3d_max_height;
	size_t img3d_max_depth;
	cl_uint max_samplers;
	size_t max_param_sz;
	cl_uint mem_align_bits;
	cl_uint datatype_align_sz;
	cl_device_fp_config single_fp_config;
	cl_device_mem_cache_type global_mem_cache_type;
	cl_uint global_mem_cacheline_sz;
	cl_ulong global_mem_cache_sz;
	cl_ulong global_mem_sz;
	cl_ulong max_const_buffer_sz;
	cl_uint max_const_narg;
	cl_device_local_mem_type local_mem_type;
	cl_ulong local_mem_sz;
	cl_bool supp_ec;
	size_t prof_timer_res;
	cl_bool endian_little;
	cl_device_exec_capabilities supp_exec_cap;
	cl_command_queue_properties cmdq_prop;
	cl_platform_id platformid;
	char* name;
	char* vendor;
	char* drv_version;
	char* profile;
	char* version;
	char* extensions;

	char* dstrtab;
	size_t dstrtab_sz;

};

struct coprthr_command_queue;
struct coprthr_device_state {
	cpu_set_t cpumask;
	cl_bool avail;
	cl_bool compiler_avail;
	union {
		struct {
			unsigned int veid_base;
			unsigned int nve;
		} cpu;
	};
	struct coprthr_command_queue* cmdq;
};

struct coprthr_device_operations {
	cmdcall_t* v_cmdcall;
};

struct coprthr_device_compiler {
	void* (*comp)(void*);
	void* (*ilcomp)(void*);
};

struct _coprthr_ksyms_struct;
struct coprthr_device_linker {
	void* (*link)(void*);
	int (*bind_ksyms)(struct _coprthr_ksyms_struct*,void*,char*);
};

struct coprthr_device {
	struct coprthr_device_info* devinfo;
	struct coprthr_device_state* devstate;
	struct coprthr_device_operations* devops;
	struct coprthr_device_compiler* devcomp;
	struct coprthr_device_linker* devlink;
};

#define __resolve_devid_devinfo(d,m) ((d)->codev->devinfo->m)
#define __resolve_devid_devstate(d,m) ((d)->codev->devstate->m)
#define __resolve_devid_devops(d,m) ((d)->codev->devops->m)
#define __resolve_devid_devcomp(d,m) ((d)->codev->devcomp->m)
#define __resolve_devid_devlink(d,m) ((d)->codev->devlink->m)

/*
#define __imp_init_device(imp) do { \
	imp = malloc(sizeof(struct _imp_device)); \
	bzero(imp,sizeof(struct _imp_device)); \
	} while(0)

#define __imp_free_device(imp) do { if (imp) free(imp) } while(0)

#define __resolve_devid(d,m) ((d)->imp->m)
*/

/*
void __do_discover_devices( unsigned int* ndevices, 
	struct _cl_device_id**, struct _strtab_entry* );

void __do_release_devices(struct _cl_device_id*, struct _strtab_entry*);

void __do_get_ndevices(cl_platform_id, cl_device_type, cl_uint*);

void __do_get_devices(cl_platform_id, cl_device_type, cl_uint, cl_device_id*);
*/

#endif
