#include "test_hkl.h"

TEST_F(HKLSockTest, DefaultConstructorInitializesSocketFd) {
    HKLSock::TSocketFd fd;
    sock.GetHandle(fd);
    EXPECT_EQ(fd, -1); // SOCKET_ERROR
}

TEST_F(HKLSockTest, AssignmentOperatorCopiesSocketFd) {
    HKLSock sock2(5);
    sock = sock2;

    HKLSock::TSocketFd fd;
    sock.GetHandle(fd);
    EXPECT_EQ(fd, 5);
}

TEST_F(HKLSockTest, CloseSetsSocketFdToError) {
    HKLSock sock2(5);
    sock2.Close();

    HKLSock::TSocketFd fd;
    sock2.GetHandle(fd);
    EXPECT_EQ(fd, -1); // SOCKET_ERROR
}