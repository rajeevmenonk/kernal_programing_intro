void insertElement (struct list_head *head, 
                    struct list_head *tail,
                    struct list_head *new)
{
    if (!head->next)
        head->next = new;
    else
        (tail->next)->next = new;

    tail->next = new;
}

void deleteElement (struct list_head *head,
                    struct list_head *tail)
{
    head->next = (head->next)->next;
    if(!head->next)
        tail->next = NULL;
}


void setupICMPFilter (struct list_head *head,
                      struct list_head *tail)
{
    struct ofp_match *new;

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_ETH_SRC;
    new->value.ethernetAddress[0] = 0x00; // 0
    new->value.ethernetAddress[1] = 0x50; // 80
    new->value.ethernetAddress[2] = 0x56; // 86
    new->value.ethernetAddress[3] = 0x08; // 8
    new->value.ethernetAddress[4] = 0x00; // 170
    new->value.ethernetAddress[5] = 0x00; // 35
    new->mask.ethernetAddress[0] = 0xff;
    new->mask.ethernetAddress[1] = 0xff;
    new->mask.ethernetAddress[2] = 0xff;
    new->mask.ethernetAddress[3] = 0xff;
    new->mask.ethernetAddress[4] = 0x00;
    new->mask.ethernetAddress[5] = 0x00;
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_ETH_DST;
    new->value.ethernetAddress[0] = 0x00;
    new->value.ethernetAddress[1] = 0x00;
    new->value.ethernetAddress[2] = 0x00;
    new->value.ethernetAddress[3] = 0x00;
    new->value.ethernetAddress[4] = 0x00;
    new->value.ethernetAddress[5] = 0x00;
    new->mask.ethernetAddress[0] = 0x00;
    new->mask.ethernetAddress[1] = 0x00;
    new->mask.ethernetAddress[2] = 0x00;
    new->mask.ethernetAddress[3] = 0x00;
    new->mask.ethernetAddress[4] = 0x00;
    new->mask.ethernetAddress[5] = 0x00;
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_ETH_TYPE;
    new->value.ethernetProtocol = htons(0x0800);
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_IPV4_SRC;
    new->value.ipAddress = htonl(169412470); // 10.25.7.118
    new->mask.ipAddress = 0xffffffff;
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_IPV4_DST;
    new->value.ipAddress = 0;
    new->mask.ipAddress = 0;
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_IP_PROTO;
    new->value.ipProtocol = 1; // ICMP
    insertElement(head, tail, (struct list_head *)new);


    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_ICMPV4_TYPE;
    new->value.icmpType = ICMP_ECHO;
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_ICMPV4_CODE;
    new->value.icmpCode = 0;
    insertElement(head, tail, (struct list_head *)new);
}

void setupQueue( struct list_head *head, struct list_head *tail)
{
    struct ofp_match *new;

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_ETH_SRC;
    new->value.ethernetAddress[0] = 0x00; // 0
    new->value.ethernetAddress[1] = 0x50; // 80
    new->value.ethernetAddress[2] = 0x56; // 86
    new->value.ethernetAddress[3] = 0x08; // 8
    new->value.ethernetAddress[4] = 0x00; // 170
    new->value.ethernetAddress[5] = 0x00; // 35
    new->mask.ethernetAddress[0] = 0xff;
    new->mask.ethernetAddress[1] = 0xff;
    new->mask.ethernetAddress[2] = 0xff;
    new->mask.ethernetAddress[3] = 0xff;
    new->mask.ethernetAddress[4] = 0x00;
    new->mask.ethernetAddress[5] = 0x00;
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_ETH_DST;
    new->value.ethernetAddress[0] = 0x00;
    new->value.ethernetAddress[1] = 0x00;
    new->value.ethernetAddress[2] = 0x00;
    new->value.ethernetAddress[3] = 0x00;
    new->value.ethernetAddress[4] = 0x00;
    new->value.ethernetAddress[5] = 0x00;
    new->mask.ethernetAddress[0] = 0x00;
    new->mask.ethernetAddress[1] = 0x00;
    new->mask.ethernetAddress[2] = 0x00;
    new->mask.ethernetAddress[3] = 0x00;
    new->mask.ethernetAddress[4] = 0x00;
    new->mask.ethernetAddress[5] = 0x00;
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_ETH_TYPE;
    new->value.ethernetProtocol = htons(0x0800);
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_IPV4_SRC;
    new->value.ipAddress = htonl(169412470); // 10.25.7.118
    new->mask.ipAddress = 0xffffffff;
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_IPV4_DST;
    new->value.ipAddress = 0;
    new->mask.ipAddress = 0;
    insertElement(head, tail, (struct list_head *)new);


    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_IP_PROTO;
    new->value.ipProtocol = 6;
    insertElement(head, tail, (struct list_head *)new);

    new= kmalloc(sizeof(struct ofp_match), GFP_KERNEL);
    new->next = NULL;
    new->field = OFPXMT_OFB_TCP_DST;
    new->value.port = htons(11111);
    insertElement(head, tail, (struct list_head *)new);
}


