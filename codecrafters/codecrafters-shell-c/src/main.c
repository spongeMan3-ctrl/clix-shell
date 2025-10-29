#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <dirent.h>
#include <sys/stat.h> 

#define MKDIR_PREFIX 6

#define RMDIR_PREFIX 6

#define ECHO_PREFIX 5

#define CD_PREFIX 3

#define TOUCH_PREFIX 6

#define RM_PREFIX 3

#define CAT_PREFIX 4

void display_clix_logo(void) {
    printf("\n");
    printf("   \033[1m\033[92m  CCCC   L    I  X   X\033[0m\n");
    printf("   \033[1m\033[92m C    C  L    I   X X\033[0m\n");
    printf("   \033[1m\033[92m C       L    I    X\033[0m\n");
    printf("   \033[1m\033[92m C    C  L    I   X X\033[0m\n");
    printf("   \033[1m\033[92m  CCCC   LLLL I  X   X\033[0m\n");
    printf("\n");
}

void display_info(void) {
   printf("   \033[1m\033[97mCLIX: C Linux/UNIX Shell Interface\033[0m\n");
   printf("   \033[1m\033[97mversion 1.0 beta 2025\033[0m\n");
}


void p(const char *s) {
    printf("%s", s);
}



void help(void) {
    p("help:\n");
    p(" exit [[0 flase],[1 true]] close clix\n");
    p(" echo [text] display a line of text\n");
    p(" pwd shows your directory\n");
    p(" clear clean your RootWay\n");
    p(" cd [.. back one directory] [~ back to $HOME] [your PATH]\n");
    p(" clix displays CLIX ANSI\n");
    p(" version [-v -ver] shows your version of clix\n");
    p(" touch [file name] create new file in directory\n");
    p(" rm [file name] felate FILE [not folder]\n");
    p(" ls shows info about oyur directory\n");
    p(" mkdir [folder name] create folder\n");
    p(" rmdir [folder name] delate folder with no files\n");
    p(" cat [file name] shows file content\n");

}


char *get_line() {

  char *line = NULL;
  size_t len = 0;

  size_t bytes_Read = getline(&line, &len, stdin);

  if(bytes_Read < 0) {
    perror("error");
    exit(-1);
  }

  line[bytes_Read - 1] = '\0';

  return line;
}

int main(int argc, char *argv[]) {

  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  
  while(1) {
    printf("\033[32m$\033[0m "); // ansi $ dg
    
    char *line = get_line();

    if(strcmp(line, "exit 0") == 0 || strcmp(line, "exit 1") == 0)
     exit(0);

    else if(strcmp(line, "help") == 0){
      help();
    }
    else if(strncmp(line, "rm ", RM_PREFIX) == 0) {
      char *filename = line + RM_PREFIX;

      if(remove(filename) == 0) {

      }else {
        perror("rm error");
      }
    }
    else if(strncmp(line, "mkdir ", MKDIR_PREFIX) == 0) {
    	char *dirname = line + MKDIR_PREFIX;

	    if(mkdir(dirname, 0777) == 0) { //0777 full perm 100%
	  
      }
      else{
		  perror("mkdir error");
    }
	}

    else if(strcmp(line, "ls") == 0 ) {

      DIR *d;
      struct dirent *dir;
      
      d = opendir(".");

      if(d) {
      while((dir = readdir(d)) != NULL) {
        printf("%s  ", dir->d_name);
      }
      closedir(d);

      printf("\n");
    }else {
      perror("ls error");
    }

      
    }
    else if(strncmp(line, "touch ", TOUCH_PREFIX) == 0) {
      char *filename = line + TOUCH_PREFIX;
      FILE *file = fopen(filename, "w");

      if(file == NULL) {
        perror("touch error");
      }else {
        fclose(file);
      }
    }
    else if(strcmp(line, "clix") == 0) {
      display_clix_logo();
    }
    else if(strncmp(line, "cat ", CAT_PREFIX) == 0) {
      char *filename = line + CAT_PREFIX;
      FILE *file = fopen(filename, "r");
      int x;

      if(file == NULL) {
        perror("cat error");
      }else {
        while ((x = fgetc(file)) != EOF) { //-1
          putchar(x);
        }
        fclose(file);
      }
    }
    else if(strncmp(line, "rmdir ", RMDIR_PREFIX) == 0) {
      char *dirname = line + RMDIR_PREFIX;

      if(rmdir(dirname) == 0) {

      }else {
        perror("rmdir error");
      }
    }
    else if(strcmp(line, "version") == 0 || strcmp(line, "-v") == 0 || strcmp(line, "-ver") == 0) {
      display_info();
    }
    else if(strcmp(line, "clear") == 0) {
      printf("\033[H\033[J"); //ANSI
    }
    else if(strncmp(line, "echo ", ECHO_PREFIX) == 0) {
        char *text = line + ECHO_PREFIX;
        printf("%s\n", text);
        if(strcmp(line, "echo ") == 0){
          printf("echo: enter after echo min one char\n");
        }
    }
      else if(strcmp(line, "pwd") == 0) {
        char buff[2048];
          if(getcwd(buff, sizeof(buff))) {
            printf("%s\n", buff);
          }else{
            perror("pwd error");
          }
      }
      else if (strncmp(line, "cd", 2) == 0) {
      char *path = NULL;

      if (strcmp(line, "cd") == 0 || strcmp(line, "cd ~") == 0) {
          
          path = getenv("HOME");
          if (path == NULL) {
              fprintf(stderr, "cd error: HOME not set.\n");
          }
      } 
      else if (strcmp(line, "cd ..") == 0) {
          path = "..";
      }
      else if (strncmp(line, "cd ", CD_PREFIX) == 0) { 
          path = line + CD_PREFIX;
      }
    
      if (path != NULL) {
          if (chdir(path) != 0) {
              perror("cd error"); 
          }
      } else if (line[2] != '\0' && line[2] != ' ') {
          //cda cdarom soon.
      }
  }

    else if(line){
      printf("%s: command not found\n", line);
    }

    free(line); 


    
 
  }
  
  return 0;
}
//happy coding!