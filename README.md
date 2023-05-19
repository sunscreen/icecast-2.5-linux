# icecast-2.5-linux
root@ks4000477:~/icecast-2.5-linux/src/builddir# time meson setup --wipe
The Meson build system
Version: 1.1.0
Source dir: /root/icecast-2.5-linux/src
Build dir: /root/icecast-2.5-linux/src/builddir
Build type: native build
Project name: icecast-linux
Project version: 2.5.0-Linux
C compiler for the host machine: cc (gcc 4.9.2 "cc (Debian 4.9.2-10) 4.9.2")
C linker for the host machine: cc ld.bfd 2.25
Host machine cpu family: x86_64
Host machine cpu: x86_64
Run-time dependency threads found: YES
Found pkg-config: /usr/bin/pkg-config (0.28)
Run-time dependency libssl found: YES 3.2.0-dev
Run-time dependency libcrypto found: YES 3.2.0-dev
Run-time dependency libxml-2.0 found: YES 2.9.1
Run-time dependency libxslt found: YES 1.1.28
Run-time dependency libcurl found: YES 8.1.0-DEV
Run-time dependency vorbis found: YES 1.3.4
Run-time dependency ogg found: YES 1.3.2
Run-time dependency theora found: YES 1.1.1
Run-time dependency speex found: YES 1.2rc1
Has header "unistd.h" : YES
Has header "inttypes.h" : YES
Has header "stdint.h" : YES
Has header "pwd.h" : YES
Has header "grp.h" : YES
Has header "strings.h" : YES
Has header "sys/types.h" : YES
Has header "sys/stat.h" : YES
Has header "sys/uio.h" : YES
Has header "sys/socket.h" : YES
Has header "sys/resource.h" : YES
Has header "sys/select.h" : YES
Has header "sys/epoll.h" : YES
Checking for function "epoll_create" : YES
Message: Best Poll Selected Epoll
Checking for function "select" : YES
Checking for function "inet_pton" : YES
Checking for function "inet_addr" : YES
Checking for function "getnameinfo" : YES
Checking for function "gethostname" : YES
Checking for function "getaddrinfo" : YES
Checking for function "localtime_r" : YES
Checking for function "uname" : YES
Checking for function "getrlimit" : YES
Checking for function "nanosleep" : YES
Checking for function "setenv" : YES
Checking for function "setuid" : YES
Checking for function "setresuid" : YES
Checking for function "setresgid" : YES
Checking for function "chroot" : YES
Checking for function "sethostent" : YES
Checking for function "endhostent" : YES
Checking for function "strcasestr" : YES
Checking for function "writev" : YES
Message: /root/icecast-2.5-linux/src
Message: Installing web interface to: /usr/local/share/icecast-linux
Configuring config.h using configuration
Build targets in project: 7

Found ninja-1.12.0.git at /usr/bin/ninja

real    0m1.324s
user    0m0.876s
sys     0m0.132s
root@ks4000477:~/icecast-2.5-linux/src/builddir# mcedit ../meson.build

root@ks4000477:~/icecast-2.5-linux/src/builddir# time meson compile
INFO: autodetecting backend as ninja
INFO: calculating backend command to run: /usr/bin/ninja
[74/74] Linking target icecast

real    0m1.884s
user    0m4.832s
sys     0m0.512s
root@ks4000477:~/icecast-2.5-linux/src/builddir# cd common/
