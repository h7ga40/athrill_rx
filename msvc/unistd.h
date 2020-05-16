#ifndef _UNISTD_H_
#define _UNISTD_H_

extern int opterr;
extern int optind;
extern int optopt;
extern int optreset;
extern char *optarg;

int getopt(int nargc, char * const nargv[], const char *ostr);

#endif // _UNISTD_H_
