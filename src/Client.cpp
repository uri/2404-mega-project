//
//  Client.cpp
//  Multiplayer
//
//  Created by ugorelik on 11-03-26.
//  Copyright 2011 Carleton University. All rights reserved.
//

#include "Client.h"


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

//void error(const char *msg);

/*
int main(int argc, char *argv[])
{
    Client client(argv[1], argv[2]);
    client.Run();
    client.Stop();
}
 */

Client::Client()
{
    cout << "Enter a port number, EX: 60001" << endl;
    
    char temp[30];
    scanf("%s", temp);
    
    portNumber = atoi(temp);
    cout << "Enter the host name, EX: lambda04" << endl;
    scanf("%s", hostName);
    printf("\n This is the host name %s, this is the portnumber: %d", hostName, portNumber);
    
    
    InitSocket();
    InitSocketAddress();
    Connect();
}

bool Client::InitSocket()
{
    int r = 0;
    // Create a socket for sending data
    r = sock_send = socket(AF_INET, SOCK_STREAM, 0);
    if (r < 0 ) return false;
    
    return server = gethostbyname(hostName);
}

void Client::InitSocketAddress()
{
    // Create the socket address structure to connect to
    memset(&addr_send,0, sizeof (addr_send));   // Zero the structure
    addr_send.sin_family = AF_INET;
    
    
    
    //    addr_send.sin_addr.s_addr = inet_addr(SERVER_IP);
    // Set the internet address
    bcopy((char *)server->h_addr, 
          (char *)&addr_send.sin_addr.s_addr,
          server->h_length);
    
    addr_send.sin_port = htons((unsigned short) portNumber);
    
}

bool Client::Connect()
{
    int r = -1;
	while(r < 0){
		r = connect (sock_send, (struct sockaddr *) &addr_send, sizeof (addr_send));
		//usleep(500);
	}
    
    return r < 0;
}


void Client::Stop()
{
    // Close
	close(sock_send);
}

void Client::GotMessage() 
{
    write(sock_send,"\0",BUF_SIZE); // Tell the Player to stop Listening
}

char * Client::ReadMessage()
{
    int n = -1;
    
    bzero(buf,BUF_SIZE);
	while (n<0){
		n = recv(sock_send, buf, BUF_SIZE, 0);
	}

    return buf;
}

void Client::SendMessage(const char * hitMiss) 
{
    int n = -1;
    bzero(buf, BUF_SIZE);
    strcpy(buf,hitMiss);
	while (n < 0){
	 n = write(sock_send,buf,BUF_SIZE);
	}
        
        
    
}




