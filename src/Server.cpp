
#include "Server.h"

#include <iostream>
#include <sstream>
#include "NetworkUtility.h"

using namespace std;

//void error(const char *msg)

Server::Server()
{
    cout << "Enter a port number, EX 60001" << endl;
    scanf("%d", &portNumber);
    
    if (CreateListeningSocket()) {
        printf("server could not open listen socket\n");
        exit(-1);
    }
    
    fcntl(sock_listen, F_SETFL, O_NDELAY); // Might need to check after error check
   
    InitAddress();
	Listen();
    CreateReceivingSocket();
}


bool Server::CreateListeningSocket()
{
    // Create a socket for listening
	sock_listen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    return sock_listen < 0;
}

bool Server::InitAddress()
{
    int r = 0;
    // Make local address structure
	memset(&my_addr, 0, sizeof (my_addr));		// Zero the structure
    my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons((unsigned short) portNumber);
	
	// Bind the socket to the local address
	r = bind(sock_listen, (struct sockaddr *) &my_addr, sizeof (my_addr));
	
    return r < 0;
}

bool Server::Listen()
{
    int r = 0;
    
    // TIME TO LISTEN!
	r = listen(sock_listen, 5);	// Up to 5 connections
	return r < 0;
}

void Server::CreateReceivingSocket()
{
    // Get new socket to recieve on
	addr_size = sizeof(recv_addr);
    socklen_t address_size = sizeof (recv_addr);

    
    sock_recv = -1;
    while (sock_recv == -1) {
        sock_recv = accept(sock_listen, (struct sockaddr *) &recv_addr, &address_size);
       // usleep(500);
    }
    
}

void Server::UpdateObservers(Player * player, Player * enemy){
	// Loop through the spectators
    std::vector<int>::iterator itr;
	stringstream stream;
    for (itr = allSocketsList.begin(); itr != allSocketsList.end(); ++itr) {
		stream.str("");
		stream << NetworkUtility::convertToStringObserver(player->getHits(),player->getMisses());
		write(*itr,stream.str().c_str(),BUF_SIZE);
		stream.str("");
		stream << NetworkUtility::convertToStringObserver(enemy->getHits(), enemy->getMisses());
		write(*itr,stream.str().c_str(),BUF_SIZE);
        
    }
}

int Server::AddObserver(Player * player, Player * enemy) {
    struct sockaddr_in aNewObserverAddr;
    int observerSocket = - 1;
    
    addr_size = sizeof(aNewObserverAddr);
    socklen_t address_size = sizeof (aNewObserverAddr);
	
    
    observerSocket = accept(sock_listen, (struct sockaddr *) &aNewObserverAddr, &address_size);
    
    if (observerSocket != -1 ) {
        allSocketsList.push_back(observerSocket);
        allSocketsAddress.push_back(aNewObserverAddr);
		stringstream stream;
		stream << NetworkUtility::convertToStringObserver(player->getHits(),player->getMisses());
		write(observerSocket,stream.str().c_str(),BUF_SIZE);
		stream.str("");
		stream << NetworkUtility::convertToStringObserver(enemy->getHits(), enemy->getMisses());
		write(observerSocket,stream.str().c_str(),BUF_SIZE);
    }
    
    
    return observerSocket;
}

void Server::EndTransmission() 
{
    write(sock_recv,"\0",BUF_SIZE); // Tell the Player to stop Listening
}

char * Server::ReadMessage()
{
	int n = -1;
	bzero(buf,BUF_SIZE);
	while (n < 0){
		 n = recv(sock_recv, buf, BUF_SIZE, 0);
	 }
    return buf;
}

void Server::SendMessage(const char * hitMiss) 
{
    int n = -1;
    bzero(buf, BUF_SIZE);
    strcpy(buf,hitMiss);
	while (n < 0){
	 n = write(sock_recv,buf,BUF_SIZE);
	}
}


void Server::Stop()
{
    close(sock_recv);
	close(sock_listen);
}


