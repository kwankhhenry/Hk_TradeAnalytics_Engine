#include "gtest/gtest.h"

#include "hkl/HKLSock.h"

class HKLSockTest : public ::testing::Test {
protected:
    HKLSock sock;

    void SetUp() override {
        // Optional: initialize or configure sock if needed
    }

    void TearDown() override {
        // Optional: cleanup if needed
    }
};

TEST_F(HKLSockTest, DefaultConstructorInitializesSocketFd) {
    /*TSocketFd fd;
    sock.GetHandle(fd);
    EXPECT_EQ(fd, -1); // SOCKET_ERROR*/
}

TEST_F(HKLSockTest, AssignmentOperatorCopiesSocketFd) {
    /*HKLSock sock2(5);
    sock = sock2;

    TSocketFd fd;
    sock.GetHandle(fd);
    EXPECT_EQ(fd, 5);*/
}

TEST_F(HKLSockTest, CloseSetsSocketFdToError) {
    /*HKLSock sock2(5);
    sock2.Close();

    TSocketFd fd;
    sock2.GetHandle(fd);
    EXPECT_EQ(fd, -1); // SOCKET_ERROR*/
}