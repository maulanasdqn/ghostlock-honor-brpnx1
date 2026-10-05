# GhostLock — HONOR Magic 7 Lite / X9C 5G (BRP-NX1) Port

Port of [GhostLock (CVE-2026-43499)](https://github.com/JoinChang/ghostlock-oneplus) for the HONOR Magic 7 Lite / X9C 5G with kernel 5.10.252 and locked bootloader.

## Device Info

| Detail | Value |
|---|---|
| Model | HONOR BRP-NX1 (Magic 7 Lite / X9C 5G) |
| SoC | Qualcomm SM6450 (Snapdragon 6 Gen 1) |
| Kernel | 5.10.252-android12-9-00009-gf960ed27302b-ab15212796 |
| Android | 16 |
| Security Patch | 2026-09-01 |
| GKI Build | ab15212796 |

## Patches Applied (7 fixes for 5.10 compact waiter)

1. **Runtime symbol offset resolution** — All symbol addresses (`SELINUX_ENFORCING_OFF`, `ASHMEM_IOCTL_OFF`, etc.) were hardcoded for OnePlus Ace 6T (6.12). Patched `runtime_struct_offsets.h` to resolve from device entry at runtime.

2. **Pipe blocking for select()** — Replaced timerfd with pipe read-end for the pselect blocking FD. Timerfd caused select() to return immediately (ret=4) on HONOR 5.10. Pipe write-end moved to high FD to prevent clobbering by open_selected_fds.

3. **child_node=1 for W1** — W1 SELinux write used all-zeros (child_node=0) which corrupted `selinux_state.initialized` → kernel crash. Set child_node=1 to write `page+0x100` (low byte 0x00 = enforcing off, preserves initialized).

4. **pi_waiters → W0 for all custom write modes** — Mode 1/2/3 had `fake_task->pi_waiters = NULL`, so the PI chain walk found an empty waiters list and performed NO write. Fixed to point pi_waiters to W0's PI tree entry (same as mode 4).

5. **W0 PI tree offset for compact waiter** — `FAKE_WAITER_PI_TREE_ENTRY_OFF = 0x28` is for 6.12 nested waiter. On 5.10 compact waiter, PI tree is at offset `0x18`. All W0 PI tree fields were shifted by 16 bytes, clobbering task/lock fields.

6. **Leaf node at fake_right** — `fake_right = base+0x100 = FOPS_TABLE_OFF` overlaps with the fake fops table. rb_erase followed fake_right as a child node into fops function pointers → crash. Overwrote first 24 bytes at FOPS_TABLE_OFF with clean leaf node data for mode=1.

7. **Auto-restart between W1 and W2** — W1's pselect route corrupts the FD table (hundreds of dup2'd pipe FDs). W2's select() returns immediately because of leftover FDs. After W1 succeeds (SELinux DISABLED), the binary exec's itself for a clean W2 run.

## Status

- ✅ CVE-2026-43499 confirmed present (remove_waiter still uses `current`)
- ✅ W1 SELinux write: **WORKING** (SELinux DISABLED achieved multiple times)
- 🔄 W2 cred write: in progress (select timing issue for W2's heap spray pages)
- ✅ 143,316 kernel symbols extracted from GKI boot.img
- ✅ All device offsets verified against kernel binary

## Build

```bash
NDK=/path/to/android-ndk
CC="$NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android35-clang"
$CC -O2 -Wall -Isrc/core -Isrc/devices -DTARGET_CONFIG_H=\"target.h\" \
  src/core/main.c src/core/util.c src/core/slide.c \
  src/core/fops.c src/core/pipe_physrw.c src/core/root.c \
  src/core/miniadb.c src/core/umh_root.c \
  -o ghostlock -fPIE -pie -pthread
```

## Run

```bash
adb push ghostlock /data/local/tmp/a/e
adb shell chmod 755 /data/local/tmp/a/e
adb shell /data/local/tmp/a/e
```

## Credits

- [JoinChang/ghostlock-oneplus](https://github.com/JoinChang/ghostlock-oneplus) — original GhostLock exploit
- [YuKongA/ghostlock-app](https://github.com/YuKongA/ghostlock-app) — GhostLock app (compact waiter layout reference)
- CVE-2026-43499 — Futex PI Use-After-Free
