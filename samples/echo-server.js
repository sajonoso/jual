require_n("libinet");

var ts = TCPServer("localhost", 1122, 5000);
if (ts == null) { os.exit() };

var szOutput;
var blServerRunning = true;
while (blServerRunning) {
    print( "Listening on localhost port 81 for connections" );
    var tc = TCPAccept(ts);

    print( "Connection established" );
    if (tc != null) {
        TCPWrite(tc, "Welcome to the echo server! \r\n");
        while (true) {
            var szLine = TCPReadLine(tc);
            if (szLine != null) {
                if (szLine == "close") {
                    break;
                } else if (szLine == "quit") {
                    blServerRunning = false;
                    break;
                } else {
                    szOutput = "" + szLine + "\r\n";
                    TCPWrite(tc, szOutput);
                    print("Client wrote " + szLine.size() + "bytes(s) " + szOutput);
                };
            };
        };
        
        print( "Connection closed." );

        TCPClose(tc);
    };
};

TCPClose(ts);
