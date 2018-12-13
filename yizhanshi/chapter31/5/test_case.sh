#! /bin/sh

echo "Is it morning? Please enter yes or no."
read YES_OR_NO
case "$YES_OR_NO" in
yes|y|Yes|YES)
    echo "Good morning!";;
[nN]*)
    echo "Good afternoon!";;
7)
    echo "you typed 7.";;
*)
    echo "Sorry, \"$YES_OR_NO\" not recognized. Enter yes or no."
esac
exit 0
