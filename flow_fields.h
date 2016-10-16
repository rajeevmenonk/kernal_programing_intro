
// Match type
enum ofp_match_type {
    OFPMT_STANDARD = 0, /* Deprecated. */
    OFPMT_OXM      = 1, /* OpenFlow Extensible Match */
};

// Match class
enum ofp_oxm_class {
    OFPXMC_NXM_0          = 0x0000, /* Backward compatibility with NXM */
    OFPXMC_NXM_1          = 0x0001, /* Backward compatibility with NXM */
    OFPXMC_OPENFLOW_BASIC = 0x8000, /* Basic class for OpenFlow */
    OFPXMC_EXPERIMENTER   = 0xFFFF, /* Experimenter class */
};

// Match field 
enum oxm_ofb_match_fields {
    OFPXMT_OFB_IN_PORT        =  0,   /* Switch input port. */
    OFPXMT_OFB_IN_PHY_PORT    =  1,   /* Switch physical input port. */           
    OFPXMT_OFB_METADATA       =  2,   /* Metadata passed between tables. */    
    OFPXMT_OFB_ETH_DST        =  3,   /* Ethernet destination address. */
    OFPXMT_OFB_ETH_SRC        =  4,   /* Ethernet source address. */
    OFPXMT_OFB_ETH_TYPE       =  5,   /* Ethernet frame type. */               
    OFPXMT_OFB_VLAN_VID       =  6,   /* VLAN id. */                           
    OFPXMT_OFB_VLAN_PCP       =  7,   /* VLAN priority. */                     
    OFPXMT_OFB_IP_DSCP        =  8,   /* IP DSCP (6 bits in ToS field). */
    OFPXMT_OFB_IP_ECN         =  9,   /* IP ECN (2 bits in ToS field). */
    OFPXMT_OFB_IP_PROTO       =  10,  /* IP protocol. */                       
    OFPXMT_OFB_IPV4_SRC       =  11,  /* IPv4 source address. */               
    OFPXMT_OFB_IPV4_DST       =  12,  /* IPv4 destination address. */          
    OFPXMT_OFB_TCP_SRC        =  13,  /* TCP source port. */
    OFPXMT_OFB_TCP_DST        =  14,  /* TCP destination port. */
    OFPXMT_OFB_UDP_SRC        =  15,  /* UDP source port. */
    OFPXMT_OFB_UDP_DST        =  16,  /* UDP destination port. */
    OFPXMT_OFB_SCTP_SRC       =  17,  /* SCTP source port. */                  
    OFPXMT_OFB_SCTP_DST       =  18,  /* SCTP destination port. */             
    OFPXMT_OFB_ICMPV4_TYPE    =  19,  /* ICMP type. */                            
    OFPXMT_OFB_ICMPV4_CODE    =  20,  /* ICMP code. */                            
    OFPXMT_OFB_ARP_OP         =  21,  /* ARP opcode. */
    OFPXMT_OFB_ARP_SPA        =  22,  /* ARP source IPv4 address. */
    OFPXMT_OFB_ARP_TPA        =  23,  /* ARP target IPv4 address. */
    OFPXMT_OFB_ARP_SHA        =  24,  /* ARP source hardware address. */
    OFPXMT_OFB_ARP_THA        =  25,  /* ARP target hardware address. */
    OFPXMT_OFB_IPV6_SRC       =  26,  /* IPv6 source address. */               
    OFPXMT_OFB_IPV6_DST       =  27,  /* IPv6 destination address. */          
    OFPXMT_OFB_IPV6_FLABEL    =  28,  /* IPv6 Flow Label */                       
    OFPXMT_OFB_ICMPV6_TYPE    =  29,  /* ICMPv6 type. */                          
    OFPXMT_OFB_ICMPV6_CODE    =  30,  /* ICMPv6 code. */                          
    OFPXMT_OFB_IPV6_ND_TARGET =  31,  /* Target address for ND. */                   
    OFPXMT_OFB_IPV6_ND_SLL    =  32,  /* Source link-layer for ND. */             
    OFPXMT_OFB_IPV6_ND_TLL    =  33,  /* Target link-layer for ND. */             
    OFPXMT_OFB_MPLS_LABEL     =  34,  /* MPLS label. */                          
    OFPXMT_OFB_MPLS_TC        =  35,  /* MPLS TC. */
    OFPXMT_OFP_MPLS_BOS       =  36,  /* MPLS BoS bit. */                      
    OFPXMT_OFB_PBB_ISID       =  37,  /* PBB I-SID. */                         
    OFPXMT_OFB_TUNNEL_ID      =  38,  /* Logical Port Metadata. */              
    OFPXMT_OFB_IPV6_EXTHDR    =  39,  /* IPv6 Extension Header pseudo-field */    
};

// Instruction Type
enum ofp_instruction_type {
    OFPIT_GOTO_TABLE     = 1,        /* Setup the next table in the lookup pipeline */
    OFPIT_WRITE_METADATA = 2,    /* Setup the metadata field for use later in pipeline */    
    OFPIT_WRITE_ACTIONS  = 3,     /* Write the action(s) onto the datapath action set */     
    OFPIT_APPLY_ACTIONS  = 4,     /* Applies the action(s) immediately */                    
    OFPIT_CLEAR_ACTIONS  = 5,     /* Clears all actions from the datapath action set */      
    OFPIT_METER          = 6,             /* Apply meter (rate limiter) */
    OFPIT_EXPERIMENTER   = 0xFFFF  /* Experimenter instruction */                                
};

