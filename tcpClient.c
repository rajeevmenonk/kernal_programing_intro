#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/kthread.h>
#include <net/sock.h>
#include <linux/inet.h>

#define OF_SOURCE_IP 3232236546
#define NEXT_HOP_IP_OF 3232236034

void send_the_packet_out (struct sk_buff *skb)
{
    struct socket *socket = NULL;
    struct sockaddr_in servaddr;

    struct iovec iov;
    struct msghdr msg;

    __u8 buffer[100];
    mm_segment_t old_fs;

    if (sock_create(AF_INET, SOCK_STREAM, IPPROTO_TCP, &socket) < 0)
    {
        printk (KERN_INFO "SOCKET OPEN FAILED \n");
        return;
    }

    memset(&servaddr,0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6633);
    servaddr.sin_addr.s_addr = in_aton("127.0.0.1");

    socket->ops->connect(socket,
                         (struct sockaddr *) &servaddr,
                         sizeof(servaddr), O_RDWR);

    memset(&iov, 0, sizeof(struct iovec));
    memset(&msg, 0, sizeof(struct msghdr));

    iov.iov_base = buffer;
    iov.iov_len = 100;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    old_fs = get_fs();
    set_fs(KERNEL_DS);
    int size = sock_recvmsg(socket, &msg, 100, 0);
    set_fs(old_fs);

    int i = 0;
    int value = 0;
    while ( i < size)
    {
        value = buffer[i];
        printk (KERN_INFO "\nTHE PACKET DATA for byte %d is %d \n", i, value);
        i++;
    }
}

static struct task_struct *thread_new;
int init_module (void)
{
    struct sk_buff *skb = kmalloc(sizeof(*skb), GFP_KERNEL);
    printk (KERN_INFO "Inside Init of Hello World \n");
    skb->len = 100;
    thread_new = kthread_run(&send_the_packet_out, skb, "testThread");
    return 0;
}

void cleanup_module (void)
{
    printk(KERN_INFO "Inside Clean up of Hello World \n");
}

