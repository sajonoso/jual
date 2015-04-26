/*
        This script contains functions that verify common field in a form
        When a field is found to be incorrect, the background color is changed to red.  Otherwise color is set to white.
        pass to main function checkform form name.  Form should have input named EMAIL, PWD, VERIFY
*/

function substr_count(szHayStack, szNeedle) {
    var _c = 0;
    for (var i=0;i<szHayStack.length;i++) {
        if (szNeedle == szHayStack.substr(i,szNeedle.length)) _c++;
    }
    return _c;
}


function getFormByName(szName) {
    var i;
    for(i=0; i<document.forms.length; i++){
        if (document.forms[i].name == szName) return document.forms[i];
    };
}

function getElementsByName(myForm, szName) {
    var i;
    for(i=0; i<myForm.elements.length; i++){
        if (myForm.elements[i].name == szName) return myForm.elements[i];
    };
}

function IsValidPassword(szPassword) {
    iLength = szPassword.length;

    if ( (iLength < 6) || (iLength > 32) ) return false;

    return true;
}

/*
function IsValidUserID(szUserID) {
    var szValidChars = "abcdefghijklmnopqrstuvwxyz1234567890.-_";
    
    var szLowerUserID = szUserID.toLowerCase();
    
    var iLength = szLowerUserID.length;

    if ( (iLength > 32) || (iLength < 3)) return false;

    for (var i=0; i<iLength; i++) {
        if (szValidChars.indexOf(szLowerUserID.charAt(i)) == -1) return false;
    };

    return true;
}
*/

function getUrlVars() {
    var vars = {};
    var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function(m,key,value) {
        vars[key] = value;
    });
    return vars;
}

function IsValidEmailAddress(szEmail) {
    szValidCharsDomain = "abcdefghijklmnopqrstuvwxyz1234567890.-";
    szValidCharsUser = szValidCharsDomain + "@!#$%&'*+/=?^_`{|}~";

    szLowerEmail = szEmail.toLowerCase();

    iLength = szLowerEmail.length;

    if ( (iLength > 100) || (iLength < 4)) return false; // must be less than 101 characters

    if (substr_count(szLowerEmail, "@") != 1) return false; // only one @ symbol allowed
    if (substr_count(szLowerEmail, "..") > 0) return false; // can not have two consecutive dots
    if ( (szLowerEmail.charAt(0) == ".") || (szLowerEmail.charAt(0) == "-") ) return false; // can not start with dot or dash

    var blInUserPart = true;
    for (var i=0; i<iLength; i++) {
        if (blInUserPart) {
            if (szValidCharsUser.indexOf(szLowerEmail.charAt(i)) == -1) return false;
            if (szLowerEmail.charAt(i) == "@") blInUserPart = false;
        } else {
            if (szValidCharsDomain.indexOf(szLowerEmail.charAt(i)) == -1) return false;
        };
    };

    return true;
}


function TestCookies() {
    if (navigator.cookieEnabled == false) document.write('Cookies must be enabled for this web site to function');
}


function checkform(szFormName) {
    var pageerrors = 0;
    var myForm = getFormByName(szFormName);

    if (getElementsByName(myForm, "EMAIL") != null) {
        if (IsValidEmailAddress(myForm.EMAIL.value)) {
            myForm.EMAIL.style.background = "#FFFFFF";
        } else {
            myForm.EMAIL.style.background = "#FF0000";
            pageerrors++;
        };
    };

    if (getElementsByName(myForm, "PWD") != null) {
        if ( (myForm.PWD.value != "") &&
             IsValidPassword(myForm.PWD.value) &&
              (myForm.PWD.value == myForm.VERIFY.value) ) {
            myForm.PWD.style.background = "#FFFFFF";
        } else {
            myForm.PWD.style.background = "#FF0000";
            pageerrors++;
        };
    };

    if (pageerrors != 0) alert("Incorrect input hightlighted in red");

    return (pageerrors == 0);
}

function FieldClear(obj) {
    obj.style.background = "#FFFFFF";
}

function FieldError(obj) {
    obj.style.background = "#FF0000";
};

function VerifyForm() {
    var blFormIsGood = true;
    var txtName = document.getElementById("txtName");
    var txtEmail = document.getElementById("txtEmail");
    var txtSubject = document.getElementById("txtSubject");
    var txtMessage = document.getElementById("txtMessage");
    
    if (txtName.value.length < 1) {
        txtName.value = "Must be more than 1 letter";
        FieldError(txtName);
    } else {
        FieldClear(txtName);
    };

    if (txtSubject.value.length < 5) {
        txtSubject.value = "Must be more than 5 letters";
        FieldError(txtSubject);
        blFormIsGood = false;
    } else {
        FieldClear(txtSubject);
    };

    if (txtMessage.value.length < 10) {
        txtMessage.value = "Must be more than 10 letters";
        FieldError(txtMessage);
        blFormIsGood = false;
    } else {
        FieldClear(txtMessage);
    };
    
    if (!IsValidEmailAddress(txtEmail.value)) {
        FieldError(txtEmail);
        blFormIsGood = false;
    } else {
        FieldClear(txtEmail);
    };

    return blFormIsGood;
}

