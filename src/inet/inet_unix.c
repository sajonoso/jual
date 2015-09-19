/*
    Copyright (C) 2015 Sajon Oso 
    Jual Native C module - Internet Protocol Suite
    Currently only implements IPv4 socket functions
    Unix specific functions
*/

#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>

#define IP4STR_SIZE 16
#define SOCKET_LINECACHE_MAX 256
#define MAX_CONNECTIONS 128

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


typedef struct tcp_socket_ {
    int ip[4];
    int port;
    int cacheUsed;
    int cacheStart;
    char cacheLine[SOCKET_LINECACHE_MAX];
    // OS_specific struct goes here
    int sock;
} tcp_socket;


IP4INT ResolveHostIP(const char *hostAddress) {
    struct addrinfo hints;
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;

    memset( &hints, 0, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    int iResult = getaddrinfo(hostAddress, "80", &hints, &result);
    if ( iResult != 0 ) {
        return 0;
    };

    struct sockaddr_in *sin;
    IP4INT IP4Result;
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
        if (ptr->ai_family == AF_INET) {
            sin = (struct sockaddr_in *)ptr->ai_addr;
            IP4Result = sin->sin_addr.s_addr;
            freeaddrinfo(result); 
            return IP4Result;
        };
    };

    freeaddrinfo(result);
    return 0;
}


tcp_socket *TCPClient(tcp_socket *ts, const char *address, int port, int timeout) {

    IP4INT testIP;
    testIP = isIPString(address);
    if (testIP == 0) {
        testIP = ResolveHostIP(address);
        if (testIP == 0) return NULL;
    };

    ts->sock = socket( AF_INET, SOCK_STREAM, 0 );
    
    if (ts->sock < 0) return NULL;

    ip4toarray(ts->ip, testIP);
    ts->cacheUsed = 0;
    ts->cacheStart = 0;

    struct sockaddr_in sin;
    memset( &sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = testIP;
    sin.sin_port = htons( port );

    if (connect(ts->sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        close (ts->sock);
        return NULL;
    };

    return ts;
}


tcp_socket *TCPServer(tcp_socket *ts, const char *address, int port, int timeout, void *onConnection) {
    IP4INT testIP;

    // Assuming address is at least one terminated character
    // check for special case of listening to any address
    if (address[0] == '*' && address[1] == '\0') {
        testIP = INADDR_ANY;
    } else {
    
        testIP = isIPString(address);
        if (testIP == 0) {
            testIP = ResolveHostIP(address);
            if (testIP == 0) return NULL;
        };
    };

    ts->sock = socket( AF_INET, SOCK_STREAM, 0 );

    if (ts->sock < 0) return NULL;

    ip4toarray(ts->ip, testIP);
    ts->cacheUsed = 0;
    ts->cacheStart = 0;    

    struct sockaddr_in sin;
    memset( &sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = testIP;
    sin.sin_port = htons( port );

    if (bind(ts->sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        // could not bind - port may be in use
        return NULL;
    };

    // parm2 default SOMAXCONN
    if (listen(ts->sock, MAX_CONNECTIONS) < 0) {
        // could not listen - port may be in use
        return NULL;
    };

    return ts;
}


tcp_socket *TCPAccept(tcp_socket *ts, tcp_socket *tc) {
    // this call is blocking ...
    struct sockaddr_in client_info;
    int size = sizeof(client_info);

    int ClientSocket = accept(ts->sock, (struct sockaddr *)&client_info, &size);

    if (ClientSocket < 0) {
        close(ts->sock);
        return NULL;
    }

    tc->sock = ClientSocket;
    ip4toarray(tc->ip, client_info.sin_addr.s_addr);
    tc->cacheUsed = 0;
    tc->cacheStart = 0;      

    return tc;
}


int TCPWrite(tcp_socket *ts, const char *buffer, int bufferSize) {
    int iResult = send( ts->sock, buffer, bufferSize, 0 );
    if (iResult != bufferSize) {
        // printf("send failed: %d\n", WSAGetLastError());
        close( ts->sock );
        return FALSE;
    }

    return TRUE;
}


// result < 0 = error
// result = 0 = socket closed
// result > 0 = number of bytes read
int TCPRead(tcp_socket *ts, char *buffer, int bufferSize) {
    int iResult = recv( ts->sock, buffer, bufferSize, 0);
    return iResult;
}

// return number of characters in line. zero is a valid response i.e empty line
// errors return negative results
int TCPReadLine(tcp_socket *ts, char *buffer, int bufferSize) {
    char *cache = ts->cacheLine;
    int iRead = 0;

    if (bufferSize > 0) buffer[0] = '\0';

    // if cache is free read more data
    if (ts->cacheUsed == 0) {
        ts->cacheStart = 0;
        iRead = TCPRead(ts, cache, SOCKET_LINECACHE_MAX-1);
        if (iRead < 0) return iRead;
        if (iRead == 0) return -1;

        ts->cacheUsed = iRead;
    };

    // Copy cache to output buffer filling cache again if required.
    int i, k;
    k = ts->cacheStart;
    for (i=0; i<bufferSize-1; i++) {
        if (cache[k] == '\n') {
            ts->cacheUsed--;
            if (ts->cacheUsed == 0) {
                ts->cacheStart = 0;
            } else {
                ts->cacheStart = k+1;
            };
            buffer[i] = '\0';
            return i;
        } else {
            buffer[i] = cache[k];
            if (cache[k] == '\r') i--;
            ts->cacheUsed--;
            k++;
            if (ts->cacheUsed == 0) {
                ts->cacheStart = 0;
                k=0;
                iRead = TCPRead(ts, cache, SOCKET_LINECACHE_MAX-1);
                if (iRead <= 0) {
                    buffer[i+1] = '\0';
                    if (iRead < 0) return iRead;
                    if (iRead == 0) return i;
                };
                ts->cacheUsed = iRead; 
            };
        };
    };
    ts->cacheStart = k;

    // reached buffer size - terminate string and return content so far
    buffer[bufferSize-1] = '\0';
    return bufferSize-1;
}

void TCPClose(tcp_socket *ts) {
    close( ts->sock );
}
