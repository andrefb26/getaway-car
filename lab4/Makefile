# name of the program (Minix service)
PROG=lab4

# source code files to be compiled
SRCS = lab4.c mouse.c kbc.c  utils.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -I. -I../lab2 -pedantic

# list of library dependencies (for Lab 2, only LCF library)
DPADD +=  ${LIBLCF} ../lab2/libtimer.a
LDADD +=  -llcf -L../lab2 -ltimer

LIB_NAME = libmouse.a
LIB_SRCS = mouse.c
LIB_OBJS = ${LIB_SRCS:.c=.o}
all: lib
lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}
# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
