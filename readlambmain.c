/* 
 * File:   readlambmain.c
 * Author: dap
 *
 * Readlamb.c -- test program to try to find lamb poem on another host
 *
 * Created on November 30, 2009, 4:02 PM
 * Updated on November 10, 2016 to use a Posix compliant hostent structure
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define LAMBPORT 10035

#define abort(param) { fprintf(stderr, "Read lamb program: ");\
                        fprintf param ;\
                        exit(1) ; }

int main(int argc, char** argv) {

    struct hostent *hostptr;
    struct sockaddr_in server_sockaddr;
    int socket_fd = -1;
    char * server_netadd;
    int loop;
    char textin[80];
    int result;
    char server_name[80];

    printf("Read Lamb Poem: where is server?:");
    scanf("%79s", server_name);

    printf("Trying to find %s\n", server_name);

    hostptr = gethostbyname(server_name);
    if (hostptr == NULL)
        abort((stderr, " Couldn't get hostname '%s' \n", server_name));

    server_netadd = hostptr->h_addr_list[0];

    printf("\nhost official name is %s\nadd type %d add len %d \n"
            , hostptr->h_name, hostptr->h_addrtype
            , hostptr->h_length);
    printf("net work address \n");
    for (loop = 1; loop <= hostptr->h_length; loop++)
        printf("%d.", (*server_netadd++) & 255);
    printf("\n");

    server_sockaddr.sin_family = AF_INET;
    memcpy(& server_sockaddr.sin_addr, hostptr->h_addr_list[0], hostptr->h_length);
    server_sockaddr.sin_port = htons(LAMBPORT);

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
        abort((stderr, " Couldnt create socket.\n "));

    if (connect(socket_fd, (struct sockaddr *) & server_sockaddr, sizeof (server_sockaddr)) < 0) {
        (void) close(socket_fd);
        abort((stderr, " Couldn't connect to socket %d.\n", errno));
    }

    printf("Connected OK, so it would seem\n");
    
    printf("which poem would you like to print\n");
    int poemprint;
    scanf("%d",poemprint);
    fflush(poemprint);

    while ((result = read(socket_fd, textin, sizeof (textin))) != 0)
        write(1, textin, result);
    return (EXIT_SUCCESS);
}


