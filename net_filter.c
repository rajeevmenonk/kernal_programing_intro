#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>

unsigned int hook_func(const struct nf_hook_ops *ops,
                               struct sk_buff *skb,
                               const struct net_device *in,
                               const struct net_device *out,
                               int (*okfn)(struct sk_buff *))
{
    printk(KERN_INFO "INSIDE GET_PACKET_INFO %s \n", in->name);
    return 1;
}

int init_module (void)
{
    printk (KERN_INFO "Inside Init of Hello World \n");

    static struct nf_hook_ops nf_hook;
    nf_hook.hook = hook_func;
    nf_hook.pf = PF_INET;
    nf_hook.hooknum = 0; // NF_IP_PRE_ROUTING
    nf_hook.priority = INT_MIN; // NF_IP_PRI_FIRST
    nf_register_hook(&nf_hook);

    return 0;
}

void cleanup_module (void)
{
    printk(KERN_INFO "Inside Clean up of Hello World \n");
}

