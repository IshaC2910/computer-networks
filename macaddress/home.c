#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

void getMacAddress(const char *interface_name, unsigned char mac_address[6]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("socket");
        return;
    }

    struct ifreq ifr;
    strncpy(ifr.ifr_name, interface_name, IFNAMSIZ - 1);
    
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) == -1) {
        perror("ioctl");
        close(sock);
        return;
    }

    memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);
    close(sock);
}

int main() {
    const char *interface_name = "enp3s0"; // Change this to your network interface name
    unsigned char mac_address[6];

    getMacAddress(interface_name, mac_address);

    printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
           mac_address[0], mac_address[1], mac_address[2],
           mac_address[3], mac_address[4], mac_address[5]);

    return 0;
}

