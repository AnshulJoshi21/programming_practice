#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX 5

typedef struct Deque
{
    int arr[MAX];
    int front;
    int rear;

} Deque;

static void d_init(Deque *d)
{
    assert(d);

    d->front = -1;
    d->rear  = -1;
}

static bool d_is_empty(Deque *d)
{
    assert(d);

    return (d->front == -1);
}

static void d_insert_front(Deque *d)
{
    assert(d);

    if (d_is_empty(d)) {
        d->front = d->rear = 0;
    }
}

int main(void)
{
    int deque[MAX];
    int front = 0, rear = 0;

    return 0;
}
