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
     //ip_output(skb);
    struct sock *sk = skb->sk;
    struct net *net = sock_net(sk);
    struct net_device *dev = __dev_get_by_name(net, "eth2");
    struct neighbour *neigh;
    
    rcu_read_lock_bh();
    u32 nexthop = NEXT_HOP_IP_OF;
    neigh = __ipv4_neigh_lookup_noref(dev, nexthop);
    if (unlikely(!neigh))
            neigh = __neigh_create(&arp_tbl, &nexthop, dev, false);
    if (!IS_ERR(neigh)) {
            dst_neigh_output(skb_dst(skb), neigh, skb);
            rcu_read_unlock_bh();
    }
    rcu_read_unlock_bh();
    dev_queue_xmit(skb);
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
    // TODO - KILL THE THREAD THAT WAS CREATED
    nf_unregister_hook(&nf_hook_open_flow);
    printk(KERN_INFO "Inside Clean up of Hello World \n");
}

