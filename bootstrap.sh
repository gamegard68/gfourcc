intltoolize --force --automake
autoreconf --force --install --symlink

if test "x$NOCONFIGURE" = "x"; then
    CFLAGS="-g -O0" ./configure --sysconfdir=/etc --localstatedir=/var "$@"
    make clean
fi

