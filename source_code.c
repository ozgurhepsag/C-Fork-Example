#include <sys/types.h> 
#include <errno.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h> 

int main(void)
{
    int n1 = fork(); //Creation of CH1
    int n2 = fork(); //Creation of CH2 and CH4

    if(n1 == -1 || n2 == -1)
    {
        // When failure occurs fork() returns -1.
        printf("fork() failed.");
        return (-1);
    }
    else if (n1 > 0 && n2 > 0) //P1
    {
        printf("Parent process ID: %d \n", getpid(), getppid());

        wait(NULL); // Parent is waiting CH1 and CH2 with these two "wait(NULL)".
        wait(NULL); // Reason of the using two "wait" is that "wait" is waiting for just a child process.  

        int n3 = fork(); // Creation of CH3

        if(n3 == -1)
        {
            printf("fork() failed.");
            return (-1);
        }
        else if(n3 == 0) // CH3
        { 
            int parent = getppid();

            printf("3rd child process ID: %d (parent: %d) \n", getpid(), parent);
            
            FILE * fp;
            fp = fopen ("opSys.txt", "r+");

            int key;

            fscanf(fp, "%d", &key);
            fclose(fp);

            printf("trying key: %d\n", key);

            if(key == parent)
                printf("matched...\n");
            else
                printf("not matched...\n");
            
        }
        else // P1
        { 
            wait(NULL); // Parent is waiting CH3 to complete.
            printf("Parent process ID: %d (parent: %d) \n", getpid(), getppid());
            printf("program finished...\n");
        }
    }
    else if (n1 == 0 && n2 > 0) // CH1
    {
        int parent = getppid();

        sleep(1); // Used sleep() to specify order of the child processes. 
        
        printf("1st child process ID: %d (parent: %d) \n", getpid(), parent);

        FILE * fp;
        fp = fopen ("opSys.txt", "w+");
        fclose(fp);

        printf("file was created...\n");
    }
    else if (n1 > 0 && n2 == 0) // CH2
    { 
        int parent = getppid();
        int input;

        sleep(5);
        
        printf("2nd child process ID: %d (parent: %d) \n", getpid(), parent);
        printf("write the key: ");
        scanf("%d", &input);

        printf("trying: %d\n", input);

        FILE * fp;
        fp = fopen ("opSys.txt", "w+");
        fprintf(fp, "%d", input);
        fclose(fp);
    }
    else // CH4 (grandson)
    {
        int parent = getppid();

        sleep(3);

        printf("4th child process ID: %d (parent: %d) \n", getpid(), parent);
        printf("say me password...\n");
    }
    return (0);
}