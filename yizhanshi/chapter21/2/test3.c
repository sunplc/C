#define showlist(...) printf(#__VA_ARGS__)
#define report(test, ...) ((test) ? printf(#test) : \
		printf(__VA_ARGS__))

showlist(The first, second, and the third items.);
report(x>y, "x is %d but y is %d", x, y);
