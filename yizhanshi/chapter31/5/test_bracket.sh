[ -d folder ]
echo $?

[ -f file ]
echo $?

VAR=hello
[ -z VAR ]
echo $?

[ -n VAR ]
echo $?

[ VAR = VAR ]
echo $?

[ VAR != VAR ]
echo $?

[ 2 -lt 3 ]
echo $?

test ! 2 -lt 3
echo $?

unset VAR
VAR=abc
[ -d folder -a "$VAR" = 'abc' ]
echo $?
