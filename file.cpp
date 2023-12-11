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


void ProcessPacket(unsigned char*, int);
void print_ip_header(unsigned char*, int);
void print_tcp_packet(unsigned char*, int);
void print_udp_packet(unsigned char*, int);
void print_icmp_packet(unsigned char*, int);
void PrintData(unsigned char*, int);

std::ofstream logfile;
// struct describing an internet socket address
struct sockaddr_in source,dest;
// global variables
int tcp = 0, udp = 0, icmp = 0, others = 0, igmp = 0, total = 0, i, j;

int main()
{
    int saddr_size, data_size;

	// we will store the information of sender of received packet
    struct sockaddr saddr;

    unsigned char* buffer = new unsigned char[65536]; // Its Big!

    logfile.open("log.txt");
    if (!logfile.is_open())
    {
        std::cout << "Unable to create log.txt file." << std::endl;
        return 1;
    }
    std::cout << "Starting..." << std::endl;

	// creating a raw socket with the below parameters
    int sock_raw = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	// if there is error in socket creation
	// may be due to insufficient priveleges
    if (sock_raw < 0)
    {
        perror("Socket Error");
        return 1;
    }

	// looping continuously to receive packets
	// extracting the information from the packets in the below loop
	// Using the function ProcessPacket
    while (1)
    {
        saddr_size = sizeof(saddr);
		// u can see an interesting typecasting here (socklen_t*)&saddr_size
		// (socklen_t*) casts the pointer to the type socklen_t*. 
		// This means we are treating the memory location pointed to by &saddr_size 
		// as if it stores a pointer of type socklen_t
        data_size = recvfrom(sock_raw, buffer, 65536, 0, &saddr, (socklen_t*)&saddr_size);
        if (data_size < 0)
        {
            std::cout << "Recvfrom error, failed to get packets" << std::endl;
            return 1;
        }
        ProcessPacket(buffer, data_size);
    }

	// closing the raw socket
    close(sock_raw);
    std::cout << "Finished" << std::endl;
    return 0;
}