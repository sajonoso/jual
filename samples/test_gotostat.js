var iDoTimes=5;
goto HERE;

::THERE::
print("I got there");
goto EVERYWHERE;

::HERE::
print("I got here");
iDoTimes = iDoTimes - 1;
if (iDoTimes > 0) { goto HERE; };
goto THERE;

::EVERYWHERE::
print("I got everywhere!");
