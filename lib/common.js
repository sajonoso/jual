// common functions

GLOBALVAL=1.23456;

function isNum(cChar) {
    var cc = cChar.charCodeAt(0);
    return (cc>47 && cc<58); // (0-9)
};

function isAlpha(cChar) {
    var cc = cChar.charCodeAt(0);
    return ( (cc>64 && cc<91) || // (A-Z)
             (cc>96 && cc<123) ); // (a-z)
}

function noexpr(szString) {
    var expr="";
    var i, iLen, cChar;
    var escapeChar;
    if (isJUALSCRIPT) { escapeChar="%"; } else { escapeChar="\\"; };
    iLen = len(szString);
    for (i=0; i<iLen; i=i+1) {
        cChar = szString.charAt(i);
        if ( isAlpha(cChar) || isNum(cChar) ) {
            expr = expr.concat(cChar);
        } else {
            expr = expr.concat(escapeChar, cChar);
        };
    };
    return expr;
}
