#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>

int main(){

    utsname buf;
    uname(&buf);
    
    printf("Operating system name: %s \n", buf.sysname);
    printf("Name within 'some implementation-defined network': %s \n", buf.nodename);
    printf("Operating system realease: %s \n", buf.release);
    printf("Operating system version: %s \n", buf.version);
    printf("Hardware identifier: %s \n", buf.machine);
    printf("NIPS or YP domain name: %s \n", buf.domainname);

    return 1;
}
