

OSPL_LIBS = -lpthread -lddskernel -ldcpssacpp
LIBS=-L${OSPL_HOME}/lib ${OSPL_LIBS} -lboost_system -lboost_thread

CFLAGS = -Wall -O0 -g -I. \
         -I./include -I${OSPL_HOME}/include/dcps/C++/SACPP \
         -I${OSPL_HOME}/include/sys \
         -I${OSPL_HOME}/include

CXXFLAGS = -std=c++11

all: stalker


IDL_GENERATED_H= \
                 ccpp_tsn.h \
                 tsnDcps.h \
                 tsnDcps_impl.h \
                 tsn.h \
                 tsnSplDcps.h 

IDL_GENERATED_CPP=\
                 tsn.cpp \
                 tsnDcps.cpp \
                 tsnDcps_impl.cpp \
                 tsnSplDcps.cpp

IDL_GENERATED=${IDL_GENERATED_H} ${IDL_GENERATED_CPP}

${IDL_GENERATED}: idl/tsn.idl
	${OSPL_HOME}/bin/idlpp -l cpp idl/tsn.idl

COMMON_CPP= src/CheckStatus.cpp src/DDSEntityManager.cpp 

COMMON_H= src/io.h src/CheckStatus.h src/DDSEntityManager.h 


stalker: ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} src/stalker.cpp
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS}

#Dealer: ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} src/Dealer.cpp ${DEALER_FILES} ${DEALER_H_FILES}  ${COMMON_H} ${COMMON_CPP}
#	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS}

#Player: ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} src/Player.cpp ${PLAYER_FILES} ${PLAYER_H_FILES} ${COMMON_H} ${COMMON_CPP}
#	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS}

clean:
	-rm -f stalker
	-rm -f ${IDL_GENERATED_H} ${IDL_GENERATED_CPP}
	-rm -f ospl-error.log ospl-info.log
