#ifdef VERBOSE

#include <stdio.h>
#include <errno.h>
#define debug(fmt, ...) do{printf("\x1B[32mD: %s:%s:%d " fmt "\x1B[30;0m", __FILE__,__FUNCTION__,__LINE__, ##__VA_ARGS__);fflush(stdout);}while(0)
#define errout(fmt, ...) do{fprintf(stderr,"\x1B[31;1mE: %s:%s:%d " fmt "\x1B[30;0m", __FILE__,__FUNCTION__,__LINE__, ##__VA_ARGS__);fflush(stderr);}while(0)
/** set the return value of a system call to -1 and save in variable n. Also set errno to err*/
#define inject(n, err) do{ n =-1; errno = (err);}while(0);
#else
#define debug(fmt, ...)
#define errout(fmt, ...)
#endif

