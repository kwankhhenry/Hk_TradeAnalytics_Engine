#pragma once

#ifndef TEST_HKLSOCK_H
#define TEST_HKLSOCK_H

#include "gtest/gtest.h"
#include "resource/testbase.h"

#include "hkl/HKLSock.h"

#include <thread>
#include <chrono>

class HKLSockTest : public TestBase {
protected:
    HKLSock sock;

    void SetUp() override {
        // Optional: initialize or configure sock if needed
    }

    void TearDown() override {
        // Optional: cleanup if needed
    }
};

// Helper function to get a free port
static uint16_t GetFreePort() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = 0; // Let OS pick
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    socklen_t len = sizeof(addr);
    getsockname(sock, (struct sockaddr*)&addr, &len);
    uint16_t port = ntohs(addr.sin_port);
    close(sock);
    return port;
}

#endif // TEST_HKLSOCK_H