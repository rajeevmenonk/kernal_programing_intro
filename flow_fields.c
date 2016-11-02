#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/sctp.h>
#include <linux/icmp.h>
#include "enums_local.h"
#include "structs_local.h"
#include "setup_local.h"

struct transportHeader {
    __be16 source;
    __be16 dest;
};

struct transportHeader* trans_hdr(const struct sk_buff *skb)
{
    return (struct transportHeader *)skb_transport_header(skb);
}

int checkIfFlowEntriesMatch(struct ofp_match* first,
                             struct ofp_match* second)
{
    while(first && second)
    {
        if (! ((sizeof(*first) == sizeof(*second)) && 
               (memcmp(first+sizeof(struct list_head *),
                       second+sizeof(struct list_head *),
                       sizeof(*first) - sizeof(struct list_head  *)) == 0)))
            return 0;

        first  = (struct ofp_match *)first->next;
        second = (struct ofp_match *)second->next;
    }
    return 1;
}

// The flow entries are sorted based in the priority. The values
// with the higher priority comes first in the list.
enum ofp_error_type addFlowEntry (struct list_head *head,
                                  struct ofp_flow_table *new,
                                  __u8 checkForOverlap)
{
    struct ofp_flow_table *entry;
    struct list_head *prev;

    // Adding first flow entry;
    if (!head->next)
    {
        head->next = (struct list_head *)new;
        return OFPET_SUCCESS;
    }

    entry = (struct ofp_flow_table *)head->next;
    prev = head;

    while(entry)
    {
        if (entry->priority < new->priority)
            break;
        else if (checkForOverlap && 
                 entry->priority == new->priority &&
                 checkIfFlowEntriesMatch ((struct ofp_match *)entry->match->next,
                                          (struct ofp_match *)new->match->next))
        {
            return 0;
        }
        
        prev = (struct list_head *)entry;
        entry = (struct ofp_flow_table *)entry->next;
    }

    new->next = (struct list_head *)entry;
    prev->next = (struct list_head *)new;
    return OFPET_SUCCESS;
}

void deleteFlowEntry (struct list_head *head,
                      struct list_head *entry)
{
     struct list_head *prev = NULL;
     while (head != entry)
     {
         prev = head;
         head = head->next;
     }

     if (prev)
         prev->next = head->next;
}

//struct list_head* getNextEntry (struct list_head *head)
//{
//    
//}

// Verify if flow matches with the entries in the queue.
int match_values (struct ofp_match *matchQueue,
                  struct sk_buff *skb)
{
    struct ofp_match *iter = matchQueue;

