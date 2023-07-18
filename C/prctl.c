// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/prctl.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>

// int main(void)
// {
//     int *status;
//     int i=0;

//     prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0);
//     //perror("PARENT:Set");
//     printf("PARENT: %d :  my dad : %d\n", getpid(), getppid());
//     if(fork() != 0)
//     {
//         while(1)
//         {
//             wait(status);
//             if(++i == 2)
//             {
//                 break;
//             }
//         }
//         int p = 1;
//         prctl(PR_GET_CHILD_SUBREAPER, &p);
//         printf("PARENT : %d\n",p);
//         printf("PARENT terminated\n");
//     }
//     else
//     {
//         printf("Before CHILD: %d: my dad  %d\n",getpid(), getppid());
//         if(fork() == 0)
//         {
//             int p = 1;
//             printf("Before grandchild: %d: my dad %d\n",getpid(), getppid());
//             sleep(2);
//             printf("After grandchild: %d: my dad %d\n",getpid(), getppid());
//             prctl(PR_GET_CHILD_SUBREAPER, &p);
//             printf("After grandchild : %d\n",p);
//             printf("Grandchild terminated\n");
//             exit(0);
//         }
//         else
//         {
//             int p = 1;
//             prctl(PR_GET_CHILD_SUBREAPER, &p);
//             printf("After CHILD : %d\n",p);
//             printf("After CHILD: %d: my dad  %d\n",getpid(), getppid());
//             printf("CHILD terminated\n");
//             exit(1);
//         }
//     }   
//     return 0;
// }



#include <stdio.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Make a grandchild process, which sleep(2)s and then exits
int doGrandchild(void) {
    int pid;
    if ((pid = fork()) != 0) {
        return pid;
    }
    
    printf("    GRANDCHILD(%d): before sleep, parent is %d\n", getpid(), getppid());
    sleep(2);   // Wait for CHILD to report and exit
    printf("    GRANDCHILD(%d): after sleep, parent is %d\n", getpid(), getppid());
    
    printf("    GRANDCHILD(%d): exiting\n", getpid());
    exit(0);
    // Will never return
}

// Make a child process, which makes a grandchild process, sleep(1)s, and then exits
int doChild(void) {
    int pid;
    if ((pid = fork()) != 0) {
        return pid;
    }
    sleep(1);   // Wait for PARENT to report fork
    printf("  CHILD(%d): parent is %d\n", getpid(), getppid());
    
    pid = doGrandchild();
    printf("  CHILD(%d): forked grandchild %d\n", getpid(), pid);
    sleep(1);   // Wait for GRANDCHILD to report
    
    printf("  CHILD(%d): exiting\n", getpid());
    exit(0);    // Exit before GRANDCHILD exits
    // Will never return
}

// Wait for all child descendents to exit
void waitDescendents(void) {
    printf("PARENT(%d): waiting for descendents to exit\n", getpid());
    while(1) {
        // Wait for any descendant process to exit
        int pid = wait(NULL);
        if(pid == -1) {
            printf("PARENT(%d): no more descendants\n", getpid());
            break;
        } else {
            printf("PARENT(%d): pid %d exited\n", getpid(), pid);
        }
    }
}

// Run the test
int main(void) {
    int pid;

    printf("PARENT(%d): parent is %d\n", getpid(), getppid());
    
    prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0);
    printf("PARENT(%d): ===== Run test with CHILD_SUBREAPER set to 1 =====\n", getpid());
    
    pid = doChild();
    printf("PARENT(%d): forked child %d\n", getpid(), pid);
    waitDescendents();
    
    prctl(PR_SET_CHILD_SUBREAPER, 0, 0, 0, 0);
    printf("PARENT(%d): ===== Run test with CHILD_SUBREAPER set to 0 =====\n", getpid());
    
    pid = doChild();
    printf("PARENT(%d): forked child %d\n", getpid(), pid);
    waitDescendents();
    
    printf("PARENT(%d): ===== Exiting =====\n", getpid());
    return 0;
}
