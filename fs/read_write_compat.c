// SPDX-License-Identifier: GPL-2.0
#include <linux/compat.h>
#include <linux/syscalls.h>
#include <linux/uio.h>
#include <linux/fs.h>

asmlinkage ssize_t compat_sys_writev(compat_ulong_t fd,
                                     const struct compat_iovec __user *vec, compat_ulong_t vlen)
{
    return sys_writev(fd, (const struct iovec __user *)vec, vlen);
}

asmlinkage ssize_t compat_sys_preadv(compat_ulong_t fd,
                                     const struct compat_iovec __user *vec,
                                     compat_ulong_t vlen, u32 pos_low, u32 pos_high)
{
    loff_t pos = ((loff_t)pos_high << 32) | pos_low;
    return sys_preadv(fd, (const struct iovec __user *)vec, vlen, pos);
}

asmlinkage ssize_t compat_sys_pwritev(compat_ulong_t fd,
                                      const struct compat_iovec __user *vec,
                                      compat_ulong_t vlen, u32 pos_low, u32 pos_high)
{
    loff_t pos = ((loff_t)pos_high << 32) | pos_low;
    return sys_pwritev(fd, (const struct iovec __user *)vec, vlen, pos);
}

#ifdef CONFIG_PREADV2
asmlinkage ssize_t compat_sys_preadv2(compat_ulong_t fd,
                                      const struct compat_iovec __user *vec,
                                      compat_ulong_t vlen, u32 pos_low, u32 pos_high, rwf_t flags)
{
    loff_t pos = ((loff_t)pos_high << 32) | pos_low;
    return sys_preadv2(fd, (const struct iovec __user *)vec, vlen, pos, flags);
}

asmlinkage ssize_t compat_sys_pwritev2(compat_ulong_t fd,
                                       const struct compat_iovec __user *vec,
                                       compat_ulong_t vlen, u32 pos_low, u32 pos_high, rwf_t flags)
{
    loff_t pos = ((loff_t)pos_high << 32) | pos_low;
    return sys_pwritev2(fd, (const struct iovec __user *)vec, vlen, pos, flags);
}
#endif
