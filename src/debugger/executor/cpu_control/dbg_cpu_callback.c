#include "cpu.h"
#include "bus.h"
#include "cpu_control/dbg_cpu_callback.h"
#include "cpu_control/dbg_cpu_thread_control.h"
#include "cpu_control/dbg_cpu_control.h"
#include "cpuemu_ops.h"
#include "cui/cui_ops.h"
#include "symbol_ops.h"
#include "file_address_mapping.h"

void dbg_notify_cpu_clock_supply_start(const TargetCoreType *core)
{
	CoreIdType core_id;
	bool need_stop = FALSE;
	uint32 pc = cpu_get_pc(core);
	bool is_debug_mode;


	is_debug_mode = cpuctrl_is_debug_mode();

	core_id = cpu_get_core_id(core);
	if ((cpuctrl_is_force_debug_mode() == FALSE) && (dbg_cpu_debug_mode_get(core_id) == FALSE)) {
		return;
	}
	/*
	 * cont timeout check
	 * break point check
	 * debug mode check
	 */
	if (cpuctrl_is_timeout_cont_clocks(core_id) == TRUE) {
		need_stop = TRUE;
		printf("\nCONT TIMEOUT\n");
		//printf("[DBG>");
	}
	else if ((cpuctrl_is_break_point(pc) == TRUE)) {
		 uint32 funcaddr;
		 int funcid;
		 need_stop = TRUE;
		 funcid = symbol_pc2funcid(pc, &funcaddr);
		 if (funcid >= 0) {
			 printf("\nHIT break:0x%x %s(+0x%x)\n", pc, symbol_funcid2funcname(funcid), pc - funcaddr);
		 }
		 else {
			 printf("\nHIT break:0x%x\n", pc);
		 }

	}
	else if (is_debug_mode == TRUE) {
		need_stop = TRUE;
	}

	if (need_stop == TRUE) {
		ValueFileType value;
		Std_ReturnType err = file_address_mapping_get(pc, &value);
		dbg_cpu_control_print_source(pc);
		if (err == STD_E_OK) {
			CUI_PRINTF((CPU_PRINT_BUF(), CPU_PRINT_BUF_LEN(), "%s %u\n", value.file, value.line));
		}
		else {
			CUI_PRINTF((CPU_PRINT_BUF(), CPU_PRINT_BUF_LEN(), "OK\n"));
		}
		//fflush(stdout);
		//CUI_PRINTF((CPU_PRINT_BUF(), CPU_PRINT_BUF_LEN(), "core[%u].pc = 0x%x\n", cpu_get_core_id(core), pc));
		cpuctrl_set_current_debugged_core(cpu_get_core_id(core));
		cpuctrl_set_debug_mode(TRUE);
		dbg_log_sync();
		/*
		 * return コマンド実行時の一時的なブレークポイントを削除する．
		 */
		cpuctrl_del_all_break(BREAK_POINT_TYPE_ONLY_ONCE);
		cputhr_control_cpu_wait();
	}
	return;
}

void dbg_notify_cpu_clock_supply_end(const TargetCoreType *core, const DbgCpuCallbackFuncEnableType *enable_dbg)
{
	uint32 pc = cpu_get_pc(core);
	uint32 sp = cpu_get_sp(core);
	BusAccessType type;
	uint32 size;
	uint32 access_addr;
	bool need_stop = FALSE;

	/*
	 * call callback
	 */
	if (enable_dbg->enable_ft == TRUE) {
		cpuctrl_set_func_log_trace(core->core_id, pc, sp);
	}
	if (enable_dbg->enable_prof == TRUE) {
		cpuctrl_profile_collect(core->core_id, pc);
	}
	if (enable_dbg->enable_bt == TRUE) {
		cpuctrl_set_stack_pointer(sp);
	}
	if (enable_dbg->enable_watch == TRUE) {
		/*
		 * data watch check
		 */
		while (TRUE) {
			int inx;
			Std_ReturnType err;
			uint32 last_data;

			err = bus_access_get_log(&type, &size, &access_addr, &last_data);
			if (err != STD_E_OK) {
				break;
			}
			if (type == BUS_ACCESS_TYPE_READ) {
				inx = cpuctrl_is_break_read_access(access_addr, size);
				if (inx >= 0) {
					need_stop = TRUE;
					printf("\nore%d HIT watch data : read access : [%u] 0x%x 0x%x %u\n", core->core_id, inx, access_addr, last_data, size);
				}
			}
			else if (type == BUS_ACCESS_TYPE_WRITE) {
				inx = cpuctrl_is_break_write_access(access_addr, size);
				if (inx >= 0) {
					need_stop = TRUE;
					printf("\ncore%d HIT watch data : write access : [%u] 0x%x 0x%x %u\n", core->core_id, inx, access_addr, last_data, size);
				}
			}
		}

		if (need_stop == TRUE) {
			cpuctrl_set_debug_mode(TRUE);
		}
	}

	return;
}
