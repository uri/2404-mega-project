//
//  Client.h
//  Multiplayer
//
//  Created by ugorelik on 11-03-26.
//  Copyright 2011 Carleton University. All rights reserved.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 

#define BUF_SIZE            1024
#define SERVER_IP           "134.117.27.122"
#define SERVER_PORT         60000

class Client
{
    
public:
    
    Client();
    
    bool InitSocket();
    void InitSocketAddress();
    bool Connect();
    void Stop();
    
    void SendMessage(const char *);
    char * ReadMessage();
    void GotMessage();
    
    int portNumber;
    char hostName[100];
private:
    int                 sock_send;
    struct sockaddr_in  addr_send;
    char                text[80];
    char                buf[BUF_SIZE];
    int                 send_len;
    int                 bytes_sent;
    
    struct              hostent *server;
};

#endif