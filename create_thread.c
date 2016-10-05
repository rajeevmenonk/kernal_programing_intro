#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/kthread.h>
#include <net/ip.h>
#include <net/arp.h>
#include <net/sock.h>

#define OF_SOURCE_IP 3232236546
#define NEXT_HOP_IP_OF 3232236034

void send_the_packet_out (struct sk_buff *skb)
{
    printk (KERN_INFO "Inside Init of Thread test %d \n", skb->len);
}

int init_module (void)
{
    printk (KERN_INFO "Inside Init of Hello World \n");
    struct sk_buff *skb = kmalloc(sizeof(*skb), GFP_KERNEL);
    skb->len = 100;
    kthread_run(&send_the_packet_out, skb, "testThread");
    return 0;
}

void cleanup_module (void)
{
    printk(KERN_INFO "Inside Clean up of Hello World \n");
}

