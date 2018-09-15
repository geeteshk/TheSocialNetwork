# TheSocialNetwork
This repository contains the idl files for the F2018 CSE-3310-002 project

To compile or run anything, you need to execute the release.com file (or its)
equivalent from the opensplice distribution.  

For best results, untar the opensplice distribution in your home directory.



Below was discussed in class.  Might be usefull to keep it around for a while.


Send out a UserInformation
        uuid = 'AAAAAA'
        first name = 'bud'
        dateOfBirth = 0;
        number of highest post = 5;


Another user, sends out Request
        uuid = 'BBBBBBBB'
          fulfiller_uuid = 'AAAAAAAA'
                   request = { 1 }

Then AAAAA sends out a response:

         uuid = 'AAAAAAA"
         post_id = 1
         post body = "dude, the thing got rained out"
         dateOfCreation = <sometime>

Then CCCCC sends out a request
        uuid = 'CCCCCCCCC'
          fulfiller_uuid = 'AAAAAAAA'
                   request = { 2,3,4,5 }



:wq


