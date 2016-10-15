#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/kthread.h>
#include <net/ip.h>
#include <net/arp.h>
#include <net/sock.h>

struct flowStruct 
{
    struct flowStruct *node;
    int value;
};
int init_module (void)
{
    struct flowStruct a,b;
    a.value = 10;
    b.value = 20;
    a.node = &b;

    printk (KERN_INFO "Inside Init of Hello World \n");
    return 0;
}

void cleanup_module (void)
{
    printk(KERN_INFO "Inside Clean up of Hello World \n");
}

