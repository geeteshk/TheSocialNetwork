
// this program, called 'stalker' is designed to assist in debugging 
// TheSocialNetwork.
//
// it only listens, it never publishes anything.

#include <iostream>
#include "tsn.h"
#include "dds_io.h"


int main ( int argc, char* argv[] )
{
   std::cout << "I am the stalker.  I only listen" << std::endl;

   // these classes give us access to routines to read / write opensplice
   // IDL structures over the network.  it is ugly due to all the strong typing
   // and what it takes to make a c++ generic.


                   dds_io<user_information,
                          user_informationSeq,
                          user_informationTypeSupport_var,
                          user_informationTypeSupport,
                          user_informationDataWriter_var,
                          user_informationDataWriter,
                          user_informationDataReader_var,
                          user_informationDataReader> UserInfo = 
                   dds_io<user_information,
                          user_informationSeq,
                          user_informationTypeSupport_var,
                          user_informationTypeSupport,
                          user_informationDataWriter_var,
                          user_informationDataWriter,
                          user_informationDataReader_var,
                          user_informationDataReader>
                          ( (char*) "user_information", true     , true );
                          //        topic name,         publish, subscribe

   while (1)
   {
      TSN::user_information D;
      UserInfo.publish ( D );
      sleep(1);
      std::vector<TSN::user_information> V = UserInfo.recv ();
      std::cout << "the size is " << V.size() << std::endl;
   }
   return 0;
}
