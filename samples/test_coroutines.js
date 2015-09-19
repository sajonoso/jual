// Testing co-routines in JualScript
// translated from http://lua-users.org/wiki/CoroutinesTutorial

function odd(x) {
   print('A: odd', x);
   coroutine.yield(x);
   print('B: odd', x);
}

function even(x) {
    print('C: even', x);
    if (x==2) { return x };
    print('D: even ', x);
}

function cro(x) {
    for (i=1; i<=x; i=i+1) {
        if (i==3) { coroutine.yield(-1); };
        if (i % 2 == 0) { even(i); } else { odd(i); };
    };
}
co = coroutine.create(cro)

var count = 1
while (coroutine.status(co) != 'dead') {
   print('----', count) ; count = count+1;
   errorfree, value = coroutine.resume(co, 5);
   print('E: errorfree, value, status', errorfree, value, coroutine.status(co));
};
