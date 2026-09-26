// SPDX-License-Identifier: GPL-2.0
/*
 * Luckfox Pico hello kernel module
 *
 * 功能验证用最小内核模块:
 *   insmod hello.ko            -> dmesg 打印加载信息
 *   insmod hello.ko who=xxx    -> 自定义问候对象
 *   rmmod hello                -> dmesg 打印卸载信息
 *
 * 验证步骤(板子上):
 *   insmod /oem/usr/ko/hello.ko && dmesg | tail -2
 *   rmmod hello && dmesg | tail -1
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#define HELLO_VERSION "1.0.0"

static char *who = "luckfox";
module_param(who, charp, 0644);
MODULE_PARM_DESC(who, "greeting target name (default: luckfox)");

static int __init hello_init(void)
{
	pr_info("hello: module loaded (version %s)\n", HELLO_VERSION);
	pr_info("hello: nice to meet you, %s!\n", who);
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("hello: module unloaded, goodbye %s\n", who);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("luckfox");
MODULE_DESCRIPTION("Luckfox Pico hello module for functional verification");
MODULE_VERSION(HELLO_VERSION);
