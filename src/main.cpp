#include "../lib/IpFilter.h"

void usage() {
    std::cout << "Example:\n"
        "./ipaddr Ip1 Ip2 Ip3 ... IpN\n" << std::endl;
}

bool checkArgLen(int len) {
    return len > 1;
}

int main (int argc, char* argv[]) {
    if (!checkArgLen(argc)) {
        std::cerr << "Invalid argument count\n" << std::endl;
        usage();
        return -1;
    }
    IpFilter ipFilter;
    ipFilter.parseArguments(argc, argv);

    std::cout << "\n1.show sorted Ips:" << std::endl;
    for(uint32_t bin : ipFilter.getSortedIps()) {
        uint8_t* bytes = (uint8_t*)&bin;
        std::cout << (int)bytes[0] << "." << (int)bytes[1] << "." << (int)bytes[2] << "." << (int)bytes[3] << std::endl;
    }

    std::cout << "\n2.show ips, when ip = 1.*.*.* :" << std::endl;
    for(uint32_t bin : ipFilter.getSortedIps()) {
        uint8_t* bytes = (uint8_t*)&bin;
        if ((int)bytes[0] == 1) {
            std::cout << (int)bytes[0] << "." << (int)bytes[1] << "." << (int)bytes[2] << "." << (int)bytes[3] << std::endl;
        }
    }

    std::cout << "\n3.show ips, when ip = 46.70.*.*:" << std::endl;
    for(uint32_t bin : ipFilter.getSortedIps()) {
        uint8_t* bytes = (uint8_t*)&bin;
        if ((int)bytes[0] == 46 && (int)bytes[0] == 70) {
            std::cout << (int)bytes[0] << "." << (int)bytes[1] << "." << (int)bytes[2] << "." << (int)bytes[3] << std::endl;
        }
    }

    std::cout << "\n4.show ips, when ip have any octets = 46:" << std::endl;
    for(uint32_t bin : ipFilter.getSortedIps()) {
        uint8_t* bytes = (uint8_t*)&bin;
        if ((int)bytes[0] == 46 || (int)bytes[1] == 46 || (int)bytes[2] == 46 || (int)bytes[3] == 46) {
            std::cout << (int)bytes[0] << "." << (int)bytes[1] << "." << (int)bytes[2] << "." << (int)bytes[3] << std::endl;
        }
    }
    return 0;
}




