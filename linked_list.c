#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/kthread.h>
#include <net/ip.h>
#include <net/arp.h>
#include <net/sock.h>

struct listTracker
{
    struct listTracker *next;
};

struct flowStruct 
{
    struct listTracker *next;
    int value;
};

void insertElement (struct listTracker *head, 
                    struct listTracker *new)
{
    struct listTracker *iter = head;
    while(iter->next)
        iter = iter->next;

    iter->next = new;
}

void deleteElement (struct listTracker *head,
                    struct listTracker *toDelete)
{
    struct listTracker *iter = head;
    while(iter->next && iter->next != toDelete)
       iter = iter->next;

    //if (!iter->next)
    //    return;

    iter->next = toDelete->next;
}

void printList (struct listTracker *head)
{
    struct flowStruct *new = (struct flowStruct *)head->next;
    while(new)
    {
        printk (KERN_INFO "\n The value is %d", new->value);
        new=(struct flowStruct *)new->next;
    }
}

static struct listTracker *head;
int init_module (void)
{
    printk (KERN_INFO "Inside Init of Hello World \n");
    head = kmalloc(sizeof(struct listTracker), GFP_KERNEL);
    head->next = NULL;

    struct flowStruct *new;

    int i = 1;
    while(i < 6)
    {
        printk (KERN_INFO "Adding element to linked list %d \n", i);
        new = kmalloc(sizeof(struct flowStruct), GFP_KERNEL);
        new->value = i*10;
        new->next = NULL;
        insertElement(head, (struct listTracker *)new);
        i++;
    }

    new = (struct FlowStruct *)head->next;
    while(new)
    {
        printk (KERN_INFO "\n Printing values %d", new->value);
        new = (struct FlowStruct *)new->next;
    }

    printk (KERN_INFO "Before return Inside Init of Hello World \n");
    return 0;
}

void cleanup_module (void)
{
    printk(KERN_INFO "Inside Clean up of Hello World \n");
    struct flowStruct *new = (struct flowStruct *)head->next;
    while(new)
    {
	printk(KERN_INFO "Value being deleted is %d \n", new->value);
        deleteElement(head, (struct listTracker*)new);
        kfree(new);
        printList(head);
        new = (struct flowStruct *)head->next;
    }
    kfree(head);
}

