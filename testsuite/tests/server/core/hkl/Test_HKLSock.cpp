#include "hkl/Test_HKLSock.h"

TEST_F(HKLSockTest, DefaultConstructorInitializesSocketFd) {
    HKLSock::TSocketFd fd;
    sock.GetHandle(fd);
    EXPECT_EQ(fd, -1); // SOCKET_ERROR
}

TEST_F(HKLSockTest, ConstructorWithFdSetsFd) {
    HKLSock sock2(10);
    HKLSock::TSocketFd fd;
    sock2.GetHandle(fd);
    EXPECT_EQ(fd, 10);
}

TEST_F(HKLSockTest, MoveConstructorTransfersFd) {
    HKLSock sock2(20);
    HKLSock sock3(std::move(sock2));
    HKLSock::TSocketFd fd2, fd3;
    sock2.GetHandle(fd2);
    sock3.GetHandle(fd3);
    EXPECT_EQ(fd2, -1); // SOCKET_ERROR
    EXPECT_EQ(fd3, 20);
}

TEST_F(HKLSockTest, AssignmentOperatorMoveSocketFd) {
    sock.SetHandle(2);
    sock = HKLSock(5);

    HKLSock::TSocketFd fd;
    sock.GetHandle(fd);
    EXPECT_EQ(fd, 5);
}

TEST_F(HKLSockTest, MoveAssignmentTransfersFd) {
    HKLSock sock2(30);
    HKLSock sock3;
    sock3 = std::move(sock2);
    HKLSock::TSocketFd fd2, fd3;
    sock2.GetHandle(fd2);
    sock3.GetHandle(fd3);
    EXPECT_EQ(fd2, -1); // SOCKET_ERROR
    EXPECT_EQ(fd3, 30);
}

TEST_F(HKLSockTest, DestructorClosesSocket) {
    HKLSock::TSocketFd fd = socket(AF_INET, SOCK_STREAM, 0);
    {
        HKLSock sock2(fd);
    }
    int closeResult = close(fd);
    EXPECT_EQ(closeResult, -1);
}

TEST_F(HKLSockTest, SetHandleClosesPreviousFd) {
    HKLSock sock2(40);

    HKLSock::TSocketFd oldFd;
    sock2.GetHandle(oldFd);

    sock2.SetHandle(50);    // Closing Old Fd=40
    int closeResult = close(oldFd);     // Attempt to close old Fd=40 again
    EXPECT_EQ(closeResult, -1);     // Should fail due to socket of Fd already closed
    
    HKLSock::TSocketFd fd;
    sock2.GetHandle(fd);
    EXPECT_NE(fd, -1);      // Expect not equal to -1
    sock2.Close();
}

TEST_F(HKLSockTest, GetHandleReturnsCurrentFd) {
    HKLSock sock2(60);
    HKLSock::TSocketFd fd;
    sock2.GetHandle(fd);
    EXPECT_EQ(fd, 60);
}

TEST_F(HKLSockTest, BindWithInvalidAddressReturnsFalse) {
    IString invalidAddr("999.999.999.999");
    bool result = sock.Bind(8080, invalidAddr);
    EXPECT_FALSE(result);
}

TEST_F(HKLSockTest, BindWithEmptyAddressBindsToAny) {
    HKLSock sock2;
    sock2.SetHandle(socket(AF_INET, SOCK_STREAM, 0));
    IString EmptyAddr("");
    bool result = sock2.Bind(0, EmptyAddr);
    EXPECT_TRUE(result);
    sock2.Close();
}

TEST_F(HKLSockTest, BindWithSockAddrWorks) {
    HKLSock sock2;
    sock2.SetHandle(socket(AF_INET, SOCK_STREAM, 0));
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    bool result = sock2.Bind((struct sockaddr*)&addr, sizeof(addr));
    EXPECT_TRUE(result);
    sock2.Close();
}

TEST_F(HKLSockTest, CloseSetsSocketFdToError) {
    HKLSock sock2(5);
    sock2.Close();

    HKLSock::TSocketFd fd;
    sock2.GetHandle(fd);
    EXPECT_EQ(fd, -1); // SOCKET_ERROR
}

TEST_F(HKLSockTest, CreateBindsSuccessfully) {
    HKLSock sock2;
    uint16_t port = GetFreePort();
    IString addr("127.0.0.1");
    bool result = sock2.Create(port, SOCK_STREAM, addr);
    EXPECT_TRUE(result);
    sock2.Close();
}

TEST_F(HKLSockTest, CreateFailsIfAlreadyCreated) {
    HKLSock sock2;
    uint16_t port = GetFreePort();
    IString addr("127.0.0.1");
    bool result1 = sock2.Create(port, SOCK_STREAM, addr);
    EXPECT_TRUE(result1);
    bool result2 = sock2.Create(port, SOCK_STREAM, addr);
    EXPECT_FALSE(result2);
    sock2.Close();
}

TEST_F(HKLSockTest, ListenAcceptConnectWorks) {
    uint16_t port = GetFreePort();
    IString addr("127.0.0.1");
    HKLSock server;
    EXPECT_TRUE(server.Create(port, SOCK_STREAM, addr));
    EXPECT_TRUE(server.Listen(1));

    // Start client in another thread
    std::thread clientThread([port, addr]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        HKLSock client;
        client.SetHandle(socket(AF_INET, SOCK_STREAM, 0));
        EXPECT_TRUE(client.Connect(addr, port));
        client.Close();
    });

    HKLSock peer;
    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    EXPECT_TRUE(server.Accept(peer, (struct sockaddr*)&clientAddr, &clientAddrLen));
    peer.Close();
    server.Close();
    clientThread.join();
}