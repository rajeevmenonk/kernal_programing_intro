struct maskValues {
        unsigned char sourceEthernetAddress[ETH_ALEN]; // ETH_ALEN = 6
        unsigned char destEthernetAddress[ETH_ALEN]; // ETH_ALEN = 6
        char          interface_name[IFNAMSIZ];
        __u8          dscpField; // Expected with the value right shifted to right twice.
        __u8          icmpType;
        __u8          icmpCode;
        __u16         ethernetProtocol;
        __u16         ipProtocol;
        __u16         sourcePort;
        __u16         destPort;
        __be32        sourceIpAddress;
        __be32        destIpAddress;
};

struct matchValues {
        unsigned char sourceEthernetAddress[ETH_ALEN]; // ETH_ALEN = 6
        unsigned char destEthernetAddress[ETH_ALEN]; // ETH_ALEN = 6
        char          interface_name[IFNAMSIZ];
        __u8          dscpField; // Expected with the value right shifted to right twice.
        __u8          icmpType;
        __u8          icmpCode;
        __u16         ethernetProtocol;
        __u16         ipProtocol;
        __u16         sourcePort;
        __u16         destPort;
        __be32        sourceIpAddress;
        __be32        destIpAddress;
};

// Flow match fields
struct ofp_match {
    struct list_head  *next;
    __u16             class; /* One of OFPMT_* */
    __u8              field;
    __u8              hasMask;
    struct matchValues value;

//    __u16 length; /* Length of ofp_match (excluding padding) */
//    // Add padding
//    __u8 oxm_fields[4]; /* OXMs start here - Make compiler happy */
//    union matchfield {
//        unsigned char ethernetAddress[ETH_ALEN]; // ETH_ALEN = 6
//        char          interface_name[IFNAMSIZ];
//        __u8          dscpField; // Expected with the value right shifted to right twice.
//        __u8          icmpType;
//        __u8          icmpCode;
//        __u16         ethernetProtocol;
//        __u16         ipProtocol;
//        __u16         port;
//        __be32        ipAddress;
//    }                 value, mask;
};

// Instruction header.
struct ofp_instruction {
    __u16 type; /* Instruction type */
    __u16 len; /* Length of this struct in bytes. */
};

//struct ofp_instruction_actions {
//    __u16 type; /* One of OFPIT_*_ACTIONS */
//    __u16 len; /* Length of this struct in bytes. */
//    __u8 pad[4]; /* Align to 64-bits */
//    struct ofp_action_header actions[0]; /* Actions associated with OFPIT_WRITE_ACTIONS and OFPIT_APPLY_ACTIONS */
//};

struct ofp_flow_stats_request {
    __u8 table_id; /* ID of table to read (from ofp_table_stats), OFPTT_ALL for all tables. */
    __u8 pad[3]; /* Align to 32 bits. */
    __u32 out_port; /* Require matching entries to include this as an output port. A value of OFPP_ANY indicates no restriction. */
    __u32 out_group; /* Require matching entries to include this as an output group. A value of OFPG_ANY indicates no restriction. */
    __u8 pad2[4]; /* Align to 64 bits. */
    __u64 cookie; /* Require matching entries to contain this cookie value */
    __u64 cookie_mask; /* Mask used to restrict the cookie bits that must match. A value of 0 indicates no restriction. */
    struct ofp_match match; /* Fields to match. Variable size. */
};

struct ofp_flow_table {
    struct list_head *next;
    __u64 cookie; /* Opaque controller-issued identifier. */
    __u64 cookie_mask; /* Mask used to restrict the cookie bits that must match when the command is OFPFC_MODIFY* or OFPFC_DELETE*. A value of 0 indicates no restriction. */

    /* Flow actions. */
    __u8 table_id;       /* ID of the table to put the flow in.  For OFPFC_DELETE_* commands, OFPTT_ALL can also be used to delete matching flows from all tables. */
    __u8 command;        /* One of OFPFC_*. */
    __u16 idle_timeout;  /* Idle time before discarding (seconds). */                                                                                                     
    __u16 hard_timeout;  /* Max time before discarding (seconds). */                                                                                                      
    __u16 priority;      /* Priority level of flow entry. */                                                                                                                 
    __u32 buffer_id;     /* Buffered packet to apply to, or OFP_NO_BUFFER.  Not meaningful for OFPFC_DELETE*. */                                                       
    __u32 out_port;      /* For OFPFC_DELETE* commands, require matching entries to include this as an output port. A value of OFPP_ANY indicates no restriction. */  
    __u32 out_group;     /* For OFPFC_DELETE* commands, require matching entries to include this as an output group. A value of OFPG_ANY indicates no restriction. */  
    __u16 flags;         /* One of OFPFF_*. */
    __u8 pad[2]; /* Fields to match. Variable size. */
    struct list_head *match; //struct ofp_instruction instructions[0]; /* Instruction set */
    struct ofp_instruction instructions[0]; /* Instruction set */
};
