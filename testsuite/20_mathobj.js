// Testing maths functions

var szOut;

function RoundTo(iDecimalPlaces, fNumber) {
  if (iDecimalPlaces > 0) {
    var mult = Math.pow(10, iDecimalPlaces);
    var value = Math.floor((fNumber*mult)+0.5) / mult;
    if (value%1==0) { // if integer result set to integer
        return value|0;
    } else {
        return value;
    };
  };

  return Math.floor(fNumber+0.5)|0;
};

var iDec = 12;

szOut = "";
szOut = (szOut + "\nMath.abs:   " + RoundTo(iDec, Math.abs(-135)) );
szOut = (szOut + "\nMath.acos:  " + RoundTo(iDec, Math.acos(0.235)) );
szOut = (szOut + "\nMath.asin:  " + RoundTo(iDec, Math.asin(0.34)) );
szOut = (szOut + "\nMath.atan:  " + RoundTo(iDec, Math.atan(0.34)) );
szOut = (szOut + "\nMath.atan2: " + RoundTo(iDec, Math.atan2(2, 1.5)) );
szOut = (szOut + "\nMath.ceil:  " + RoundTo(iDec, Math.ceil(0.34)) );
szOut = (szOut + "\nMath.cos:   " + RoundTo(iDec, Math.cos(0.34)) );
szOut = (szOut + "\nMath.exp:   " + RoundTo(iDec, Math.exp(0.34)) );
szOut = (szOut + "\nMath.floor: " + RoundTo(iDec, Math.floor(356.34)) );
szOut = (szOut + "\nMath.log:   " + RoundTo(iDec, Math.log(10)) );
szOut = (szOut + "\nMath.max:   " + RoundTo(iDec, Math.max(456,456,757,564,234)) );
szOut = (szOut + "\nMath.min:   " + RoundTo(iDec, Math.min(456,456,757,564,234)) );
szOut = (szOut + "\nMath.pow:   " + RoundTo(iDec, Math.pow(2,8)) );

// Testing the random function will cause the test to fail.
// szOut = szOut + "\nMath.random:" + RoundTo(iDec, Math.random() );

szOut = szOut + "\nMath.round: " + Math.round(2.60);
szOut = szOut + "\nMath.round: " + Math.round(2.50);
szOut = szOut + "\nMath.round: " + Math.round(2.49);
szOut = szOut + "\nMath.round: " + Math.round(-2.60);
szOut = szOut + "\nMath.round: " + Math.round(-2.50);
szOut = szOut + "\nMath.round: " + Math.round(-2.49);

szOut = (szOut + "\nMath.sin:   " + RoundTo(iDec, Math.sin(135)) );
szOut = (szOut + "\nMath.sqrt:  " + RoundTo(iDec, Math.sqrt(25)) );
szOut = (szOut + "\nMath.tan:   " + RoundTo(iDec, Math.tan(135)) );

print (szOut);
