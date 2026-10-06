#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * Executes the command "cat scores | grep Lakers".  In this quick-and-dirty
 * implementation the parent doesn't wait for the child to finish and
 * so the command prompt may reappear before the child terminates.
 *
 */

int main(int argc, char **argv)
{
  int pipefd[2];
  int pipefd2[2];
  int pid;
  int pid2;
  int pid3;

  if (argc != 2){
    fprintf(stderr, "usage: %s ,grep_argument>\n", argv[0]);
  }

  char *cat_args[] = {"cat", "scores", NULL};
  char *grep_args[] = {"grep", argv[0], NULL};
  char *sort_args[] = {"sort", NULL};

  // make a pipe (fds go in pipefd[0] and pipefd[1])

  pipe(pipefd);
  pipe(pipefd2);

  pid = fork();

  if (pid == 0)
    {
      // child gets here and handles "grep Villanova"
      pid2 = fork();

      if (pid2 == 0){
        dup2(pipefd2[0], 0);

        close(pipefd[0]);
        close(pipefd[1]);
        close(pipefd2[0]);
        close(pipefd2[1]);

        execvp("sort", sort_args);
        exit(1);
      } else{
        dup2(pipefd[0], 0);
        dup2(pipefd2[1],1);

        close(pipefd[0]);
        close(pipefd[1]);
        close(pipefd2[0]);
        close(pipefd2[1]);
        execvp("grep", grep_args);
        exit(1);

      }
      // replace standard input with input part of pipe

      

      // close unused hald of pipe

    

      // execute grep

     
    }
  else
    {
      // parent gets here and handles "cat scores"

      // replace standard output with output part of pipe

      dup2(pipefd[1], 1);

      // close unused unput half of pipe

      close(pipefd[0]);
      close(pipefd[1]);
      close(pipefd2[0]);
      close(pipefd2[1]);


      // execute cat

      execvp("cat", cat_args);
    }
}