    while(iter)
    {
        switch(iter->field)
        {
            case OFPXMT_OFB_IN_PHY_PORT:
            {
                if (strcmp((skb->dev)->name,
                           iter->value.interface_name) == 0)
                    break;
                return 0;
            }
            case OFPXMT_OFB_ETH_DST:
            {
                unsigned char etherAddr[ETH_ALEN];
                __u8 byteIndex = 0;
                while (byteIndex < ETH_ALEN)
                {
                    etherAddr[byteIndex] = eth_hdr(skb)->h_dest[byteIndex] & 
                                           iter->mask.ethernetAddress[byteIndex];
                    byteIndex++;
                }
                
                if (memcmp( etherAddr, 
                            iter->value.ethernetAddress,
                            ETH_ALEN) == 0)
                    break;
                return 0;
            }
            case OFPXMT_OFB_ETH_SRC:
            {
                unsigned char etherAddr[ETH_ALEN];
                __u8 byteIndex = 0;
                while (byteIndex < ETH_ALEN)
                {
                    etherAddr[byteIndex] = eth_hdr(skb)->h_source[byteIndex] & 
                                           iter->mask.ethernetAddress[byteIndex];
                    byteIndex++;
                }
 
                if (memcmp( etherAddr,
                            iter->value.ethernetAddress,
                            ETH_ALEN) == 0)
                    break;
                return 0;
            }
            case OFPXMT_OFB_ETH_TYPE:
            {
                if (eth_hdr(skb)->h_proto == iter->value.ethernetProtocol)
                    break;
                return 0;
            }
            case OFPXMT_OFB_IP_DSCP:
            {
                if ((ip_hdr(skb)->tos >> 2) == iter->value.dscpField)
                    break;
                return 0;
            }
            case OFPXMT_OFB_IP_PROTO:
            {
                if (ip_hdr(skb)->protocol == iter->value.ipProtocol)
                    break;
                return 0;
            }
            case OFPXMT_OFB_IPV4_SRC:
            {
                if ((ip_hdr(skb)->saddr & iter->mask.ipAddress) ==                                                                                   
                    iter->value.ipAddress)                                 
                    break;
                return 0;
            }
            case OFPXMT_OFB_IPV4_DST:
            {
                if ((ip_hdr(skb)->daddr & iter->mask.ipAddress) ==                                                                                   
                    iter->value.ipAddress)                                 
                    break;
                return 0;
            }
            case OFPXMT_OFB_TCP_SRC:
            case OFPXMT_OFB_UDP_SRC:
            case OFPXMT_OFB_SCTP_SRC:
            {
                if (trans_hdr(skb)->source == iter->value.port)
                    break;
                return 0;
            }
            case OFPXMT_OFB_TCP_DST:
            case OFPXMT_OFB_UDP_DST:
            case OFPXMT_OFB_SCTP_DST:
            {
                if (trans_hdr(skb)->dest == iter->value.port)
                    break;
                return 0;
            }
            case OFPXMT_OFB_ICMPV4_TYPE:
            {
                if(icmp_hdr(skb)->type == iter->value.icmpType)
                    break;
                return 0;
            }
            case OFPXMT_OFB_ICMPV4_CODE:
            {
                if(icmp_hdr(skb)->code == iter->value.icmpCode)
                    break;
                return 0;
            }
            case OFPXMT_OFB_IN_PORT:
            case OFPXMT_OFB_METADATA:
            case OFPXMT_OFB_VLAN_VID:
            case OFPXMT_OFB_VLAN_PCP:
            case OFPXMT_OFB_IP_ECN:
            case OFPXMT_OFB_ARP_OP:
            case OFPXMT_OFB_ARP_SPA:
            case OFPXMT_OFB_ARP_TPA:
            case OFPXMT_OFB_ARP_SHA:
            case OFPXMT_OFB_ARP_THA:
            case OFPXMT_OFB_IPV6_SRC:
            case OFPXMT_OFB_IPV6_DST:
            case OFPXMT_OFB_IPV6_FLABEL:
            case OFPXMT_OFB_ICMPV6_TYPE:
            case OFPXMT_OFB_ICMPV6_CODE:
            case OFPXMT_OFB_IPV6_ND_TARGET:
            case OFPXMT_OFB_IPV6_ND_SLL:
            case OFPXMT_OFB_IPV6_ND_TLL:
            case OFPXMT_OFB_MPLS_LABEL:
            case OFPXMT_OFB_MPLS_TC:
            case OFPXMT_OFP_MPLS_BOS:
            case OFPXMT_OFB_PBB_ISID:
            case OFPXMT_OFB_TUNNEL_ID:
            case OFPXMT_OFB_IPV6_EXTHDR:
            default:
                return 0;

        }
        iter = (struct ofp_match *)iter->next;
    }
    printk(KERN_INFO "SUCCESS\n" );
    return 1;
}

static struct list_head flow_head;

int match_for_flow (struct list_head *head, struct sk_buff *skb)
{
    struct ofp_flow_table *iter = (struct ofp_flow_table *)head->next;
    while(iter)
    {
        if (match_values((struct ofp_match *)(iter->match->next), skb))
            return 1;

        iter=(struct ofp_flow_table*)iter->next;
    }
    return 0;
}

unsigned int hook_func(const struct nf_hook_ops *ops,
                               struct sk_buff *skb,
                               const struct net_device *in,
                               const struct net_device *out,
                               int (*okfn)(struct sk_buff *))
{
    match_for_flow(&flow_head, skb);
    return 1;
}

static struct nf_hook_ops nf_hook_open_flow;

int init_module (void)
{
    struct ofp_flow_table *new;
    nf_hook_open_flow.hook = hook_func;
    nf_hook_open_flow.pf = PF_INET;
    nf_hook_open_flow.hooknum = 0; // NF_IP_PRE_ROUTING
    nf_hook_open_flow.priority = INT_MIN; // NF_IP_PRI_FIRST
    nf_register_hook(&nf_hook_open_flow);

    printk (KERN_INFO "Inside Init of Hello World \n");

    flow_head.next = NULL;
    new = kmalloc(sizeof(struct ofp_flow_table), GFP_KERNEL);
    new->next = NULL;
    new->match =  kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->match->next = NULL;
    setupICMPFilter(new->match);
    insertElement(&flow_head, (struct list_head *)new);

    new = kmalloc(sizeof(struct ofp_flow_table), GFP_KERNEL);
    new->next = NULL;
    new->match =  kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->match->next = NULL;
    setupQueue(new->match);
    insertElement(&flow_head, (struct list_head *)new);

    return 0;
}

void cleanup_module (void)
{
    nf_unregister_hook(&nf_hook_open_flow);
    printk(KERN_INFO "Inside Clean up of Hello World \n");
}
