#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <dirent.h>
#include <string.h>

#define  BUFFER 300

int  main(int argc , char *argv [])
{
	char  cwd[BUFFER];
	getcwd(cwd, BUFFER);

	DIR* dir = opendir(cwd);
	struct dirent *entry;
	char buffer[BUFFER];

	while ((entry = readdir(dir)) != NULL){
		struct stat sb;
		
		//Output of this is always 10 - 265? Double check wot dat means
		snprintf(buffer, BUFFER , "/home/philfish/ArchSummutiveC/%s", entry->d_name );
		
		stat(buffer , &sb);
		

		//Filter stuff not in -ls
		if (!strncmp(entry->d_name, ".", 1) || !(S_ISDIR(sb.st_mode) || S_ISREG(sb.st_mode))){
			puts("IGNORED");
		}
		else {
			puts(entry->d_name);
			
			if (S_ISDIR(sb.st_mode) == 0){
				putc('d', stdout);
			}
			else {
				putc('-', stdout);
			}

			printf("%lo", (unsigned long)sb.st_mode);


			putc('\n', stdout);
		}
	}
	closedir(dir);	

	return  EXIT_SUCCESS;
}

