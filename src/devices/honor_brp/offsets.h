/* HONOR Magic 7 Lite / X9C 5G (BRP-NX1) — SM6450 / Snapdragon 6 Gen 1, kernel 5.10.252
 * Compact waiter (10 words), waiter_word=0 (expected), PSELECT_SHIFT=0
 * C ashmem (ashmem_misc), no copy_splice_read (5.10)
 *
 * kimage_text_base=0xffffffc008000000 (VA_BITS=39, standard 5.10).
 * GKI certified build ab15212796.
 *
 * 5.10 CFI: function pointers in fops use .cfi_jt addresses.
 * fops struct layout: ioctl=0x50, compat_ioctl=0x58, mmap=0x60 (5.10 has iterate+iterate_shared)
 */

OFFSETS_ENTRY("5.10.252-android12-9-00009-gf960ed27302b-ab15212796",
  .kernel_phys_load=0, STRUCT_OFFSETS_5_10,
  .kimage_text_base=0xffffffc008000000ULL,
  /* fops struct field offsets for 5.10 (has iterate+iterate_shared before poll) */
  .fops_ioctl=0x50, .fops_compat_ioctl=0x58, .fops_mmap=0x60,
  .off_init_task=0x027ABC80, .off_init_cred=0x027C0860, .off_init_uts_ns=0x027ABA28,
  .off_empty_zero_page=0x0299F000, .off_root_task_group=0x029A4040,
  .off_selinux_enforcing=0x02A53B98, .off_kptr_restrict=0x0279CBE8,
  .off_selinux_blob_sizes=0x022FBA80, .off_security_hook_heads=0x022FB3E8,
  .off_kmalloc_caches=0x022FAF20, .off_anon_pipe_buf_ops=0x02162DA8,
  .off_ashmem_misc_fops=0, .off_ashmem_fops=0x022B8798,
  /* CFI JT addresses for function pointers */
  .off_ashmem_ioctl=0x01837978, .off_ashmem_compat_ioctl=0x01837980,
  .off_ashmem_mmap=0x01822940, .off_ashmem_open=0x01831468,
  .off_ashmem_release=0x01831470, .off_ashmem_show_fdinfo=0x01822AC0,
  .off_configfs_read_iter=0x0182FD20, .off_configfs_bin_write_iter=0x01830240,
  .off_copy_splice_read=0, .off_noop_llseek=0x0181FC90,
  .off_cap_capable_active=0,
  .off_slide_nfulnl_logger=0x027A1140, .off_slide_loggers_0_1=0x027A1070,
  .off_slide_boot_id=0x02A72BD5,
  .off_system_unbound_wq=0x02799C08, .off_call_usermodehelper_exec_work=0x00166B9C,
),
