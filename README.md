
# PHP 7 bindings for xapian

Some methods I didnt need are not implemented yet, see TODO

## build environment

Provided Dockerfile contains requirements for debian 9. it can be easily adapted for other distros.


```bash
docker-compose up -d
docker exec -it php7xapian bash


apt-get update
apt-get install -y --no-install-recommends php7.0-dev xzdec curl g++-6 uuid-dev make sudo
```


## build xapian-core and make libxapian30 deb package

if libxapian30 and libxapian-dev are available via apt, as for debian 9, skip this step.

```bash
cd ~/projects
curl http://oligarchy.co.uk/xapian/1.4.0/xapian-core-1.4.0.tar.xz|xzdec|tar -xf -
cd xapian-core-1.4.0/
./configure prefix=/usr
make
make install  prefix=/usr

make install prefix=/tmp/libxapian30/usr

mkdir -p /tmp/libxapian30/DEBIAN
cat <<END > /tmp/libxapian30/DEBIAN/control
Package: libxapian30
Architecture: amd64
Maintainer: pascal.masschelier@elbee.fr
Depends: libc6 (>= 2.11), libgcc1 (>= 1:4.1.1), libstdc++6 (>= 4.4), libuuid1 (>= 2.16), zlib1g (>= 1:1.1.4)
Priority: optional
Version: 1.4.3
Description: xapian search engine
END

cat <<END > /tmp/libxapian30/DEBIAN/conffiles
END

(cd /tmp;dpkg-deb -b libxapian30)

dpkg --contents /tmp/libxapian30.deb

# dpkg -i /tmp/libxapian30.deb

```

## build bindings

```bash

cd ~/projects/php7xapian
[ -f PHP-CPP/.git ] || git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git 
(cd PHP-CPP;make;make install)

ln -s PHP-CPP/include phpcpp
ln -s include PHP-CPP/phpcpp
mkdir -p /etc/php/7.0/mods-available/


make install
```

## build bindings debian package

```bash

mkdir -p /tmp/php7.0-xapian/$(php-config --extension-dir)
mkdir -p /tmp/php7.0-xapian/etc/php/7.0/mods-available
mkdir -p /tmp/php7.0-xapian/DEBIAN
mkdir -p /tmp/php7.0-xapian/usr/lib
cp xapian.so /tmp/php7.0-xapian/$(php-config --extension-dir)/
cp xapian.ini /tmp/php7.0-xapian/etc/php/7.0/mods-available/
cp /usr/lib/lipphpcpp.so* /tmp/php7.0-xapian/usr/lib/
ln -sf ../../mods-available/xapian.ini /tmp/php7.0-xapian/etc/php/7.0/cli/conf.d/20-xapian.ini
ln -sf ../../mods-available/xapian.ini /tmp/php7.0-xapian/etc/php/7.0/fpm/conf.d/20-xapian.ini

cat <<END > /tmp/php7.0-xapian/DEBIAN/control
Package: php7.0-xapian
Architecture: amd64
Maintainer: pascal.masschelier@elbee.fr
Depends: libxapian30 (>=1.4.3)
Priority: optional
Version: 1.4.3
Description: xapian search engine bindings for php7
END

cat <<END > /tmp/php7.0-xapian/DEBIAN/conffiles
END

(cd /tmp;dpkg-deb -b php7.0-xapian)
dpkg --contents /tmp/php7.0-xapian.deb

# dpkg -i /tmp/php7.0-xapian.deb
```

##TODO

implement methods for following classes
- ExpandDecider
- ExpandDeciderAnd
- ExpandDeciderFilterTerms
- ExpandDeciderFilterPrefix
- LatLongCoordsIterator
- LatLongCoords
- LatLongMetric
- GreatCircleMetric
- KeyMaker
- LatLongDistanceKeyMaker
- MultiValueKeyMaker
- PostingSource
- LatLongDistancePostingSource
- ValuePostingSource
- ValueWeightPostingSource
- DecreasingValueWeightPostingSource
- ValueMapPostingSource
- FixedWeightPostingSource
- RangeProcessor
- DateRangeProcessor
- NumberRangeProcessor
- ValueRangeProcessor
- FieldProcessor
- Registry
- StemImplementation
- Utf8Iterator
- ValueSetMatchDecider
