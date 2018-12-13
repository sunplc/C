#! /bin/sh

for FRUIT in apple banana pear; do
    echo "I like $FRUIT"
done

echo ""

for FILENAME in `ls .`; do
    echo "$FILENAME"
done
