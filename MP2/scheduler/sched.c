/* Copyright (c) 2013 Pablo Oliveira <pablo.oliveira@prism.uvsq.fr>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.  All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "sched.h"
/* Compile the task descriptions */
#include "task_description.h"
#include <math.h>

/* --Scheduler random--*/
tproc * randomscheduler(tlist * procs, tlist * ready, int * delta) {
    int length = len(ready);
    int selected = rand()%length;
    tnode * p = ready->first;
    for (int i=0; i < selected; i++) {
        p = p->next;
    }
    *delta = rand()%p->proc->remaining + 1;
    return p->proc;
}
/* --Scheduler random--*/

/* --Scheduler fcfs-- */
tproc * fcfs(tlist * procs, tlist * ready, int * delta) {
    /* Premier arrive pemier servi (FIFO) */
    tnode * p = ready->first;
    *delta = p->proc->remaining;
    return p->proc;
}
/* --Scheduler fcfs-- */

/* --Scheduler rr-- */
tproc * rr(tlist * procs, tlist * ready, int * delta) {
    /* Ordonnancement en Tourniquet */
    tnode * p = ready->first;
    if (q > p->proc->remaining) {
      *delta = p->proc->remaining;
    }
    else
    {
      *delta = q;
    }

    add(procs, p->proc);
    del(ready, p->proc);
    return procs->last->proc;
}
/* --Scheduler rr-- */

/* --Scheduler sjf-- */
tproc * sjf(tlist * procs, tlist * ready, int * delta) {
    /* Shortest Job First */
    tnode * p = ready->first;
    tnode * min = ready->first;
    for (int i=0; i < len(ready);i++) {
      if (p->proc->remaining < min->proc->remaining) {
        min = p;
      }
      p = p->next;
    }
    *delta = min->proc->remaining;
    return min->proc;
}
/* --Scheduler sjf-- */

/* --Scheduler srtf-- */
tproc * srtf(tlist * procs, tlist * ready, int * delta) {
    /* Shortest Reamining Time First */
    tnode * p = ready->first;
    tnode * min = ready->first;
    for (int i=0; i < len(ready);i++) {
      if (p->proc->remaining < min->proc->remaining) {
        min = p;
      }
      p = p->next;
    }
    *delta = 1;
    return min->proc;
}
/* --Scheduler srtf-- */

/* --Scheduler rm-- */
tproc * rm(tlist * procs, tlist * ready, int * delta) {
  /* monotonic analysis */
  tnode * p = ready->first;
  tnode * min = ready->first;
  for (int i=0; i < len(ready);i++)
  {
    if ((p->proc->period) < (min->proc->period))
    {
        min = p;
    }
    p = p->next;
  }
  *delta = 1;
  return min->proc;
}
/* --Scheduler rm-- */

/* --Scheduler edf-- */
tproc * edf(tlist * procs, tlist * ready, int * delta) {
  /* Earliest Deadline First */
  tnode * p = ready->first;
  tnode * min = ready->first;
  for (int i=0; i < len(ready);i++) {
    if ((p->proc->activation + p->proc->period) < (min->proc->activation + min->proc->period)) {
      min = p;
    }
    p = p->next;
  }
  *delta = 1;
  return min->proc;
}
/* --Scheduler edf-- */

/* List of ready procs */
tlist ready;

/* List of other procs */
tlist procs;

/* The selected scheduler */
tscheduler scheduler;

/* The scheduling statistics */
tstats stats = {0} ;

/* display usage message */
void usage() {
    fail("usage: sched [fcfs, rr, sjf, srtf, rm, edf]\n");
}

