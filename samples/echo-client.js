require_n("libinet");

var tc = TCPClient("localhost", 1122, 5000);

if (tc != null) {

    var szLine = TCPReadLine(tc);
    if (szLine != null) { print(szLine); }

    TCPWrite(tc, "GET /test.txt\r\n");
    szLine = TCPReadLine(tc);
    if (szLine != null) { print(szLine); }
    
    TCPWrite(tc, "POST /serverhandler\r\n");
    szLine = TCPReadLine(tc);
    if (szLine != null) { print(szLine); }
    
    TCPWrite(tc, "quit\r\n");

    TCPClose(tc);
};
