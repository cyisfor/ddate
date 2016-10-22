#include "ddate.h"
#include <stdio.h>
int main(void)
{
	struct disc_time disc = disc_fromtime(time(NULL));

	char default_fmt[] = "%{%A, %B %d%}, %Y YOLD";
	char buf[0x100];
	ssize_t amt = disc_format(buf,0x100,default_fmt,disc);
	fwrite(buf,amt,1,stdout);
	fputc('\n',stdout);
	return 0;
}
