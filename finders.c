/*
 * Copyright 2013-2016, iH8sn0w. <iH8sn0w@iH8sn0w.com>
 *
 * This file is part of iBoot32Patcher.
 *
 * iBoot32Patcher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * iBoot32Patcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with iBoot32Patcher.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <include/finders.h>
#include <include/functions.h>
#include <include/iBoot32Patcher.h>

void* find_bl_verify_shsh(struct iboot_img* iboot_in) {
    int os_vers = get_os_version(iboot_in);
    
    /* Use the os-specific method for finding BL verify_shsh... */
    if(os_vers >= 5 && os_vers <= 7) {
        return find_bl_verify_shsh_5_6_7(iboot_in);
    }
    
    return find_bl_verify_shsh_generic(iboot_in);
}


void* find_ldr_ecid(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the LDR Rx, ='ECID' instruction... */
    void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'ECID');
    if(!ldr_insn) {
        printf("%s: Unable to find LDR ECID!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found LDR instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    char *ldr_ecid = bl_search_down(ldr_insn,0x100);
    if(!ldr_ecid) {
        printf("%s: Unable to find a BL ECID! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL ECID at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_ecid));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return ldr_ecid;
}

void* find_ldr_bord(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the LDR Rx, ='BORD' instruction... */
    void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'BORD');
    if(!ldr_insn) {
        printf("%s: Unable to find LDR insn!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found LDR BORD instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    char *ldr_bord = bl_search_down(ldr_insn,0x100);
    if(!ldr_bord) {
        printf("%s: Unable to find a BL BORD! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL BORD at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_bord));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return ldr_bord;
}

void* find_ldr_prod(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the LDR Rx, ='PROD' instruction... */
    void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'PROD');
    if(!ldr_insn) {
        printf("%s: Unable to find LDR insn!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found LDR PROD instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    char *ldr_prod = bl_search_down(ldr_insn,0x100);
    if(!ldr_prod) {
        printf("%s: Unable to find a BL PROD! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL PROD at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_prod));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return ldr_prod;
}

void* find_ldr_sepo(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the LDR Rx, ='SEPO' instruction... */
    void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'SEPO');
    if(!ldr_insn) {
        printf("%s: Unable to find LDR insn!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found LDR SEPO instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    char *ldr_sepo = bl_search_down(ldr_insn,0x100);
    if(!ldr_sepo) {
        printf("%s: Unable to find a BL SEPO! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL SEPO at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_sepo));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return ldr_sepo;
}

void* find_rsa_check_4(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the RSA check */
    void* rsa_check_4 = memstr(iboot_in->buf, iboot_in->len, RSA_PATCH_IOS_4);
    if(!rsa_check_4) {
        printf("%s: Unable to find RSA check!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found RSA check at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, rsa_check_4));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return rsa_check_4;
}

void* find_bl_verify_shsh_5_6_7(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the MOVW Rx, #'RT' instruction... */
    void* movw = find_next_MOVW_insn_with_value(iboot_in->buf, iboot_in->len, 'RT');
    if(!movw) {
        printf("%s: Unable to find MOVW instruction!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found MOVW instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, movw));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    void* bl_verify_shsh = find_bl_verify_shsh_insn(iboot_in, movw);
    if(!bl_verify_shsh) {
        printf("%s: Unable to find a BL verify_shsh! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL verify_shsh at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, bl_verify_shsh));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return bl_verify_shsh;
}

void* find_bl_verify_shsh_generic(struct iboot_img* iboot_in) {
	printf("%s: Entering...\n", __FUNCTION__);

	/* Find the LDR Rx, ='CERT' instruction... */
	void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'CERT');
	if(!ldr_insn) {
		printf("%s: Unable to find LDR insn!\n", __FUNCTION__);
		return 0;
	}

	printf("%s: Found LDR instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));

	/* Resolve the BL verify_shsh routine from found instruction... */
	void* bl_verify_shsh = find_bl_verify_shsh_insn(iboot_in, ldr_insn);
	if(!bl_verify_shsh) {
		printf("%s: Unable to find a BL verify_shsh! (Image may already be patched?)\n", __FUNCTION__);
		return 0;
	}

	printf("%s: Found BL verify_shsh at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, bl_verify_shsh));

	printf("%s: Leaving...\n", __FUNCTION__);

	return bl_verify_shsh;
}

void* find_bl_verify_shsh_insn(struct iboot_img* iboot_in, void* pc) {
	/* Find the top of the function... */
	void* function_top = find_verify_shsh_top(pc);
	if(!function_top) {
		printf("%s: Unable to find top of verify_shsh!\n", __FUNCTION__);
		return 0;
	}

	/* Find the BL insn resolving to this function... (BL verify_shsh seems to only happen once) */
	void* bl_verify_shsh = find_next_bl_insn_to(iboot_in, (uint32_t) ((uintptr_t)GET_IBOOT_FILE_OFFSET(iboot_in, function_top)));
	if(!bl_verify_shsh) {
		return 0;
	}

	return bl_verify_shsh;
}

void* find_dtre_get_value_bl_insn(struct iboot_img* iboot_in, const char* var) {
	printf("%s: Entering...\n", __FUNCTION__);

	/* Find the variable string... */
	void* var_str_loc = memstr(iboot_in->buf, iboot_in->len, var);
	if(!var_str_loc) {
		printf("%s: Unable to find %s string!\n", __FUNCTION__, var);
		return 0;
	}
	printf("%s: %s string is at %p\n", __FUNCTION__, var, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, var_str_loc));

	/* Find the variable string xref... */
	void* var_xref = iboot_memmem(iboot_in, var_str_loc);
	if(!var_xref) {
		printf("%s: Unable to find %s string xref!\n", __FUNCTION__, var);
		return 0;
	}
	printf("%s: \"%s\" xref is at %p\n", __FUNCTION__, var, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, var_xref));

	/* Locate corresponding LDR insn for xref... */
	void* var_ldr = ldr_to(var_xref);
	if(!var_ldr) {
		printf("%s: Unable to find %s string LDR from xref!\n", __FUNCTION__, var);
		return 0;
	}

	struct arm32_thumb_LDR* ldr_rd_debug_enabled = (struct arm32_thumb_LDR*) var_ldr;
	printf("%s: Found LDR R%d, =\"%s\" at %p\n", __FUNCTION__, ldr_rd_debug_enabled->rd, var, GET_IBOOT_FILE_OFFSET(iboot_in, var_ldr));

	/* Find the BL insn that follows the LDR insn... (Usually BL does_dtre_have_var) */
	void* is_in_dtre_bl = bl_search_down(var_ldr, 0x100);
	if(!is_in_dtre_bl) {
		printf("%s: Unable to find a BL following LDR insn.\n", __FUNCTION__);
		return 0;
	}
	is_in_dtre_bl++;

	/* Find the next BL insn after the previous BL insn... (Usually BL get_value_for_dtre_var) */
	void* get_value_for_dtre_bl = bl_search_down(is_in_dtre_bl, 0x100);
	if(!get_value_for_dtre_bl) {
		printf("%s: Unable to find a BL following the previous BL.\n", __FUNCTION__);
		return 0;
	}

	printf("%s: Found BL instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, get_value_for_dtre_bl));

	printf("%s: Leaving...\n", __FUNCTION__);

	return get_value_for_dtre_bl;
}

void* find_verify_shsh_top(void* ptr) {
	void* top = push_r4_r7_lr_search_up(ptr, 0x500);
	if(!top) {
		return 0;
	}
	top++; // Thumb
	return top;
}

void* find_boot_partition_ldr(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    uint32_t boot_partition_loc = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "boot-partition", strlen("boot-partition")));
    if (!boot_partition_loc) {
        printf("%s: Failed to find boot-partition string\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found boot-partition string: %p\n", __FUNCTION__, boot_partition_loc);
    void * boot_partition_ldr = find_next_LDR_insn_with_value(iboot_in, boot_partition_loc);
    if (!boot_partition_ldr) {
        printf("%s: Failed to find boot-partition LDR\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found boot-partition LDR: %p\n", __FUNCTION__, GET_IBOOT_ADDR(iboot_in, boot_partition_ldr));
    return boot_partition_ldr;
}

void* find_boot_ramdisk_ldr(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    uint32_t boot_ramdisk_loc = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "boot-ramdisk", strlen("boot-ramdisk")));
    if (!boot_ramdisk_loc) {
        printf("%s: Failed to find boot-ramdisk string\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found boot-ramdisk string: %p\n", __FUNCTION__, boot_ramdisk_loc);
    void * boot_ramdisk_ldr = find_next_LDR_insn_with_value(iboot_in, boot_ramdisk_loc);
    if (!boot_ramdisk_ldr) {
        printf("%s: Failed to find boot-ramdisk LDR\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found boot-ramdisk LDR: %p\n", __FUNCTION__, GET_IBOOT_ADDR(iboot_in, boot_ramdisk_ldr));
    return boot_ramdisk_ldr;
}

