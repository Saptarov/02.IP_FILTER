#include "IpFilter.h"

IpFilter::IpFilter()
{

}

void IpFilter::parseArguments(int argc, char** argv) {
    for (int i = START_INDEX; i < argc; ++i) {
        std::string ip = argv[i];

        std::vector<int> parsedIp;
        if (!checkIpLen(ip, parsedIp)) {
            std::cerr << "Error parsing: " << ip <<" is not have ip address\n" << std::endl;
        }

        if (parsedIp.size()) {
            std::for_each(parsedIp.begin(), parsedIp.end(), [](int octet){std::cout << octet << " ";});
            std::cout << std::endl;
        }

        uint8_t ipbytes[4] = {(uint8_t)parsedIp[0],(uint8_t)parsedIp[1],(uint8_t)parsedIp[2],(uint8_t)parsedIp[3]};
        uint32_t ipBin = ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
        sortIp(orderedIps, ipBin);
    }
}

const std::vector<uint32_t>& IpFilter::getSortedIps() {
    assert(orderedIps.size() > 0);
    return orderedIps;
}

bool IpFilter::isNumber(const std::string& availNumber) {
    for (const auto& c : availNumber) {
        if (std::isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

bool IpFilter::exitIfNoIp(const std::string& ip_value) {
    if (ip_value.empty() || !isNumber(ip_value)) {
        std::cerr << "Invalid ip address type: " << (ip_value.empty() ? "empty" : ip_value) << std::endl;
        return false;
    }
    return true;
}

void IpFilter::getNumber(std::string ipAddr, std::vector<int>& parsedIp) {
    auto pos = ipAddr.find(".");
    if (pos != std::string::npos) {
        std::string ip_value = ipAddr.substr(0, pos);
        if (exitIfNoIp(ip_value)) {
            parsedIp.push_back(atoi(ip_value.c_str()));
            getNumber(ipAddr.substr(ip_value.size() + 1, ipAddr.size() - pos), parsedIp);
        }
    }
    else if (ipAddr.size() > 0) {
        if (exitIfNoIp(ipAddr)) {
            parsedIp.push_back(atoi(ipAddr.c_str()));
        }
    }
}

bool IpFilter::checkIpLen(std::string ipAddr, std::vector<int>& parsedIp) {
    if (std::count_if(ipAddr.begin(), ipAddr.end(), []( char c ){return c =='.';}) != 3) {
        return false;
    }
    getNumber(ipAddr, parsedIp);
    return true;
}

int IpFilter::compare(int ipFirst, int ipSecond) {
    // Condition if the IP Address is same then return 0
    uint8_t* ptrA = (uint8_t*)&ipFirst;
    uint8_t* ptrB = (uint8_t*)&ipSecond;
    if (ipFirst == ipSecond) {
        return 0;
    } else if ((int)ptrA[0] > (int)ptrB[0]) {
        return 1;
    } else if ((int)ptrA[0] < (int)ptrB[0]) {
        return -1;
    } else if ((int)ptrA[1] > (int)ptrB[1]) {
        return 1;
    } else if ((int)ptrA[1] < (int)ptrB[1]) {
        return -1;
    } else if ((int)ptrA[2] > (int)ptrB[2]) {
        return 1;
    } else if ((int)ptrA[2] < (int)ptrB[2]) {
        return -1;
    } else if ((int)ptrA[3] > (int)ptrB[3]) {
        return 1;
    } else if ((int)ptrA[3] < (int)ptrB[3]) {
        return -1;
    } else {
        return -1;
    }
}

void IpFilter::sortIp(std::vector<uint32_t>& sorteDescIps, uint32_t ipBin) {
    bool bInserted = false;
    for(size_t i = 0; sorteDescIps.size(); i++) {
        if (compare(ipBin, sorteDescIps[i]) == 1) {
            sorteDescIps.insert(sorteDescIps.begin() +i, ipBin);
            bInserted = true;
            break;
        }
    }
    if (bInserted) {
        return;
    }
    sorteDescIps.push_back(ipBin);
}
