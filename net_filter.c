#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/ip.h>

unsigned int hook_func(const struct nf_hook_ops *ops,
                               struct sk_buff *skb,
                               const struct net_device *in,
                               const struct net_device *out,
                               int (*okfn)(struct sk_buff *))
{
    struct iphdr *iph = ip_hdr(skb);
    printk(KERN_INFO "INSIDE GET_PACKET_INFO %s %d.%d.%d.%d\n", in->name, iph->daddr & 0xFF,(iph->daddr >> 8) & 0xFF, (iph->daddr >> 16) & 0xFF, (iph->daddr >> 24) & 0xFF);
    return 1;
}

static struct nf_hook_ops nf_hook;

int init_module (void)
{
    printk (KERN_INFO "Inside Init of Hello World \n");

    nf_hook.hook = hook_func;
    nf_hook.pf = PF_INET;
    nf_hook.hooknum = 0; // NF_IP_PRE_ROUTING
    nf_hook.priority = INT_MIN; // NF_IP_PRI_FIRST
    nf_register_hook(&nf_hook);

    return 0;
}

void cleanup_module (void)
{
    nf_unregister_hook(&nf_hook);
    printk(KERN_INFO "Inside Clean up of Hello World \n");
}

