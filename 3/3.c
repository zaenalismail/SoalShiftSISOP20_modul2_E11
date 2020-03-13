#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>

int _check_existence(char* lokasi){
	if(access(lokasi, F_OK) != -1){
		return 1;
	}else{
		return 0;
	}
}

void pindah(char* lokasi, int flag){
	char lokasi_new[] = "/home/kerupuksambel/modul2/jpg/";
	strcat(lokasi_new, lokasi);
	if(_check_existence(lokasi_new)){
		pid_t child2 = fork();
		int flag_do = 0, s;
		if(child2 == 0){
			if(flag == 4){
				//merupakan direktori
				if(strcmp(lokasi, ".") != 0 && strcmp(lokasi, "..") != 0){
					strcat(lokasi_new, "/");
					char* arg[] = {"mv", lokasi_new, "/home/kerupuksambel/modul2/indomie", NULL};
					execv("/bin/mv", arg);
					// pid_t child3 = fork();
				}
			}else{
				//merupakan file
				char* arg[] = {"mv", lokasi_new, "/home/kerupuksambel/modul2/sedaap", NULL};
				execv("/bin/mv", arg);
			}
		}else{
			while ((wait(&s)) > 0);
			if(!_check_existence(lokasi_new)){
				printf("File sudah dipindah.\n");
			}else{

			}
		}
	}else{
		exit(EXIT_SUCCESS);
	}
}

// void buat(char* lokasi){
	
// }

void buat(char* lokasi){
	// char lokasi_new[] = "/home/kerupuksambel/modul2/indomie/";
	// strcat(lokasi_new, lokasi);
	if(strcmp(lokasi, ".") != 0 && strcmp(lokasi, "..") != 0){
		pid_t before_make = fork();
		int st2;
		if(before_make == 0){
			pid_t child_make = fork();
			int st;

			if(child_make == 0){
				char nama_1[] = "/home/kerupuksambel/modul2/indomie/";
				strcat(nama_1, lokasi);
				strcat(nama_1, "/coba1.txt");
				char* arg[] = {"touch", nama_1, NULL};
				execv("/usr/bin/touch", arg);
			}else{
				while ((wait(&st)) > 0);
				sleep(3);
				char nama_2[] = "/home/kerupuksambel/modul2/indomie/";
				strcat(nama_2, lokasi);
				strcat(nama_2, "/coba2.txt");
				char* arg2[] = {"touch", nama_2, NULL};
				execv("/usr/bin/touch", arg2);
			}
		}else{
			while ((wait(&st2)) > 0);
			printf("Terbentuk!\n");
			// exit(EXIT_SUCCESS);
		}
	}else{
	}
}

int main() {
	int status_f;
	pid_t child_f = fork();

	if (child_f < 0) {
		exit(EXIT_FAILURE);
	}

	if (child_f == 0){
		int status;
		pid_t child_id = fork();

		if (child_id < 0) {
			exit(EXIT_FAILURE);
		}

		if (child_id == 0) {
			pid_t child_sedaap = fork();

			if (child_sedaap < 0) {
				exit(EXIT_FAILURE);
			}

			if (child_sedaap == 0){
				char* arg[] = {"mkdir", "/home/kerupuksambel/modul2/indomie", NULL};
				execv("/bin/mkdir", arg);
			}else{
				sleep(5);
				char* arg2[] = {"mkdir", "/home/kerupuksambel/modul2/sedaap", NULL};
				execv("/bin/mkdir", arg2);
			}
		} else {
			while ((wait(&status)) > 0);
			char* arg[] = {"unzip", "/home/kerupuksambel/modul2/jpg.zip", "-d", "/home/kerupuksambel/modul2/", NULL};
			execv("/usr/bin/unzip", arg);
		}
	}else{
		while ((wait(&status_f)) > 0);
		pid_t child_id_2 = fork();
		int status_2;

		if (child_id_2 < 0) {
			exit(EXIT_FAILURE);
		}

		if (child_id_2 == 0){
			DIR *dp;
			struct dirent *ep;     
			dp = opendir ("/home/kerupuksambel/modul2/jpg/");

			if (dp != NULL){
				while (ep = readdir (dp)){
					pindah(ep->d_name, ep->d_type);
				}
				(void) closedir (dp);
			}
		}else{
			while ((wait(&status_2)) > 0);
			printf("done\n");
			DIR *dp2;
			struct dirent *ep2;     
			dp2 = opendir ("/home/kerupuksambel/modul2/indomie/");

			if (dp2 != NULL){
				while (ep2 = readdir (dp2)){
					buat(ep2->d_name);
				}
				(void) closedir (dp2);
			}
		}
	}
}