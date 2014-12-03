/* Send Multicast Datagram code example. */

#include <arpa/inet.h>
#include <stdio.h> /* for printf & perror */
#include <stdlib.h> /* for exit */
#include <string.h> /* for memset */
#include <unistd.h> /* for close */

#include "settings.h"

char data[1024] = "Multicast test message lol!";

void setMulticastLoopback(int socketHandle, char on) {
    if (setsockopt(socketHandle, IPPROTO_IP, IP_MULTICAST_LOOP, &on, sizeof(on)) < 0) {
        perror("Setting IP_MULTICAST_LOOP error");
        close(socketHandle);
        exit(1);
    } else {
        if (on) {
            printf("Enabling the loopback...OK.\n");
        } else {
            printf("Disabling the loopback...OK.\n");
        }
    }
}

int main() {
    struct in_addr localInterface;
    struct sockaddr_in group;
    int socketHandle;

    /* Create a datagram socket on which to send. */
    socketHandle = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketHandle < 0) {
        perror("Opening datagram socket error");
        exit(1);
    } else {
        printf("Opening the datagram socket...OK.\n");
    }

    /* Initialize the group sockaddr structure. */
    memset((char*)&group, 0, sizeof(group));
    group.sin_family = AF_INET;
    group.sin_addr.s_addr = inet_addr(multicastAddress);
    group.sin_port = htons(port);

    /* Disable loopback so you do not receive your own datagrams. */
    /* setMulticastLoopback(socketHandle, 0); */

    /* Set local interface for outbound multicast datagrams. */
    /* The IP address specified must be associated with a local, multicast capable interface. */
    localInterface.s_addr = inet_addr(localAddress);
    if (setsockopt(
        socketHandle,
        IPPROTO_IP,
        IP_MULTICAST_IF,
        &localInterface,
        sizeof(localInterface)
    ) < 0) {
        perror("Setting local interface error");
        exit(1);
    } else {
        printf("Setting the local interface...OK.\n");
    }

    /* Send a message to the multicast group specified by the group sockaddr structure. */
    if (sendto(socketHandle, data, sizeof(data), 0, (struct sockaddr*)&group, sizeof(group)) < 0) {
        perror("Sending datagram message error");
    } else {
        printf("Sending datagram message...OK.\n");
    }

    close(socketHandle);
    return 0;
}
