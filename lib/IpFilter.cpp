#include "IpFilter.h"

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
            std::cout << ip_value << ".";
            parsedIp.push_back(atoi(ip_value.c_str()));
            getNumber(ipAddr.substr(ip_value.size() + 1, ipAddr.size() - pos), parsedIp);
        }
    }
    else if (ipAddr.size() > 0) {
        auto lastpos = ipAddr.find("\t");
        if (lastpos != std::string::npos) {
            std::string ip_value = ipAddr.substr(0, lastpos);
            if(exitIfNoIp(ip_value)) {
            std::cout << ip_value << ";" << std::endl;
            parsedIp.push_back(atoi(ip_value.c_str()));
            }
        }
    }
}

bool IpFilter::checkIpLen(std::string ipAddr) {
    std::vector<int> parsedIp;
    if (std::count_if(ipAddr.begin(), ipAddr.end(), []( char c ){return c =='.';}) != 3 || ipAddr[ipAddr.size() - 1] == '.') {
        return false;
    }
    getNumber(ipAddr, parsedIp);
    if (parsedIp.size() != 4) {
        return false;
    }

    uint8_t ipbytes[4] = {(uint8_t)parsedIp[0],(uint8_t)parsedIp[1],(uint8_t)parsedIp[2],(uint8_t)parsedIp[3]};
    uint32_t ipBin = ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
    std::cout << "***BEFORE ip: " << ipAddr << std::endl;
    sortIp(ipBin);
    return true;
}

int IpFilter::compare(int ipFirst, int ipSecond) {
    // Condition if the IP Address is same then return 0
    uint8_t* ptrA = (uint8_t*)&ipFirst;
    uint8_t* ptrB = (uint8_t*)&ipSecond;

    /*std::cout << "### ptrA " << ptrA << " ip is " << (int)ptrA[0]<< "." << (int)ptrA[1] << "." << (int)ptrA[2] << "." << (int)ptrA[3] << std::endl;
    std::cout << "### ptrB " << ptrB << " ip is "  << (int)ptrB[0]<< "." << (int)ptrB[1] << "." << (int)ptrB[2] << "." << (int)ptrB[3] << std::endl;


    if (ptrA == nullptr) {
        std::cout << "***ptrA" << std::endl;
        return -1;
    }
    if (ptrB == nullptr) {
        std::cout << "***ptrB" << std::endl;
        return -1;
    }*/



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

void IpFilter::sortIp(uint32_t ipBin) {
    bool bInserted = false;
    for(int i = 0; i < orderedIps.size(); ++i) {
        if (compare(ipBin, orderedIps[i]) == 1) {
           // uint8_t* ipBins = (uint8_t*)&ipBin;

            //std::cout << "try push " << ipBins[0] << "." << ipBins[1] << "." << ipBins[2] << "." << ipBins[3] << std::endl;


            orderedIps.insert(orderedIps.begin() +i, ipBin);
            bInserted = true;
            break;
        }
    }
    if (bInserted) {
        return;
    }
    orderedIps.push_back(ipBin);
}
