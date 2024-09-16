#include <iostream>
#include "TCPListener.h"

using namespace std;

int main()
{
	HK::TCPListener myTCPListener("0.0.0.0", 5000);
	myTCPListener.init();
	myTCPListener.run();
	return 0;
}