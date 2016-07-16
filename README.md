
# php 7 bindings for xapian

## build env

docker run -it -v ~/projects:/root/projects debian:testing

apt-get update
apt-get install -y --no-install-recommends php7.0-dev xzdec curl g++-6 uuid-dev make sudo

## make libxapian22 deb package
cd ~/projects
curl http://oligarchy.co.uk/xapian/1.4.0/xapian-core-1.4.0.tar.xz|xzdec|tar -xf -
cd xapian-core-1.4.0/
./configure prefix=/usr
make
make install prefix=/tmp/libxapian22/usr

mkdir -p /tmp/libxapian22/DEBIAN
cat <<END > /tmp/libxapian22/DEBIAN/control
Package: libxapian22
Architecture: amd64
Maintainer: pascal.masschelier@elbee.fr
Depends: libc6 (>= 2.11), libgcc1 (>= 1:4.1.1), libstdc++6 (>= 4.4), libuuid1 (>= 2.16), zlib1g (>= 1:1.1.4)
Priority: optional
Version: 1.4.0
Description: xapian search engine
END

cat <<END > /tmp/libxapian22/DEBIAN/conffiles
END

(cd /tmp;dpkg-deb -b libxapian22)

dpkg -i /tmp/libxapian22.deb

## build bindings

cd ~/projects
curl http://oligarchy.co.uk/xapian/1.4.0/xapian-bindings-1.4.0.tar.xz|xzdec|tar -xf -
cd xapian-bindings-1.4.0/
./configure prefix=/usr --with-php
"SWIG doesn't yet support PHP7"

cd ~/projects/php7xapian
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git 
(cd PHP-CPP;make;make install)

ln -s PHP-CPP/include phpcpp
ln -s include PHP-CPP/phpcpp
mkdir -p /etc/php/7.0/mods-available/

tweak Makefile

make install && php -f test.php



(docker image is debian:testing, container is 4407da48e4d8 berserk_allen)

