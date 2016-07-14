
# php 7 bindings for xapian

## build env

docker run -it -v ~/projects:/root/projects debian:testing

apt-get update
apt-get install -y --no-install-recommends php7.0-dev xzdec curl g++ uuid-dev make sudo

cd ~/projects
curl http://oligarchy.co.uk/xapian/1.4.0/xapian-core-1.4.0.tar.xz|xzdec|tar -xf -
cd xapian-core-1.4.0/
./configure prefix=/usr
make
make install

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

rm *.so *.o;make && make install && php -f test.php

docker image is debian:testing, container is 4407da48e4d8 berserk_allen

