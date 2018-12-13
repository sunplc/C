VAR=2
test $VAR -gt 1
echo $?

test $VAR -gt 3
echo $?

[ $VAR -gt 3 ]
echo $?
