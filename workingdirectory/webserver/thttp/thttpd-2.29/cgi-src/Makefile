# Generated automatically from Makefile.in by configure.
# Makefile for cgi-src
#
# Copyright � 1995 by Jef Poskanzer <jef@mail.acme.com>.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.

prefix =	/usr/local/thttpd
exec_prefix =	${prefix}
WEBDIR =	$(prefix)/www
CGIBINDIR =	$(WEBDIR)/cgi-bin
MANDIR =	${prefix}/man

CC =		gcc
CCOPT =		-O2
DEFS =		 -DHAVE__PROGNAME=1 -DHAVE_FCNTL_H=1 -DHAVE_GRP_H=1 -DHAVE_MEMORY_H=1 -DHAVE_PATHS_H=1 -DHAVE_POLL_H=1 -DHAVE_SYS_POLL_H=1 -DTIME_WITH_SYS_TIME=1 -DHAVE_DIRENT_H=1 -DHAVE_LIBCRYPT=1 -DHAVE_STRERROR=1 -DHAVE_WAITPID=1 -DHAVE_VSNPRINTF=1 -DHAVE_DAEMON=1 -DHAVE_SETSID=1 -DHAVE_GETADDRINFO=1 -DHAVE_GETNAMEINFO=1 -DHAVE_GAI_STRERROR=1 -DHAVE_SIGSET=1 -DHAVE_ATOLL=1 -DHAVE_UNISTD_H=1 -DHAVE_GETPAGESIZE=1 -DHAVE_MMAP=1 -DHAVE_SELECT=1 -DHAVE_POLL=1 -DHAVE_TM_GMTOFF=1 -DHAVE_INT64T=1 -DHAVE_SOCKLENT=1 
INCLS =		-I..
CFLAGS =	$(CCOPT) $(DEFS) $(INCLS)
LDFLAGS =	 
LIBS =		-lcrypt 
NETLIBS =	
INSTALL =	/usr/bin/install -c

CLEANFILES =	*.o redirect ssi phf



.c.o:
	@rm -f $@
	$(CC) $(CFLAGS) -c $*.c

all:		redirect ssi phf

redirect:	redirect.o
	$(CC) $(LDFLAGS) $(STATICFLAG) redirect.o $(LIBS) -o redirect

ssi:		ssi.o ../match.o
	$(CC) $(LDFLAGS) $(STATICFLAG) ssi.o ../match.o $(LIBS) -o ssi

ssi.o:		../match.h

phf:		phf.o
	$(CC) $(LDFLAGS) $(STATICFLAG) phf.o $(LIBS) -o phf

strerror.o:
	@rm -f strerror.o
	@ln -s ../strerror.o
	cd .. ; $(MAKE) $(MFLAGS) strerror.o

install:	all
	-mkdir -p $(CGIBINDIR)
	rm -f $(CGIBINDIR)/redirect
	cp redirect $(CGIBINDIR)/redirect
	rm -f $(MANDIR)/man8/redirect.8
	cp redirect.8 $(MANDIR)/man8/redirect.8
	rm -f $(CGIBINDIR)/ssi
	cp ssi $(CGIBINDIR)/ssi
	rm -f $(MANDIR)/man8/ssi.8
	cp ssi.8 $(MANDIR)/man8/ssi.8
	rm -f $(CGIBINDIR)/phf
	cp phf $(CGIBINDIR)/phf

clean:
	rm -f $(CLEANFILES)

distclean:
	rm -f $(CLEANFILES) Makefile
