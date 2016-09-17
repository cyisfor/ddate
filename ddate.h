struct disc_time {
    int season; /* 0-4 */
    int day; /* 0-72 */
    int yday; /* 0-365 */
    int year; /* 3066- */
};

struct disc_time disc_convert(int,int);
struct disc_time disc_makeday(int,int,int);
void disc_format(char *buf, const char* fmt, struct disc_time dt);
int disc_xday_countdown(int yday, int year);
