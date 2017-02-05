#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>
#define PROGRAM_NAME	    "Audio Media Player"
#define PROGRAM_BUILD	    " [1.0.0] "
#define PROGRAM_AUTHOR	    "HABIBULLAH"
#define PROGRAM_COPYRIGHTS  "Public Domain"
#define PROGRAM_DESCRIPTION "A Light Weight Audio Player that Plays tone in the Terminal"
void showconfig()
{
  printf("%s : ",PROGRAM_NAME );
  printf("%s\n",PROGRAM_BUILD );
  printf("%s\n\n", PROGRAM_AUTHOR);
  printf("%s\n",PROGRAM_DESCRIPTION);
}
void showconfig_M(char *s)
{
	printf("%s\n",s );
}


#endif