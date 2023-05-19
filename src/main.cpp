#include "../lib/IpFilter.h"

void help() {
    std::cout << "Please enter ipv4 address like this mask xxx.xxx.xxx.xxx or type \"q\" for sort\n" << std::endl;
}

int main () {
    help();

    IpFilter ipFilter;
    std::string ip{};
    std::vector<int> parsedIp;

    while (std::getline(std::cin, ip)) {
        if (ip == "q") {
            break;
        }
        if (!ipFilter.checkIpLen(ip, parsedIp)) {
            std::cerr << "Error parsing: " << ip <<" is not have ip address\n" << std::endl;
        }
    }

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




