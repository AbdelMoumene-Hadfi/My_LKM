#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/paravirt.h>
#include <linux/kallsyms.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abdo Hadfi <abdelmouminhadfi15@gmail.com>");
MODULE_DESCRIPTION("Chnage WP bit value in cr0");

unsigned long **syscall_table ;
unsigned long cr0;
extern unsigned long __force_order;

static inline  void write_forced_cr0(unsigned long val) {
	asm volatile("mov %0,%%cr0":"+r" (val),"+m"(__force_order));
}
static inline void zero_wp(void) {
  	  write_forced_cr0(read_cr0() & ~0x10000);
}
static inline void one_wp(void) {
      write_forced_cr0(read_cr0() | 0x10000);
}
static int __init init_mod(void) {
  printk(KERN_EMERG "insmod change_wp");
  cr0=read_cr0();
  printk(KERN_EMERG "The value of cr0 before change :%lx\n",cr0);
  zero_wp();
  cr0=read_cr0();
  printk(KERN_EMERG "The value of cr0 after change :%lx\n",cr0);
  one_wp();
  return 0;
}
static void __exit exit_mod(void) {
  printk(KERN_EMERG "rmmod change_wp");
}
module_init(init_mod);
module_exit(exit_mod);
