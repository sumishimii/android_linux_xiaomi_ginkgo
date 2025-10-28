// SPDX-License-Identifier: GPL-2.0
/*
 * 32-bit compat syscall wrappers for vector read/write operations
 * Works with or without CONFIG_PREADV2
 */

#include <linux/compat.h>
#include <linux/syscalls.h>
#include <linux/uio.h>
#include <linux/fs.h>
#include <linux/errno.h>

asmlinkage ssize_t compat_sys_writev(compat_ulong_t fd,
                                     const struct compat_iovec __user *vec,
                                     compat_ulong_t vlen)
{
    return sys_writev(fd, (const struct iovec __user *)vec, vlen);
}

asmlinkage ssize_t compat_sys_preadv(compat_ulong_t fd,
                                     const struct compat_iovec __user *vec,
                                     compat_ulong_t vlen,
                                     u32 pos_low, u32 pos_high)
{
    return sys_preadv(fd, (const struct iovec __user *)vec, vlen,
                      pos_low, pos_high);
}

asmlinkage ssize_t compat_sys_pwritev(compat_ulong_t fd,
                                      const struct compat_iovec __user *vec,
                                      compat_ulong_t vlen,
                                      u32 pos_low, u32 pos_high)
{
    return sys_pwritev(fd, (const struct iovec __user *)vec, vlen,
                       pos_low, pos_high);
}

/*
 * preadv2/pwritev2 — added in Linux 4.6
 * Some kernels may have CONFIG_PREADV2 disabled, so we provide fallbacks.
 */
#if defined(CONFIG_PREADV2)
asmlinkage ssize_t compat_sys_preadv2(compat_ulong_t fd,
                                      const struct compat_iovec __user *vec,
                                      compat_ulong_t vlen,
                                      u32 pos_low, u32 pos_high,
                                      rwf_t flags)
{
    return sys_preadv2(fd, (const struct iovec __user *)vec, vlen,
                       pos_low, pos_high, flags);
}

asmlinkage ssize_t compat_sys_pwritev2(compat_ulong_t fd,
                                       const struct compat_iovec __user *vec,
                                       compat_ulong_t vlen,
                                       u32 pos_low, u32 pos_high,
                                       rwf_t flags)
{
    return sys_pwritev2(fd, (const struct iovec __user *)vec, vlen,
                        pos_low, pos_high, flags);
}
#else /* CONFIG_PREADV2 not defined */
asmlinkage ssize_t compat_sys_preadv2(compat_ulong_t fd,
                                      const struct compat_iovec __user *vec,
                                      compat_ulong_t vlen,
                                      u32 pos_low, u32 pos_high,
                                      rwf_t flags)
{
    return -ENOSYS;
}

asmlinkage ssize_t compat_sys_pwritev2(compat_ulong_t fd,
                                       const struct compat_iovec __user *vec,
                                       compat_ulong_t vlen,
                                       u32 pos_low, u32 pos_high,
                                       rwf_t flags)
{
    return -ENOSYS;
}
#endif /* CONFIG_PREADV2 */
