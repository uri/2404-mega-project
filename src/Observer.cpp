//  Observer.cpp
//  Multiplayer
//
//  Created by Mike on 11-03-26.
//
//  Copyright 2011 Carleton University. All rights reserved.
//

#include "Observer.h"

#include "GameHost.h"
#include "Board.h"
#include "Player.h"
#include "Random.h"
#include "Renderer.h"
#include "ShipTypes.h"
#include "Statistics.h"
#include "Server.h"
#include <string>
#include "NetworkUtility.h"

#include <limits>
#include <iostream>
#include <stdio.h>




Observer::Observer()
{
    cout << "Enter a port number, EX: 60001" << endl;
    
    char temp[30];
    scanf("%s", temp);
    
    portNumber = atoi(temp);
    cout << "Enter the host name, EX: lambda04" << endl;
    scanf("%s", hostName);
    printf("\n This is the host name %s, this is the portnumber: %d\n", hostName, portNumber);
    
    
    InitSocket();
    InitSocketAddress();
    Connect();
}

bool Observer::InitSocket()
{
    int r = 0;
    // Create a socket for sending data
    r = sock_send = socket(AF_INET, SOCK_STREAM, 0);
    if (r < 0 ) return false;
    
    return server = gethostbyname(hostName);
}

void Observer::InitSocketAddress()
{
    // Create the socket address structure to connect to
    memset(&addr_send,0, sizeof (addr_send));   // Zero the structure
    addr_send.sin_family = AF_INET;
    
    // Set the internet address
    bcopy((char *)server->h_addr, 
          (char *)&addr_send.sin_addr.s_addr,
          server->h_length);
    
    addr_send.sin_port = htons((unsigned short) portNumber);
    
}

bool Observer::Connect()
{
    int r = 0;
    r = connect (sock_send, (struct sockaddr *) &addr_send, sizeof (addr_send));
    return r < 0;
}

char * Observer::ReadMessage()
{
    int n = -1;
    
    bzero(buf,BUF_SIZE);
	while (n<0){
		n = recv(sock_send, buf, BUF_SIZE, 0);
	}
    
    return buf;
}
/*
void Observer::Run()
{
    while (1) {
        
        int n;
        
        n = recv(sock_send,buf,BUF_SIZE,0);
        if (n < 0) 
            error("ERROR reading from socket");
        
        
        printf("%s\n",buf);
        bzero(buf,BUF_SIZE);
        
    }
}*/

void Observer::Stop()
{
    // Close
	close(sock_send);
}







