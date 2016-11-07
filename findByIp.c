#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/inetdevice.h>
#include <linux/ip.h>

extern struct net init_net;

int fun ( __u32 ip, int num)
{
    return ((ip >> num) & 0xFF);
}
int init_module (void)
{

     struct net_device *pTempDev = NULL;
     __u32 ipAddr = 2553155789;
     unsigned char mac_address[6];

     printk (KERN_INFO "Inside Init of Hello World \n");

     pTempDev = first_net_device (&init_net);                                                                                                          
     while (pTempDev)
     {
         for_ifa(pTempDev->ip_ptr) {
             if ((ifa->ifa_mask & ifa->ifa_address) == (ifa->ifa_mask & htonl(ipAddr)))
             {
                memcpy(&mac_address,pTempDev->dev_addr,6);
                printk(KERN_INFO "FOUND %u EOF\n", *(mac_address+0)); 
                printk(KERN_INFO "FOUND %u EOF\n", *(mac_address+1)); 
                printk(KERN_INFO "FOUND %u EOF\n", *(mac_address+2)); 
                printk(KERN_INFO "FOUND %u EOF\n", *(mac_address+3)); 
                printk(KERN_INFO "FOUND %u EOF\n", *(mac_address+4)); 
                printk(KERN_INFO "FOUND %u EOF\n", *(mac_address+5)); 
                printk(KERN_INFO "Local %d.%d.%d.%d \n",     fun(ntohl(ifa->ifa_local), 0),     fun(ntohl(ifa->ifa_local), 16),     fun(ntohl(ifa->ifa_local), 16),     fun(ntohl(ifa->ifa_local), 24));
                printk(KERN_INFO "address %d.%d.%d.%d \n",   fun(ntohl(ifa->ifa_address), 0),   fun(ntohl(ifa->ifa_address), 16),   fun(ntohl(ifa->ifa_address), 16),   fun(ntohl(ifa->ifa_address), 24));
                printk(KERN_INFO "mask %d.%d.%d.%d \n",      fun(ntohl(ifa->ifa_mask), 0),      fun(ntohl(ifa->ifa_mask), 16),      fun(ntohl(ifa->ifa_mask), 16),      fun(ntohl(ifa->ifa_mask), 24));
                printk(KERN_INFO "broadcast %d.%d.%d.%d \n", fun(ntohl(ifa->ifa_broadcast), 0), fun(ntohl(ifa->ifa_broadcast), 16), fun(ntohl(ifa->ifa_broadcast), 16), fun(ntohl(ifa->ifa_broadcast), 24));
             }
         }
         endfor_ifa(indev)
         pTempDev = next_net_device (pTempDev);

     }

    return 0;
}

void cleanup_module (void)
{
    printk(KERN_INFO "Inside Clean up of Hello World \n");
}

