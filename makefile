

OSPL_LIBS = -lpthread -lddskernel -ldcpssacpp
LIBS=-L${OSPL_HOME}/lib ${OSPL_LIBS} 

CFLAGS = -Wall -O0 -g -I. \
         -I./include -I${OSPL_HOME}/include/dcps/C++/SACPP \
         -I${OSPL_HOME}/include/sys \
         -I${OSPL_HOME}/include

CXXFLAGS = -std=c++11

all: stalker tsn


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

COMMON_H= src/dds_io.h src/CheckStatus.h src/DDSEntityManager.h 


stalker: ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} src/stalker.cpp ${COMMON_CPP} ${COMMON_H}
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS}

tsn: ${IDL_GENERATED_H} ${IDL_GENERATED_CPP} src/ConsoleOutput.h src/ConsoleOutput.cpp src/DataStore.cpp src/main.cpp
	g++ -o $@ ${CFLAGS} ${CXXFLAGS} $^ ${LIBS}

clean:
	-rm -f stalker tsn
	-rm -f ${IDL_GENERATED_H} ${IDL_GENERATED_CPP}
	-rm -f ospl-error.log ospl-info.log
