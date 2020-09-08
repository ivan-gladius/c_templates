#include <jni.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "hello.h"



void make_lower( char *word )
 {
          for ( int x = 0; x < 250; x++)
          {
                  word[x] = tolower(word[x]);
          }
  }

#define LIM 10000

JNIEXPORT void JNICALL Java_hello_sayHello(JNIEnv *env, jobject thisObj)
{

	const char *bad[] = { "bad", "ass", "fuck", "pee", NULL };
          size_t n = sizeof(bad) / sizeof(bad[0]);
          char msg[LIM];
          char msg_copy[LIM];
          char *p;
  
          printf("Comment: ");
          fgets(msg, LIM, stdin);
          msg[strcspn(msg, "\n")] = 0;
  
          strcpy(msg_copy, msg);
          make_lower(msg_copy);
  
  
          for ( int x = 0; x < strlen(msg_copy); x++)
          {
  
                 for ( int y = 0; y < 4 ; y++)
                  {
                          p = strstr(msg_copy, bad[y]);
  
                          if ( p )
                          {
                                  memset(p, '*', strlen(bad[y]));
                          }
                          p = msg_copy;
                  }
 
         }
 
          printf("%s\n", msg_copy);


	return;


}
