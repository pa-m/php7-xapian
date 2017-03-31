FROM debian:9
RUN apt-get update &&\
apt-get install -y --no-install-recommends php7.0-dev xzdec curl g++ uuid-dev make libxapian30 libxapian-dev curl unzip sudo git ca-certificates

