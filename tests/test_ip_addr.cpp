#include <gtest/gtest.h>
#include <iostream>
#include "../lib/IpFilter.h"

class TestIpFilter : public IpFilter {
public:

    bool test_checkIpLen(const std::string& ip) {
        std::vector<int> testIps;
        return checkIpLen(ip, testIps);
    }

    size_t test_getNumber(const std::string& ip) {
        std::vector<int> testIps;
        getNumber(ip, testIps);
        return testIps.size();
    }
};

TEST(TEST_VER, Test_CheckIpLen) {
    TestIpFilter testIpFilter;
    std::vector<int> parsedIp;

    EXPECT_EQ(testIpFilter.test_checkIpLen("192.168.10.22"), true);
    EXPECT_EQ(testIpFilter.test_checkIpLen("wrote kompot"), false);
}

TEST(TEST_VER, Test_GetNumber) {
    TestIpFilter testIpFilter;
    std::vector<int> parsedIp;

    EXPECT_EQ(testIpFilter.test_getNumber("192.168.10.22"), 4);
    EXPECT_EQ(testIpFilter.test_getNumber("wrote kompot"), 0);
}

