/* Receive Multicast Datagram code example. */

#include <arpa/inet.h>

#include <stdio.h> /* for printf & perror */
#include <stdlib.h> /* for exit */
#include <string.h> /* for memset */
#include <unistd.h> /* for close */

#include "settings.h"

int main() {
    struct sockaddr_in localInterface;
    struct ip_mreq group;
    int socketHandle;
    char data[1024];
    int dataLength;

    /* Create a datagram socket on which to receive. */
    socketHandle = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketHandle < 0) {
        perror("Opening datagram socket error");
        exit(1);
    } else {
        printf("Opening datagram socket....OK.\n");
    }

    /* Enable SO_REUSEADDR to allow multiple instances of this */
    /* application to receive copies of the multicast datagrams. */
    {
        int reuse = 1;
        if (setsockopt(socketHandle, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
            perror("Setting SO_REUSEADDR error");
            close(socketHandle);
            exit(1);
        } else {
            printf("Setting SO_REUSEADDR...OK.\n");
        }
    }

    /* Bind to the proper port number with the IP address specified as INADDR_ANY. */
    memset((char*)&localInterface, 0, sizeof(localInterface));
    localInterface.sin_family = AF_INET;
    localInterface.sin_port = htons(port);
    localInterface.sin_addr.s_addr = INADDR_ANY;
    if (bind(socketHandle, (struct sockaddr*)&localInterface, sizeof(localInterface))) {
        perror("Binding datagram socket error");
        close(socketHandle);
        exit(1);
    } else {
        printf("Binding datagram socket...OK.\n");
    }

    /* Join the multicast group on the local interface */
    /* Note that this IP_ADD_MEMBERSHIP option must be called for each local interface */
    /* over which the multicast datagrams are to be received. */
    group.imr_multiaddr.s_addr = inet_addr(multicastAddress);
    group.imr_interface.s_addr = inet_addr(localAddress);
    if (setsockopt(socketHandle, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group)) < 0) {
        perror("Adding multicast group error");
        close(socketHandle);
        exit(1);
    } else {
        printf("Adding multicast group...OK.\n");
    }

    /* Read data from the socket. */
    dataLength = sizeof(data);
    if (read(socketHandle, data, dataLength) < 0) {
        perror("Reading datagram message error");
        close(socketHandle);
        exit(1);
    } else {
        printf("Reading datagram message...OK.\n");
        printf("The message from multicast server is: \"%s\"\n", data);
    }

    close(socketHandle);
    return 0;
}
