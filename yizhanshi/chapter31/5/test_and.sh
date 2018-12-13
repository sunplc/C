test "$(whoami)" != 'root' && (echo "you are using a non-privileged account"; exit 1)

test "$(whoami)" == 'root' && (echo "you are using a privileged account"; exit 0)
