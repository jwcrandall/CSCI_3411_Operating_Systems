#include <stdio.h>
#include <stdlib.h>

typedef struct { void * data; int pri; } q_elem_t;
typedef struct { q_elem_t *buf; int n, alloc; } pri_queue_t, *pri_queue;

#define priorityqueue_purge(q) (q)->n = 1
#define priorityqueue_size(q) ((q)->n - 1)





/* first element in array not used to simplify indices */
pri_queue priorityqueue_new(int size)
{
  if (size < 4) size = 4;

  pri_queue q = malloc(sizeof(pri_queue_t));
  q->buf = malloc(sizeof(q_elem_t) * size);
  q->alloc = size;
  q->n = 1;

  return q;
}





void priorityqueue_push(pri_queue q, void *data, int pri)
{
  q_elem_t *b;
  int n, m;

  if (q->n >= q->alloc) {
    q->alloc *= 2;
    b = q->buf = realloc(q->buf, sizeof(q_elem_t) * q->alloc);
  } else
    b = q->buf;

  n = q->n++;
  /* append at end, then up heap */
  while ((m = n / 2) && pri < b[m].pri) {
    b[n] = b[m];
    n = m;
  }
  b[n].data = data;
  b[n].pri = pri;
}




/* remove top item. returns 0 if empty. *pri can be null. */
void* priorityqueue_pop(pri_queue q, int *pri)
{
  void *out;
  if (q->n == 1) return 0;

  q_elem_t *b = q->buf;

  out = b[1].data;
  if (pri) *pri = b[1].pri;

  /* pull last item to top, then down heap. */
  --q->n;

  int n = 1, m;
  while ((m = n * 2) < q->n) {
    if (m + 1 < q->n && b[m].pri > b[m + 1].pri) m++;

    if (b[q->n].pri <= b[m].pri) break;
    b[n] = b[m];
    n = m;
  }

  b[n] = b[q->n];
  if (q->n < q->alloc / 2 && q->n >= 16)
    q->buf = realloc(q->buf, (q->alloc /= 2) * sizeof(b[0]));

  return out;
}






/* get the top element without removing it from queue */
void* priorityqueue_top(pri_queue q, int *pri)
{
  if (q->n == 1) return 0;
  if (pri) *pri = q->buf[1].pri;
  return q->buf[1].data;
}


/* this is O(n log n), but probably not the best */
void priorityqueue_combine(pri_queue q, pri_queue q2)
{
  int i;
  q_elem_t *e = q2->buf + 1;

  for (i = q2->n - 1; i >= 1; i--, e++)
    priorityqueue_push(q, e->data, e->pri);
  priorityqueue_purge(q2);
}



int main()
{

    /*
//ExtractMax(Q) - returns the node with the highest priority.
Increase (Q,[x,p],a) - Increases priority p by a (i.e. priority += a) this is just increasing the priority a node in the queue
Change (Q,[x,p],b) - Sets priority p to b (i.e. priority = b) change
  */



//ExtractMax(Q) - returns the node with the highest priority.
  x = priorityqueue_top(q,pri[p]));
  printf("%d: %s\n", p, c);





  //integer variables
  int i, p;
  //these are character pointers
  const char *c, *tasks[] ={
    "nice", "night", "GW", "Have", "a" };
  int pri[] = { 3, 4, 5, 1, 2 };

  /* make thee queues */
  pri_queue q = priorityqueue_new(0), q2 = priorityqueue_new(0), q3 = priorityqueue_new(0);

  /* push all 5 tasks into q */
  for (i = 0; i < 5; i++)
    priorityqueue_push(q, tasks[i], pri[i]);

  /* pop them and print one by one */
  while ((c = priorityqueue_pop(q, &p)))
    printf("%d: %s\n", p, c);



  /* put a million random tasks in each queue */
  /* RAND_MAX value of this macro is an integer constant representing the largest value the rand function can return. In the GNU C Library, it is 2147483647 , which is the largest signed integer representable in 32 bits.*/
  /* Divide by 5 to be safe*/

  for (i = 0; i < 1 << 20; i++) {
    p = rand() / ( RAND_MAX / 5);
    priorityqueue_push(q, tasks[p], pri[p]);

    p = rand() / ( RAND_MAX / 5 );
    priorityqueue_push(q2, tasks[p], pri[p]);

    p = rand() / ( RAND_MAX / 5 );
    priorityqueue_push(q3, tasks[p], pri[p]);
  }

  printf("\nq has %d items, q2 has %d items, q3 has %d items\n", priorityqueue_size(q), priorityqueue_size(q2), priorityqueue_size(q3));

 while ((c = priorityqueue_pop(q, &p)))
    printf("%d: %s\n", p, c);


  /* merge q2 into q; q2 is empty */
  priorityqueue_combine(q, q2);
  printf("After merge, q has %d items, q2 has %d items\n",
    priorityqueue_size(q), priorityqueue_size(q2));
  /*merge q3 into q; q3 is empty */
  priorityqueue_combine(q, q3);
  printf("After merge, q has %d items, q3 has %d items\n",
    priorityqueue_size(q), priorityqueue_size(q3));

  /* pop q until it's empty */
  for (i = 0; (c = priorityqueue_pop(q, 0)); i++);
  printf("Popped %d items out of q\n", i);


}