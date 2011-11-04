//
//  Observer.h
//  Multiplayer
//
//  Created by ugorelik on 11-04-03. (down to the wire!)
//  Copyright 2011 Carleton University. All rights reserved.
//

#ifndef OBSERVER_H
#define OBSERVER_H

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

class Observer
{
    
public:
    Observer();
    
    bool InitSocket();
    void InitSocketAddress();
    bool Connect();
    char * ReadMessage();
    void Run();
    void Stop();
    
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