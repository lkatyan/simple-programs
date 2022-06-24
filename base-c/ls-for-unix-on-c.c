#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void dirout(DIR *cdir, char *patg);

int main(int argc, char *argv[])
{
char s1[10]="-l";
char s2[10]="-r";
struct dirent *entry;
char var[100]="/home";
DIR* dir=opendir("/home");
setlocale(LC_ALL, "");


if (argc==1) {
	entry=readdir(dir);
		while (entry!=NULL) {
			printf("%s \n", entry->d_name);
			entry=readdir(dir);
		}
	}
else {
	if (strcmp (argv[1], s1)==0) {
		struct stat buf;
		int res;
		char *n = malloc(PATH_MAX);
		entry=readdir(dir);
		while (entry!=NULL) {
			res=stat(n, &buf);
			if (buf.st_mode)
				printf("%ld		", buf.st_size);
			printf("%ld		%d		%s \n",
				entry->d_ino, entry->d_reclen, entry->d_name);
			entry=readdir(dir);
			n=entry->d_name;
		}
	}
	else if (strcmp (argv[1], s2)==0) dirout(dir, var);
}
closedir(dir);
return 0;
}
void dirout(DIR *cdir, char *path) {
	DIR *hdir;
	char var[PATH_MAX];
	struct dirent *entry;
	int flag = 0;
	while ((entry=readdir(cdir))!=NULL) {
		sprintf(var,"%s/%s",path,entry->d_name);
		hdir=opendir(var);
		if (errno == ENOTDIR)
			printf ("%s\n", entry->d_name);
		else {
			dirout(hdir, var);
			flag=1;
		}
	}
	if (flag==1) closedir(hdir);
}
