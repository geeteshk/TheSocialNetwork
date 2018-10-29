

// g++ console.cpp -Wall -std=c++11 -lpthread

#include <iostream>
#include <string>
#include <deque>
#include <thread>
#include <unistd.h>

#include <termios.h>

class screenBuffer
{
  public:
    std::deque<std::string> Q;
    bool inhibit; // i really think this should be a mutex.  
    screenBuffer ()
    {
       inhibit = false;
    }
    ~screenBuffer ()
    {
    }
} screenBuff;


bool quit = false;
// would expect this could be used to cleanly exit the threads.

void out_to_screen ()
{
    while (!quit)
    {
       // prints to the screen a single std::string, representing a
       // line of input.
       if (!screenBuff.inhibit && !screenBuff.Q.empty () )
       {
           std::string S;
           S = screenBuff.Q.back ();
           screenBuff.Q.pop_back ();
           std::cout << "q size = " << screenBuff.Q.size() << " [" << S << "]" << std::endl;
       }
       usleep(50000); // 50 msec or 20 times a second
       // sleeping an polling is not the best way to do this, but it is easy to understand
       // thats my excuse and i am sticking to it.
    }
}

void make_some_output ()
{
   int x=0;
   std::string msg[] = { "the first string ", "another string to display","and something else"};
   // this would be some async output coming from another thread that needs to be displayed to
   // stdout
   while (1)
   {
      screenBuff.Q.push_front ( msg[x] );
      x++;
      if (x>2) 
      {
         x = 0;
      }
      sleep(2);
   }
}

int main (int argc, char* argv[])
{
  std::thread p( out_to_screen );
  std::thread q( make_some_output );


  struct termios ctrl;
  tcgetattr(STDIN_FILENO, &ctrl);
  ctrl.c_lflag &= ~ICANON; // turning off canonical mode makes input unbuffered
  ctrl.c_lflag &= ~ECHO;   // do not echo input 
  tcsetattr(STDIN_FILENO, TCSANOW, &ctrl);

  std::string S;

  // to start out, all input is ignored except for the first <enter>
  //
  // the first enter then inhibits the output thread, and repeats every
  // character entered to stdout.
  //
  // on the next <enter> the string just entered is sent to the display
  // output Q, and the inhibit for the display is cleared
  //
  //
  //  this is just an example!  it needs lots of work to really be usable

  while (!quit)
  {
     int i = getchar();
     unsigned char ch = i;
     std::string T(1,ch);

     if (screenBuff.inhibit)
     { 
        if ( isprint(ch) )
        {
           std::cout << ch;  //  echo the entry
           S = S + T;
        }
        else if (ch=='\n')
        {
           std::cout << std::endl;
        }
     }

     if (ch=='\n')
     {
        if (screenBuff.inhibit)
        {
           // we are taking input from the user
           if (S.size ())
           {
              screenBuff.Q.push_front ( S );
           }
           S = ""; 
           screenBuff.inhibit = !screenBuff.inhibit;
        } 
        else
        {
           // change the 'mode'
           screenBuff.inhibit = !screenBuff.inhibit;
        }
     }
     usleep (10000); // 1/10 of a second
  }
  p.join  ();
  q.join ();
  return 0;
}
