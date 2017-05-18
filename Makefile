#================================[[ beg-code ]]================================#
BASE    = hyleoroi



#*---(standard variables)-------------*#
# must have "-x c" on gcc line so stripped files work with alternate extensions
#    shape requires -lXext and #include <X11/extentions/shape.h>
COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
INCS    = -I/usr/local/include 
LINK    = gcc 
LIBS    =
LIBS    = -L/usr/local/libs -lyX11 -lX11 -lGL -lGLU -lm -lXext -lySTR -lyFONT
LIBD    = -L/usr/local/libs -lyX11 -lX11 -lGL -lGLU -lm -lXext -lySTR -lyFONT -lyLOG
OBJS    = ${BASE}_main.os ${BASE}_prog.os ${BASE}_file.os ${BASE}_node.os ${BASE}_draw.os
OBJD    = ${BASE}_main.o  ${BASE}_prog.o  ${BASE}_file.o  ${BASE}_node.o  ${BASE}_draw.o

#*---(make variables)-----------------*#
COPY    = cp -f  
CLEAN   = rm -f
ECHO    = @echo
PRINTF  = @printf
STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



#*---(MAIN)---------------------------*#
all                : ${BASE}



#*---(executables)--------------------*#
${BASE}            : ${OBJD}
	${LINK}  -o ${BASE}        ${OBJS}   ${LIBS}
	${LINK}  -o ${BASE}_debug  ${OBJD}   ${LIBD}



#*---(normal objects)-----------------*#
${BASE}_main.o     : ${BASE}.h    ${BASE}_main.c
	${COMP}    ${BASE}_main.c                        ${INC}
	${STRIP}   ${BASE}_main.c    > ${BASE}_main.cs
	${COMP}    ${BASE}_main.cs  -o ${BASE}_main.os   ${INC}

${BASE}_prog.o     : ${BASE}.h    ${BASE}_prog.c
	${COMP}    ${BASE}_prog.c                        ${INC}
	${STRIP}   ${BASE}_prog.c    > ${BASE}_prog.cs
	${COMP}    ${BASE}_prog.cs  -o ${BASE}_prog.os   ${INC}

${BASE}_file.o     : ${BASE}.h    ${BASE}_file.c
	${COMP}    ${BASE}_file.c                        ${INC}
	${STRIP}   ${BASE}_file.c    > ${BASE}_file.cs
	${COMP}    ${BASE}_file.cs  -o ${BASE}_file.os   ${INC}

${BASE}_node.o     : ${BASE}.h    ${BASE}_node.c
	${COMP}    ${BASE}_node.c                        ${INC}
	${STRIP}   ${BASE}_node.c    > ${BASE}_node.cs
	${COMP}    ${BASE}_node.cs  -o ${BASE}_node.os   ${INC}

${BASE}_draw.o     : ${BASE}.h    ${BASE}_draw.c
	${COMP}    ${BASE}_draw.c                        ${INC}
	${STRIP}   ${BASE}_draw.c    > ${BASE}_draw.cs
	${COMP}    ${BASE}_draw.cs  -o ${BASE}_draw.os   ${INC}



#*---(housekeeping)-------------------*#
bigclean           :
	${ECHO}  cleaning out swap files
	${CLEAN} .*.swp

clean              :
	${ECHO}  cleaning out object, backup, and temp files
	${CLEAN} ${BASE}
	${CLEAN} ${BASE}*.o
	${CLEAN} ${BASE}*.cs
	${CLEAN} ${BASE}*.os
	${CLEAN} *~
	${CLEAN} temp*
	${CLEAN} ${BASE}_unit
	${CLEAN} ${BASE}_unit.c

install            : ${BASE}
	#---(executable)----------------------#
	${ECHO}  installing in b_nvdo
	${COPY}  ${BASE}         /usr/local/bin/
	chmod    0755           /usr/local/bin/${BASE}
	sha1sum  ${BASE}
	${COPY}  ${BASE}_debug   /usr/local/bin/
	chmod    0755           /usr/local/bin/${BASE}_debug
	#---(documentation)-------------------#
	rm -f       /usr/share/man/man1/${BASE}.1.bz2
	cp -f       ${BASE}.1    /usr/share/man/man1/${BASE}.1
	bzip2       /usr/share/man/man1/${BASE}.1
	chmod 0644  /usr/share/man/man1/${BASE}.1.bz2



#================================[[ end-code ]]================================#
