# this is not a makefile, rather a script that compiles
# and links the helloworld example
echo "Running IDLPP to generate the support code"
${OSPL_HOME}/bin/idlpp -l cpp idl/HelloWorldData.idl
echo "Making the publisher"
g++ -Wall -O0 -g -I. -std=c++11 \
    -I./include -I${OSPL_HOME}/include/dcps/C++/SACPP \
    -I${OSPL_HOME}/include/sys \
    -I${OSPL_HOME}/include \
    -o publisher \
    ./src/CheckStatus.cpp  \
    ./src/DDSEntityManager.cpp  \
    ./src/HelloWorldDataPublisher.cpp \
    HelloWorldData.cpp \
    HelloWorldDataDcps_impl.cpp \
    HelloWorldDataDcps.cpp  \
    HelloWorldDataSplDcps.cpp \
    -L${OSPL_HOME}/lib  \
    -lpthread -lddskernel -ldcpssacpp -lboost_system -lboost_thread 

echo "Making the subscriber"
g++ -Wall -O0 -g -I. -std=c++11 \
    -I./include -I${OSPL_HOME}/include/dcps/C++/SACPP \
    -I${OSPL_HOME}/include/sys \
    -I${OSPL_HOME}/include \
    -o subscriber \
    ./src/CheckStatus.cpp  \
    ./src/DDSEntityManager.cpp  \
    ./src/HelloWorldDataSubscriber.cpp \
    HelloWorldData.cpp \
    HelloWorldDataDcps_impl.cpp \
    HelloWorldDataDcps.cpp  \
    HelloWorldDataSplDcps.cpp \
    -L${OSPL_HOME}/lib  \
    -lpthread -lddskernel -ldcpssacpp -lboost_system -lboost_thread 

