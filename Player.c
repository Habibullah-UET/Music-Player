/*

HABIBULLAH
08/01/2016

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include "config.h"
#define BUFSIZE 1024

int main(int argc, char **argv) 
{
    /* The Sample format to use */
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2
    };
   
    pa_simple *s = NULL;
    int ret = 1;
    int error;
      if (argc != 2)
      {
      	printf("Usage: %s Audio_File_Name.Extension\n",argv[0] );
      	return 1;
      }

	 if(strcmp(argv[1],"-i") == 0)
	   {
	   	showconfig();
	   	return 0;
	   }
	 
        int fd;
        if ((fd = open(argv[1], O_RDONLY)) < 0)
         {
            fprintf(stderr,"Unable to Open : %s\n", strerror(errno));
            goto finish;
         }
        
        if (dup2(fd, STDIN_FILENO) < 0) 
        {
            fprintf(stderr,": Unable to Duplicate: %s\n", strerror(errno));
            goto finish;
        }
        close(fd);
     
    /* Create a new playback stream */
    if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error)))
     {
        fprintf(stderr, __FILE__": Failed to create Playback Stream: %s\n", pa_strerror(error));
        goto finish;
     }
    for (;;) 
    {
        uint8_t buf[BUFSIZE];
        ssize_t r;

    

        /* Read some data ... */
        if ((r = read(STDIN_FILENO, buf, sizeof(buf))) <= 0) 
        {
            if (r == 0) /* EOF */
                break;
            fprintf(stderr, __FILE__": Failed to read: %s\n", strerror(errno));
            goto finish;
        }

        /* Time to play */
        if (pa_simple_write(s, buf, (size_t) r, &error) < 0) 
        {
            fprintf(stderr,"Faild to Play: %s\n", pa_strerror(error));
            goto finish;
        }
        printf(" * ");
       
    } 

    /* Make sure that every single sample was played */
    
    if (pa_simple_drain(s, &error) < 0) 
    {
        fprintf(stderr, __FILE__": Unable to play all sampels: %s\n", pa_strerror(error));
        goto finish;
    }
    ret = 0;      // normal Termination..... 

finish:
    if (s)
        pa_simple_free(s);
    return ret;
}