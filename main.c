#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void main(void)
{
    int    fd1;  /* input sources 1 and 2 */
    fd_set readfs;    /* file descriptor set */
    fd_set realfs;    /* file descriptor set */
    int    maxfd;     /* maximum file desciptor used */
    int    loop=1;    /* loop while TRUE */
    struct timeval       timeout;

    /* open_input_source opens a device, sets the port correctly, and
       returns a file descriptor */
    fd1 = open("/dev/ttyS1");   /* COM2 */
    maxfd = fd1+1;  /* maximum bit entry (fd) to test */
    timeout.tv_sec  = 3;
    timeout.tv_usec = 0;

    FD_ZERO(&readfs);  /* set testing for source 1 */
    FD_ZERO(&realfs);  /* set testing for source 1 */
    FD_SET(fd1, &readfs);  /* set testing for source 1 */
    FD_SET(fd1, &realfs);  /* set testing for source 1 */
    /* loop for input */
    while (loop) {
        memcpy(&readfs, &realfs, sizeof(fd_set));
        /* block until input becomes available */
        select(maxfd, &readfs, NULL, NULL, &timeout);

        printf("Hello\n");
#if 0
        if (FD_ISSET(fd1, &readfs))         /* input from source 1 available */
            handle_input_from_source1();
        if (FD_ISSET(fd2, &readfs))         /* input from source 2 available */
            handle_input_from_source2();
#endif
    }

}
