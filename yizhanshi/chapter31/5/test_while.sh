#! /bin/sh

echo "Enter password:"
read TRY
COUNTER=0
while [ "$COUNTER" -lt 5 ]; do
    if test "$TRY" = 'secret'; then
        echo "Yeah, password correct."
        exit 0
    else
        echo "Sorry, password not correct, try again."
    fi
    if test "$COUNTER" = 4; then
        echo "You have tried five times."
        exit 1
    else
        read TRY
    fi
    COUNTER=$(($COUNTER+1))
done
