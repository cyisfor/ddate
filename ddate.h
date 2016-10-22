#include "config.h"
#include <time.h>
struct disc_time {
    int season; /* 0-4 */
    int day; /* 0-72 */
    int yday; /* 0-365 */
    int year; /* 3066- */
};

struct disc_time disc_fromtm(struct tm* tim);
struct disc_time disc_fromtm(time_t tim);
struct disc_time disc_convert(int,int);
struct disc_time disc_makeday(int,int,int);
int disc_format(char *buf, int len, const char* fmt, struct disc_time dt);


