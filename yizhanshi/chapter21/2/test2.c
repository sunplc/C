#define STR(s) #s
#define CONCAT(a, b) a ## b
#define HASH_HASH # ## #
//STR(hello		world);
//fputs(STR(strncmp("ab\"c\0d", "abc", '\4"') == 0) STR(: @\n), s);
//CONCAT(he, llo);

HASH_HASH
