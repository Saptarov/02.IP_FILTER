#ifndef IPFILTER_H
#define IPFILTER_H
#include "common.h"
#define START_INDEX 1

class IpFilter
{
public:
    /**
     * Parsed arguments from stdin.
     *
     * @param argc Length of arguments.
     * @param argv Pointer to arguments.
     */
    void parseArguments(int argc, char** argv);

    /**
     * Return sorted container.
     *
     * @return Reference to sorted container.
     */
    const std::vector<uint32_t>& getSortedIps();

    /**
     * Check ip address dots :).
     *
     * @param ipAddr String from stream.
     * @return false if ipAddr is not contained 3 dots.
     */
    bool checkIpLen(std::string ipAddr);
protected:

    /**
     * Return true if string is a number.
     *
     * @param availNumber Contain available number.
     * @return true if contained a number.
     */
    bool isNumber(const std::string& availNumber);

    /**
     * Validate Ip address.
     *
     * @param ip_value Contain available Ip address octet (byte).
     * @return true if number is contained.
     */
    bool exitIfNoIp(const std::string& ip_value);

    /**
     * Validate and pushed ip address octets to container.
     *
     * @param ipAddr String from stream.
     * @param parsedIp Container of ip address octets.
     */
    void getNumber(std::string ipAddr, std::vector<int>& parsedIp);

    /**
     * Compared octets of two ip address.
     *
     * @param ipFirst Ip Address.
     * @param ipSecond Ip Address.
     * @return 0 if equal, 1 if first greater, -1 if first lowwer.
     */
    int  compare(int ipFirst, int ipSecond);

    /**
     * Lexicographical sorting in result container.
     *
     * @param sorteDescIps Container of results.
     * @param ipBin Ip in binary format.
     */
    void sortIp(uint32_t ipBin);

protected:
    std::vector<uint32_t> orderedIps;
};

#endif // IPFILTER_H
