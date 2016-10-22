/* $ DVCS ID: $jer|,523/lhos,KYTP!41023161\b"?" <<= DO NOT DELETE! */

/* ddate.c .. converts boring normal dates to fun Discordian Date -><-
   written  the 65th day of The Aftermath in the Year of Our Lady of 
   Discord 3157 by Druel the Chaotic aka Jeremy Johnson aka
   mpython@gnu.ai.mit.edu  
   28 Sever St Apt #3
   Worcester MA 01609

   and I'm not responsible if this program messes anything up (except your 
   mind, I'm responsible for that)

   (k) YOLD 3161 and all time before and after.
   Reprint, reuse, and recycle what you wish.
   This program is in the public domain.  Distribute freely.  Or not.

   Majorly hacked, extended and bogotified/debogotified on 
   Sweetmorn, Bureaucracy 42, 3161 YOLD, by Lee H:. O:. Smith, KYTP, 
   aka Andrew Bulhak, aka acb@dev.null.org

   and I'm not responsible if this program messes anything up (except your 
   mind, I'm responsible for that) (and that goes for me as well --lhos)

   Version history:
   Bureflux 3161:      First release of enhanced ddate with format strings
   59 Bcy, 3161:       PRAISE_BOB and KILL_BOB options split, other minor
   changes.

   1999-02-22 Arkadiusz Miskiewicz <misiek@pld.ORG.PL>
   - added Native Language Support

   2000-03-17 Burt Holzman <bnh@iname.com>
   - added range checks for dates
   */

#include "ddate.h"

#include <stdlib.h> // srandom, atoi, strtol, exit
#include <string.h> // strrchr
#include <time.h> // time, gmtime, struct tm
#include <stdio.h> // printf, stderr, fprintf

// work around includes and defines from formerly nls.h

#include <libintl.h> // bindtextdomain, textdomain

#define LOCALEDIR "/usr/share/locale"

/* work around hacks for standalone package */
#define PACKAGE "ddate"
#define PACKAGE_STRING "Stand Alone"

char *default_immediate_fmt=
#ifdef OLD_IMMEDIATE_FMT
"Today is %{%A, the %e day of %B%} in the YOLD %Y%N%nCelebrate %H"
#else
NULL
#endif
;

int
main (int argc, char *argv[]) {
    long t;
    struct tm *eris;
    int bob,raw;
    struct disc_time hastur;
    char schwa[23*17], *fnord=0;
    int pi;
    char *progname, *p;

    progname = argv[0];
    if ((p = strrchr(progname, '/')) != NULL)
        progname = p+1;

    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    srandom(time(NULL));
    /* do args here */
    for(pi=1; pi<argc; pi++) {
        switch(argv[pi][0]) {
            case '+': fnord=argv[pi]+1; break;
            case '-': 
                switch(argv[pi][1]) {
                    case 'V':
                        printf(("%s (%s)\n"), progname, PACKAGE_STRING);
                    default: goto usage;
                }
            default: goto thud;
        }
    }

thud:
    if (argc-pi==3){ 
        int moe=atoi(argv[pi]), larry=atoi(argv[pi+1]), curly=atoi(argv[pi+2]);
        hastur=disc_makeday(
#ifdef US_FORMAT
                moe,larry,
#else
                larry,moe,
#endif
                curly);
        if (hastur.season == -1) {
            printf("Invalid date -- out of range\n");
            return -1;
        }
        fnord=fnord?fnord:default_fmt;
    } else {
        if (argc-pi==1) {
            t = strtol(argv[pi],NULL,10);
        } else if (argc!=pi) { 
usage:
#ifdef US_FORMAT
            fprintf(stderr,("usage: %s [+format] [month day year] you bloody yanks\n"), argv[0]);
#else
            fprintf(stderr,("usage: %s [+format] [day month year]\n"), argv[0]);
#endif
            fprintf(stderr,("alsousage: %s [+format] [timestamp]\n"), argv[0]);
            exit(1);
        } else {
            t= time(NULL);
        }
        eris=gmtime(&t);
        bob=eris->tm_yday; /* days since Jan 1. */
        raw=eris->tm_year; /* years since 1980 */
        hastur=disc_convert(bob,raw);
        fnord=fnord?fnord:default_immediate_fmt;
    }
    if(0!=disc_format(schwa, 23*17, fnord, hastur)) {
			puts("truncated");
		}
	
    printf("%s\n", schwa);

    return 0;
}
