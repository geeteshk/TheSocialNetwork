
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

   TSN::user_information D;
   D.first_name = DDS::string_dup("MSFT");
   while (1)
   {
      D.first_name = DDS::string_dup("MSFT");
      UserInfo.publish ( D );
      sleep(1);
      // this sleep says there is either a history depth of one
      // or the instances are not being done correctly.
      // will investigate shortly.
      D.first_name = DDS::string_dup("AAA");
      UserInfo.publish ( D );
      sleep(1);
      std::vector<TSN::user_information> V = UserInfo.recv ();
      std::cout << "the size is " << V.size() << std::endl;
      for (auto i=0;i<V.size();i++)
      {
         std::cout << i << "  " << V[i].first_name << std::endl;
      }

   }
   return 0;
}
