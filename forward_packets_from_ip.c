#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/kthread.h>

#define OF_SOURCE_IP 100

void send_the_packet_out (struct sk_buff *skb)
{
}

unsigned int hook_func(const struct nf_hook_ops *ops,
                               struct sk_buff *skb,
                               const struct net_device *in,
                               const struct net_device *out,
                               int (*okfn)(struct sk_buff *))
{
    struct iphdr *iph = ip_hdr(skb);
    printk(KERN_INFO "INSIDE GET_PACKET_INFO %s %d.%d.%d.%d\n", in->name, iph->daddr & 0xFF,(iph->daddr >> 8) & 0xFF, (iph->daddr >> 16) & 0xFF, (iph->daddr >> 24) & 0xFF);

    if (iph->daddr != OF_SOURCE_IP)
        return 1; // NF_ACCEPT

    // Call the thread here.
    kthread_create(&send_the_packet_out, skb, "testThread");
    return 2; // NF_STOLEN
}

static struct nf_hook_ops nf_hook_open_flow;

int init_module (void)
{
    printk (KERN_INFO "Inside Init of Hello World \n");

    nf_hook_open_flow.hook = hook_func;
    nf_hook_open_flow.pf = PF_INET;
    nf_hook_open_flow.hooknum = 2; // NF_IP_FORWARD
    nf_hook_open_flow.priority = INT_MIN; // NF_IP_PRI_FIRST
    nf_register_hook(&nf_hook_open_flow);

    return 0;
}

void cleanup_module (void)
{
    nf_unregister_hook(&nf_hook_open_flow);
    printk(KERN_INFO "Inside Clean up of Hello World \n");
}

