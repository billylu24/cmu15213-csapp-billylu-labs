/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q==NULL) {
        return NULL;
    }
    q->head = NULL;
    q->size=0;
    q->tail= NULL;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    if (q == NULL) {
        return;
    }
    if (q->head==NULL) {
        free(q);
        return;
    }
    struct list_ele *temp=q->head;
    while (temp!=q->tail) {
        struct list_ele *a=temp;
        temp=temp->next;
        free(a->value);
        free(a);
    }
    free(temp->value);
    free(temp);
    /* Free queue structure */
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    if (q==NULL||s==NULL) {
        return false;
    }
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh==NULL) {
        return false;
    }

    char* content=malloc(strlen(s)+1);
    if (content==NULL) {
        free(newh);
        return false;
    }

    strcpy(content,s);

    /* What if either call to malloc returns NULL? */
    newh->value=content;
    if (q->size==0) {
        q->head=newh;
        q->tail=newh;
        q->size++;
        newh->next=NULL;
        return true;
    }
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q==NULL||s==NULL) {
        return false;
    }
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (newt==NULL) {
        return false;
    }
    char* a=malloc(strlen(s)+1);
    if (a==NULL) {
        free(newt);
        return false;
    }
    strcpy(a,s);
    newt->value=a;
    newt->next=NULL;
    if (q->size==0) {
        q->head=newt;
        q->tail=newt;
        q->size++;
        return true;
    }
    q->size++;
    q->tail->next=newt;
    q->tail=newt;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    if (q==NULL||q->head==NULL) {
        return false;
    }
    if (buf!=NULL&& bufsize>0) {
        size_t len=strlen(q->head->value);
        for (size_t i=0;i<bufsize&&i<len;i++) {
            buf[i]=q->head->value[i];
        }
        if (bufsize>len) {
            buf[strlen(q->head->value)]=0;
        }
        buf[bufsize-1]='\0';
    }


    list_ele_t *old_head=q->head;
    q->head = q->head->next;
    q->size--;
    free(old_head->value);
    free(old_head);
    if (q->head==NULL) {
        q->tail=NULL;
    }
    return true;
}


/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q==NULL) {
        return 0;
    }
    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (q==NULL||q->size==1) {
        return;
    }
    list_ele_t *temp=q->head;
    list_ele_t *pre=NULL;
    while (temp!=NULL) {
        list_ele_t *OP_next=temp->next;
        temp->next=pre;
        pre=temp;
        temp=OP_next;
    }
    list_ele_t *old=q->head;
    q->head=q->tail;
    q->tail=old;
}
