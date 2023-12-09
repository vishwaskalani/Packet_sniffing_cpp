#include <iostream>
#include <fstream>
// cstring contains some useful cpp functions for c style strings like strcpy, memcpy, mmeset etc
#include <cstring>
#include <iomanip>
// Defines fundamental data structures and macros for internet protocols
// including in_addr_t for IPv4 addresses, in_port_t for port numbers, 
// structures like sockaddr_in for socket addresses
#include <netinet/in.h>
// Defines structures and functions specific to the ICMP protocol, 
// including struct icmphdr for ICMP headers 
// functions like inet_ntoa for converting IP addresses to strings
// icmp is a network layer protocol
// used by network devices, including routers, to send error messages and operational information
#include <netinet/ip_icmp.h>
// Defines structures and functions related to the UDP protocol, 
// including struct udphdr for UDP headers and 
//functions like getsockopt and setsockopt for socket options.
#include <netinet/udp.h>
// Defines structures and functions for the TCP protocol, 
// including struct tcphdr for TCP headers and 
// functions like connect and send for socket communication.
#include <netinet/tcp.h>
// Defines structures and functions for the IP protocol, 
// including struct iphdr for IP headers and functions like htonl and ntohl 
// for converting network byte order to host byte order.
#include <netinet/ip.h>
// Defines structures and macros related to the Ethernet protocol, 
// including struct ether_header for Ethernet headers and 
// macros like ETHER_ADDR_LEN for the length of an Ethernet address.
#include <netinet/if_ether.h>
#include <net/ethernet.h>
// Below is the core socket programming library
// Provides core socket programming functionalities, 
// including definitions for socket types, socket creation functions 
//like socket and bind, and communication functions like sendto and recvfrom
#include <sys/socket.h>
// Defines functions for manipulating internet addresses, 
// including inet_addr for converting a string address to an integer and 
// inet_ntoa for converting an integer address to a string.
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
// Understanding why byte order conversion is needed
// data is often exchanged between different machines with different architectures
// Two main types of byte orders : big endian (MSB at lowest mem addr) and little endian (lsb at lowest memory addr)
// Network byte order is always big-endian.