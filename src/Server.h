//
//  Server.h
//  Multiplayer
//
//  Created by ugorelik on 11-03-26.
//  Copyright 2011 Carleton University. All rights reserved.
//

#ifndef SERVER_H
#define SERVER_H

#include "Player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netinet/in.h>


#include <unistd.h>
#include <arpa/inet.h>

#include <vector>
#include <string>

#define BUF_SIZE 1024
#define LISTEN_PORT 60000

using std::vector;
using std::string;

class Server 
{
    
public:
    
    Server();
    
    bool CreateListeningSocket();   // Create the listening Socket
    bool InitAddress();             // Initialize
    bool Listen();
    void CreateReceivingSocket();
    int AddObserver(Player *, Player *);
	void UpdateObservers(Player *, Player *);
    
    void SendMessage(const char *);
    char * ReadMessage();
    void EndTransmission();
    
    void Stop();
    
    // Variables
    int                     portNumber;
    
private:
    
    int 					sock_listen, sock_recv;
	struct sockaddr_in  	my_addr, recv_addr; 
	int 					addr_size, bytes_received; 
	char 					buf[BUF_SIZE];
    vector<int>                 allSocketsList;
    vector<struct sockaddr_in>  allSocketsAddress;

    
};

#endif