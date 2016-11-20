#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/kthread.h>
#include <net/ip.h>
#include <net/arp.h>
#include <net/sock.h>
#include <linux/delay.h>

#define OF_SOURCE_IP 3232236546
#define NEXT_HOP_IP_OF 3232236034

static struct task_struct *pReadThread;
static struct task_struct *pWriteThread;
static struct socket        *socket = NULL;

struct net_device *OfcGetNetDevByName (char *pIfName)                                                                                                 
{
    struct net_device *pTempDev = NULL;

    pTempDev = first_net_device (&init_net);
    while (pTempDev)
    {
        if (!strcmp (pTempDev->name, pIfName))
        {
            printk (KERN_INFO "Device found\r\n");
            return pTempDev;
        }
        pTempDev = next_net_device (pTempDev);
    }

    return NULL;
}


void readFun (void *args)
{
    struct msghdr msg;
    struct iovec  iov;
    mm_segment_t  old_fs;
    __u32         msgLen = 0;
    __u8          *pDataPkt = NULL;

    printk("read fun begin \n");
    pDataPkt = (__u8 *) kmalloc (1000, GFP_KERNEL);
    if (pDataPkt == NULL)
    {
        printk (KERN_CRIT "Failed to allocate memory to data " 
                "packet!!\r\n");
        return;
    }

    memset (&msg, 0, sizeof(msg));
    memset (&iov, 0, sizeof(iov));
    memset (pDataPkt, 0, 1000);
    iov.iov_base = pDataPkt;
    iov.iov_len = 1000;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    msgLen = sock_recvmsg (socket, &msg, 1000, 0);
    set_fs(old_fs);
    printk("read fun end \n");
}

void writeFun(void *args)
{
    struct msghdr msg;
    struct iovec  iov;
    mm_segment_t  old_fs;
    __u32         msgLen = 0;
    char          pPkt[] = "test";

    printk("write fun begin \n");
    memset (&msg, 0, sizeof(msg));
    memset (&iov, 0, sizeof(iov));
    iov.iov_base = pPkt;
    iov.iov_len = 4;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    msgLen = sock_sendmsg (socket,
            &msg, 4);
    set_fs(old_fs);
    if (msgLen == 0)
    {
        printk (KERN_CRIT "Failed to send message from data "
                "socket!!\r\n");
        return;
    }

    printk("write fun end %d \n", msgLen);
}

int init_module (void)
{
    struct net_device    *dev = NULL;                                                                                                                 
    struct sockaddr_ll   socketBindAddr;

    printk (KERN_INFO "Inside Init of Hello World \n");

    if ((sock_create (AF_PACKET, SOCK_RAW, htons(ETH_P_ALL),
                    &socket)) < 0)
    {
        printk (KERN_CRIT "Failed to open data socket!!\r\n");
        return 1;
    }

    dev = OfcGetNetDevByName ("lo");
    memset (&socketBindAddr, 0, sizeof(socketBindAddr));
    socketBindAddr.sll_family = AF_PACKET;
    socketBindAddr.sll_protocol = htons(ETH_P_ALL);
    socketBindAddr.sll_ifindex = dev->ifindex;
    if (socket->ops->bind (socket, (struct sockaddr *) &socketBindAddr, 
                sizeof(socketBindAddr)) < 0)
    {
        printk (KERN_CRIT "Failed to bind data socket!!\r\n");
        return 1;
    }
    printk("Before Sleep \n");
    pReadThread = kthread_run(readFun, NULL, "Read");
    msleep(2000);
    printk("After Sleep \n");
    pWriteThread = kthread_run(writeFun, NULL, "Write");
    return 0;
}
    
    void cleanup_module (void)
    {
        printk(KERN_INFO "Inside Clean up of Hello World \n");
}

