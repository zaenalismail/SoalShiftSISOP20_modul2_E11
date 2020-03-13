#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  pid_t pid, sid;        // Variabel untuk menyimpan PID
  pid = fork();     // Menyimpan PID dari Child Process
  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }
  umask(0);
  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  char min, sec, hour;
  char *cmd[] = {"bash", argv[4], NULL};

    if(argc>=4){
      printf("Error\n");
      return 0;
    }
    if(atoi(argv[1])<0 || atoi(argv[1])>59 || argv[1] != "\\*"){
      printf("Error\n");
      return 0;
    }

    if(argv[1] == "\\*"){
      sec = '*';
    }
    else{
      sec = atoi(argv[1]);
    }
    
    if(atoi(argv[2])<0 || atoi(argv[2])>59 || argv[2] != "\\*"){
      printf("Error\n");
      return 0;
    }
    if(argv[2] == "\\*"){
      min = '*';
    }
    else{
      min = atoi(argv[2]);
    }
    if(atoi(argv[3])<0 || atoi(argv[3])>23 || argv[3] != "\\*"){
      printf("Error\n");
      return 0;
    }
    if(argv[3] == "\\*"){
      hour = '*';
    }
    else{
      hour = atoi(argv[3]);
    }

  time_t now;
  struct tm *now_tm;
  int currh, currm, currs;

  now = time(NULL);
  now_tm = localtime(&now);
  currh = now_tm->tm_hour;
  currm = now_tm->tm_min;
  currs = now_tm->tm_sec;

  if(sec=='*'&&min!='*'&&hour!='*'){
    while (hour==currh && min==currm) {

    execv("/bin/bash",cmd);
    
    sleep(1);
    }
  }
  else if(min=='*'&&sec!='*'&&hour!='*'){
    while (hour==currh && sec==currs) {

    execv("/bin/bash",cmd);
    
    sleep(60);
    }
  }
  else if(hour=='*'&&sec!='*'&&min!='*'){
    while (min==currm && sec==currs) {

    execv("/bin/bash",cmd);
    
    sleep(3600);
    }
  }
  else if(min=='*'&&sec=='*'&&hour!='*'){
    while (hour==currh) {

    execv("/bin/bash",cmd);
    
    sleep(1);
    }
  }
  else if(min=='*'&&sec!='*'&&hour=='*'){
    while (sec==currs) {

    execv("/bin/bash",cmd);
    
    sleep(3660);
    }
  }
  else if(min!='*'&&sec=='*'&&hour=='*'){
    while (min==currm) {

    execv("/bin/bash",cmd);
    
    sleep(3601);
    }
  }
  else if(min=='*'&&sec=='*'&&hour=='*'){
    while (1) {

    execv("/bin/bash",cmd);
    
    sleep(1);
    }
  }
  return 0;
}
