mkdir -p /tmp/php7.0-xapian/$(php-config --extension-dir)
mkdir -p /tmp/php7.0-xapian/etc/php/7.0/mods-available
mkdir -p /tmp/php7.0-xapian/DEBIAN
cp xapian.so /tmp/php7.0-xapian/$(php-config --extension-dir)/
cp xapian.ini /tmp/php7.0-xapian/etc/php/7.0/mods-available/
ln -sf ../../mods-available/xapian.ini /tmp/php7.0-xapian/etc/php/7.0/cli/conf.d/20-xapian.ini
ln -sf ../../mods-available/xapian.ini /tmp/php7.0-xapian/etc/php/7.0/fpm/conf.d/20-xapian.ini
cat <<END > /tmp/php7.0-xapian/DEBIAN/control
Package: php7.0-xapian
Architecture: amd64
Maintainer: pascal.masschelier@elbee.fr
Depends: libxapian22 (>=1.4)
Priority: optional
Version: 1.4.0
Description: xapian search engine bindings for php7
END

cat <<END > /tmp/php7.0-xapian/DEBIAN/conffiles
END
(cd /tmp;dpkg-deb -b php7.0-xapian)
dpkg --contents /tmp/php7.0-xapian.deb