/* simulate a single core scheduler, from time 0 to `max_time` */
void simulate(int max_time)
{
    int time=0;
    while(time < max_time)
    {
        /* Activate process */
        for (tnode * p = procs.first; p != NULL;) {
            tproc * proc = p->proc;
            p = p->next;

            /* Move every process which should be activated,
             * from the procs list to the ready list */
            if (proc->activation <= time)
            {
                del(&procs, proc);
                add(&ready, proc);
            }
        }

        /* If any process is ready, then we can schedule! */
        if (ready.first != NULL) {

            int delta = 0;
            /* Call the scheduler */
            tproc * proc = scheduler(&procs, &ready, &delta);

            /* Ensure the scheduler has advanced at least one unit of time */
            assert(delta > 0);


            if (scheduler == rm || scheduler == edf){
              if (time + delta > (proc->activation + proc->period)) {
                /* Output task execution qui ne satisfont pas leurs echeances */
                printf("\\TaskExecution[color=red]{%d}{%d}{%d}\n", proc->pid, time, time+delta);
              }
              else
              {
                /* Output task execution */
                printf("\\TaskExecution{%d}{%d}{%d}\n", proc->pid, time, time+delta);
              }
            }
            else
            {
              /* Output task execution */
              printf("\\TaskExecution{%d}{%d}{%d}\n", proc->pid, time, time+delta);
            }

            if (proc->length == proc->remaining) {
              stats.response += time - proc->activation ;
            }
            /* Advance time by delta */
            time += delta;
            /* Remove delta from chosen process */
            proc->remaining-=delta;
            /* If the process remaining time is less zero or less,
             * delete it */
            if (proc->remaining <= 0) {


                if (scheduler == rm || scheduler == edf) {

                  /* Le simulateur comptabilise le temps total de complétion */
                  stats.completion += time - proc->activation;
                  /* Le simulateur comptabilise le temps total de waitting */
                  stats.waiting += time - proc->activation - proc->length;

                  proc->activation += proc->period;
                  proc->remaining = proc->length;


                  del(&procs, proc);
                  add(&procs, proc);
                  del(&ready, proc);

                }
                else
                {
                  /* Le simulateur comptabilise le temps total de complétion */
                  stats.completion += time - proc->activation;
                  /* Le simulateur comptabilise le temps total de waitting */
                  stats.waiting += time - proc->activation - proc->length;
                  del(&procs, proc);
                  del(&ready, proc);
                }
            }
        }
        /* If no process is ready, just advance the simulation timer */
        else {

            time += 1;
        }

    }
}

int main(int argc, char * argv[]) {

    /* Parse arguments */
    if (argc != 2) usage();

    /* Seed random number generator */
    srand(time(NULL) ^ getpid());

    char * method = argv[1];

    /* Utilisation du cpu */
    // float u;
    /* Utilisation du cpu pour rm */
    // float u_rm;
    //
    // float n = sizeof(tasks)/sizeof(tproc);

    /* The sched argument should be one of fcfs, rr, sjf, srtf */
    if (strcmp(method, "fcfs") == 0) {
        scheduler = fcfs;
    }
    else if (strcmp(method, "rr") == 0) {
        scheduler = rr;
    }
    else if (strcmp(method, "sjf") == 0) {
        scheduler = sjf;
    }
    else if (strcmp(method, "srtf") == 0) {
        scheduler = srtf;
    }
    else if (strcmp(method, "rm") == 0) {
        scheduler = rm;
        // u_rm = n*(pow(2,(1/n))-1);
    }
    else if (strcmp(method, "edf") == 0) {
        scheduler = edf;
    }
    else {
        usage();
    }

    /* Add all tasks to the procs queue */
    for(int i = 0; i < sizeof(tasks)/sizeof(tproc); i ++) {
        add(&procs, &(tasks[i]));
        /* Utilisation du cpu au maximum de 100% */
        // if (scheduler == rm || scheduler == edf) {
        //   u += (float)(tasks[i].length/(float)tasks[i].period);
        //   if (u > 1) {
        //     usage();
        //   }
        //   // else if(u > u_rm && scheduler == rm )
        //   // {
        //   //
        //   // }
        // }
    }
    // printf("%.2f < %.2f\n\n\n",u_rm,u );

    /* Output RTGrid header */
    printf("\\begin{RTGrid}[width=0.8\\textwidth]{%d}{%d}\n", len(&procs), max_time);

    /* Output task arrivals for all tasks */
    for (tnode * p = procs.first; p != NULL; p = p->next) {
        printf("\\TaskArrival{%d}{%d}\n", p->proc->pid, p->proc->activation);
    }

    /* Start scheduling simulation */
    simulate(max_time);

    /* Close RTGrid environment */
    printf("\\end{RTGrid}\\newline\\newline\n");

    /* Print statistics */
    printf("Total completion time = %d\\newline\n", stats.completion);
    printf("Total waiting time = %d\\newline\n", stats.waiting);
    printf("Total response time = %d\\newline\n", stats.response);

    /* Empty the lists if needed */
    del_all(&ready);
    del_all(&procs);

    return 0;
}