enum ofp_action_type {
    OFPAT_OUTPUT       = 0, /* Output to switch port. */
    OFPAT_COPY_TTL_OUT = 11, /* Copy TTL "outwards" -- from next-to-outermost to outermost */
    OFPAT_COPY_TTL_IN  = 12, /* Copy TTL "inwards" -- from outermost to next-to-outermost */
    OFPAT_SET_MPLS_TTL = 15, /* MPLS TTL */
    OFPAT_DEC_MPLS_TTL = 16, /* Decrement MPLS TTL */
    OFPAT_PUSH_VLAN    =  17, /* Push a new VLAN tag */
    OFPAT_POP_VLAN     =  18, /* Pop the outer VLAN tag */
    OFPAT_PUSH_MPLS    =  19, /* Push a new MPLS tag */
    OFPAT_POP_MPLS     =  20, /* Pop the outer MPLS tag */
    OFPAT_SET_QUEUE    =  21, /* Set queue id when outputting to a port */
    OFPAT_GROUP        =  22, /* Apply group. */
    OFPAT_SET_NW_TTL   =  23, /* IP TTL. */                                  
    OFPAT_DEC_NW_TTL   =  24, /* Decrement IP TTL. */
    OFPAT_SET_FIELD    =  25, /* Set a header field using OXM TLV format. */
    OFPAT_PUSH_PBB     =  26, /* Push a new PBB service tag (I-TAG) */
    OFPAT_POP_PBB      =  27, /* Pop the outer PBB service tag (I-TAG) */
    OFPAT_EXPERIMENTER =  0xffff    
};

// Possible flow mod commands.
enum ofp_flow_mod_command
{
    OFPFC_ADD           = 0, /* New flow. */
    OFPFC_MODIFY        = 1, /* Modify all matching flows. */                  
    OFPFC_MODIFY_STRICT = 2, /* Modify entry strictly matching wildcards and priority. */
    OFPFC_DELETE        = 3, /* Delete all matching flows. */
    OFPFC_DELETE_STRICT = 4, /* Delete entry strictly matching wildcards and priority. */
};

// Flow match fields
struct ofp_match {
    uint16_t type; /* One of OFPMT_* */
    uint16_t length; /* Length of ofp_match (excluding padding) */
    // Add padding
    uint8_t oxm_fields[4]; /* OXMs start here - Make compiler happy */
};

// Instruction header.
struct ofp_instruction {
    uint16_t type; /* Instruction type */
    uint16_t len; /* Length of this struct in bytes. */
};

//struct ofp_instruction_actions {
//    uint16_t type; /* One of OFPIT_*_ACTIONS */
//    uint16_t len; /* Length of this struct in bytes. */
//    uint8_t pad[4]; /* Align to 64-bits */
//    struct ofp_action_header actions[0]; /* Actions associated with OFPIT_WRITE_ACTIONS and OFPIT_APPLY_ACTIONS */
//};

struct ofp_flow_stats_request {
    uint8_t table_id; /* ID of table to read (from ofp_table_stats), OFPTT_ALL for all tables. */
    uint8_t pad[3]; /* Align to 32 bits. */
    uint32_t out_port; /* Require matching entries to include this as an output port. A value of OFPP_ANY indicates no restriction. */
    uint32_t out_group; /* Require matching entries to include this as an output group. A value of OFPG_ANY indicates no restriction. */
    uint8_t pad2[4]; /* Align to 64 bits. */
    uint64_t cookie; /* Require matching entries to contain this cookie value */
    uint64_t cookie_mask; /* Mask used to restrict the cookie bits that must match. A value of 0 indicates no restriction. */
    struct ofp_match match; /* Fields to match. Variable size. */
};

struct ofp_flow_table {
    struct ofp_header header;
    uint64_t cookie; /* Opaque controller-issued identifier. */
    uint64_t cookie_mask; /* Mask used to restrict the cookie bits that must match when the command is OFPFC_MODIFY* or OFPFC_DELETE*. A value of 0 indicates no restriction. */
    /* Flow actions. */
    uint8_t table_id;       /* ID of the table to put the flow in.  For OFPFC_DELETE_* commands, OFPTT_ALL can also be used to delete matching flows from all tables. */
    uint8_t command;        /* One of OFPFC_*. */
    uint16_t idle_timeout;  /* Idle time before discarding (seconds). */                                                                                                     
    uint16_t hard_timeout;  /* Max time before discarding (seconds). */                                                                                                      
    uint16_t priority;      /* Priority level of flow entry. */                                                                                                                 
    uint32_t buffer_id;     /* Buffered packet to apply to, or OFP_NO_BUFFER.  Not meaningful for OFPFC_DELETE*. */                                                       
    uint32_t out_port;      /* For OFPFC_DELETE* commands, require matching entries to include this as an output port. A value of OFPP_ANY indicates no restriction. */  
    uint32_t out_group;     /* For OFPFC_DELETE* commands, require matching entries to include this as an output group. A value of OFPG_ANY indicates no restriction. */  
    uint16_t flags;         /* One of OFPFF_*. */
    uint8_t pad[2]; /* Fields to match. Variable size. */
    struct ofp_match match; //struct ofp_instruction instructions[0]; /* Instruction set */
    struct ofp_instruction instructions[0]; /* Instruction set */
};
