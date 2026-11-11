PROG=lab5

# Ficheiros para o executável
SRCS = lab5.c video_gr.c

# Flags e Includes
CFLAGS += -pedantic -I../lab3 -I../lab2

# Dependências de bibliotecas externas
DPADD += ${LIBLCF} ../lab3/libkbc.a ../lab2/libtimer.a
LDADD += -llcf ../lab3/libkbc.a ../lab2/libtimer.a

# --- Parte da Biblioteca Local ---
LIB_NAME = libvideo.a
LIB_SRCS = video_gr.c
LIB_OBJS = ${LIB_SRCS:.c=.o}

# Inclui as regras do Minix (essencial para o lcom_run)
.include <minix.lcom.mk>

# Regra 'all' para garantir que as libs externas e a interna são criadas
all: libs ${LIB_NAME} ${PROG}

# Cria a tua biblioteca local do Lab 5
${LIB_NAME}: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

# Garante que os outros labs estão compilados
libs:
	${MAKE} -C ../lab2 lib
	${MAKE} -C ../lab3 lib

# Limpeza extra
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}