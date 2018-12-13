VAR=5
test "$VAR" -gt 3 -a "$VAR" -gt 4
echo $?

test "$VAR" -gt 3 && test "$VAR" -gt 4
echo $?
