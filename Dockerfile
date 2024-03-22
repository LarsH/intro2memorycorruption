FROM ubuntu:latest as build
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update
RUN apt-get install -y xinetd gcc

RUN groupadd -r ctf && for u in ctf ctf2 ctf3 ; do useradd -r -g ctf $u ; done && mkdir /home/ctf

# Add all necessary files
ADD chall.c /home/ctf/

run gcc -fno-stack-protector -o /home/ctf/chall /home/ctf/chall.c

# Set permissions
RUN chmod 640 /home/ctf/*
RUN chmod 750 /home/ctf/chall
RUN chown -R root:ctf /home/ctf

# Setup xinetd
ADD ctf.xinetd /etc/xinetd.d/ctf
RUN service xinetd restart

cmd ["/usr/sbin/xinetd", "-dontfork"]
