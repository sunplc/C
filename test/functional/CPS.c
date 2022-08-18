
// JavaScript code demo for CPS (Continuation-passing Style)

/*

function fact(n, ret) {
    if (n == 0)
        ret(1);
    else
        fact(n - 1, function(t0) { ret(n * t0); } );
}

fact(10, function (n) {console.log(n);});

*/
