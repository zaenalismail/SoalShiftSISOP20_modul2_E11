# SoalShiftSISOP20_modul2_E11

## Kelompok
- Ammar Alifian Fahdan (05111840000007)
- Zaenal Mahmudi Ismail (05111840000054)

## Pembahasan Soal

### Soal 1

**Deskripsi**

Membuat program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:
**a.** Program menerima 4 argumen berupa:
    i. Detik: 0-59 atau * (any value)
    ii. Menit: 0-59 atau * (any value)
    iii. Jam: 0-23 atau * (any value)
    iv. Path file .sh
**b.** Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai
**c.** Program hanya menerima 1 config cron
**d.** Program berjalan di background (daemon)
**e.** Tidak boleh menggunakan fungsi system()

**Penjelasan Script**

Membuat daemon dari template
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
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

  while (1) {
    // Tulis program kalian di sini

    sleep(30);
  }
}
```
Eksepsi ketika argumen tidak sesuai
```
if(argc>=4){
      printf("Error\n");
      return 0;
    }
```
Menyimpan tiap argumen dalam variable
```
char min, sec, hour;
  char *cmd[] = {"bash", argv[4], NULL};
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
```
Menyimpan waktu untuk menjalankan daemon dalam variable yang nantinya akan dibuat kondisi kapan program akan dijalankan
```
  time_t now;
  struct tm *now_tm;
  int currh, currm, currs;

  now = time(NULL);
  now_tm = localtime(&now);
  currh = now_tm->tm_hour;
  currm = now_tm->tm_min;
  currs = now_tm->tm_sec;
```
Kondisi - kondisi yang mungkin untuk menjalankan program
```
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
```
### Soal 2

**Deskripsi**

**Penjelasan Script**

### Soal 3

**Deskripsi**

**Penjelasan Script**
