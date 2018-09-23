
// this program, called 'stalker' is designed to assist in debugging 
// TheSocialNetwork.
//
// it only listens, it never publishes anything.

#include <time.h>

#include <string.h>

#include <iostream>
#include <iomanip>


#include "tsn.h"
#include "dds_io.h"



// this macro creates some internal test data that
// can be used to verify this code works.
#define MAKE_TEST_DATA 

void print_time ()
{
   struct timespec t;
   clock_gettime ( CLOCK_REALTIME, &t );
   std::cout << t.tv_sec << " " 
             << int(t.tv_nsec/1e6) 
             << " ";
}
void print ( TSN::user_information D )
{
   print_time ();
   std::cout << "Received : user_information" << std::endl;
   std::cout << "               " << D.uuid << " "
                                << D.first_name << " "
                                << D.last_name  << " "
                                << " date of birth " 
                                << D.date_of_birth << std::endl;
   std::cout << "               " 
                                << "number of posts " 
                                << D.number_of_highest_post << std::endl;
   std::cout << "               ";
   for (unsigned int i=0;i<D.interests.length ();i++)
   {
       std::cout << "(" << D.interests[i] << ") "; 
   }
   std::cout << std::endl;
}

void print ( TSN::response D )
{
   print_time ();
   std::cout << "Received :" << std::endl;
}

void print ( TSN::request D )
{
   print_time ();
   std::cout << "Received :" << std::endl;
}

#ifdef MAKE_TEST_DATA
TSN::user_information test_data_user_information ()
{
   static int count=0;
   count++;
   std::string uuid;
   TSN::user_information D;
   if (count%2)
   {
     uuid = "d21633d5-12fb-4c93-a4a4-a56f06b7ba24";
     D.first_name = DDS::string_dup("Bud");
     D.last_name = DDS::string_dup("Davis");
     D.date_of_birth = 1;  // roughly 48 years old
     D.interests.length(1);
     D.interests[0] = DDS::string_dup("magic the gathering");
   }
   else
   {
     uuid = "924741ba-5eee-4db9-90fc-ea0175fd5686";
     D.first_name = DDS::string_dup("Someone");
     D.last_name = DDS::string_dup("Else");
     D.date_of_birth = 1537716138;
     D.interests.length(2);
     D.interests[0] = DDS::string_dup("algorithms");
     D.interests[1] = DDS::string_dup("football");
   }

   D.number_of_highest_post = 0;
   strncpy (D.uuid,uuid.c_str(),sizeof(D.uuid));
   D.uuid[sizeof(D.uuid)-1] = '\0';


   return D;
}

TSN::response test_data_response () 
{
   TSN::response D;
   return D;
}

TSN::request test_data_request ()
{
   TSN::request D;
   return D;
}
#endif

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
#ifdef MAKE_TEST_DATA
                          ( (char*) "user_information", true     , true );
#else
                          ( (char*) "user_information", false     , true );
#endif
                          //        topic name,         publish, subscribe

                   dds_io<response,
                          responseSeq,
                          responseTypeSupport_var,
                          responseTypeSupport,
                          responseDataWriter_var,
                          responseDataWriter,
                          responseDataReader_var,
                          responseDataReader> Response = 
                   dds_io<response,
                          responseSeq,
                          responseTypeSupport_var,
                          responseTypeSupport,
                          responseDataWriter_var,
                          responseDataWriter,
                          responseDataReader_var,
                          responseDataReader>
#ifdef MAKE_TEST_DATA
                          ( (char*) "response", true     , true );
#else
                          ( (char*) "response", false     , true );
#endif
                          //        topic name,         publish, subscribe

                   dds_io<request,
                          requestSeq,
                          requestTypeSupport_var,
                          requestTypeSupport,
                          requestDataWriter_var,
                          requestDataWriter,
                          requestDataReader_var,
                          requestDataReader> Request = 
                   dds_io<request,
                          requestSeq,
                          requestTypeSupport_var,
                          requestTypeSupport,
                          requestDataWriter_var,
                          requestDataWriter,
                          requestDataReader_var,
                          requestDataReader>
#ifdef MAKE_TEST_DATA
                          ( (char*) "request", true     , true );
#else
                          ( (char*) "request", false     , true );
#endif
                          //        topic name,         publish, subscribe

   while (1)
   {
#ifdef MAKE_TEST_DATA
      static int count=0;
      count++;
      if (count%10 == 0 )
      {
         UserInfo.publish ( test_data_user_information () );
         //Request.publish  ( test_data_request () );
         //Response.publish ( test_data_response () );
      }
#endif
      {
         std::vector<TSN::user_information> V = UserInfo.recv ();
         for (unsigned int i=0;i<V.size();i++)
         {
            print ( V[i] );
         }
      }
      {
         std::vector<TSN::response> V = Response.recv ();
         for (unsigned int i=0;i<V.size();i++)
         {
            print ( V[i] );
         }
      }
      {
         std::vector<TSN::request> V = Request.recv ();
         for (unsigned int i=0;i<V.size();i++)
         {
            print ( V[i] );
         }
      }
      usleep(100000); // 1/10 of a second
   }
#ifdef XX
      D.first_name = DDS::string_dup("MSFT");
      UserInfo.publish ( D );
      sleep(1);
      D.first_name = DDS::string_dup("AAA");
      UserInfo.publish ( D );
   }
#endif
   return 0;
}
