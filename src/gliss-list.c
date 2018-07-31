/*
 * This file is a part of Gliss
 *
 * Copyright (C) 2010:
 *
 *  Michael Dominic K. <mdk@mdk.am>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "gliss-list.h"

/* Add an element to the beginging of the list.
 * Slice passed has to be initialized to support elements of type list. */
GLISS_INTERNAL glissInternalList*
glissInternalListPrepend (glissInternalList *list,
                          glissInternalSlice *slice,
                          GLvoid *data)
{
    glissInternalList *newElement = glissInternalSliceNewElement (slice);

    newElement->next = list;
    newElement->prev = NULL;
    newElement->data = data;

    if (list)
        list->prev = newElement;

    return newElement;
}

GLISS_INTERNAL glissInternalList*
glissInternalListAppendSorted (glissInternalList *list,
                               glissInternalSlice *slice,
                               GLvoid *data,
                               GLint (*cmpFunction) (void*, void*))
{
    glissInternalList *newElement = glissInternalSliceNewElement (slice);
    newElement->data = data;

    glissInternalList *iterator = list;
    glissInternalList *after = NULL;

    while (iterator) {
        if (cmpFunction (data, iterator->data) < 0)
            break;

        after = iterator;
        iterator = iterator->next;
    }

    if (after) {
        newElement->next = after->next;
        newElement->prev = after;
        if (after->next)
            after->next->prev = newElement;
        after->next = newElement;
        return list;
    } else {
        newElement->next = list;
        newElement->prev = NULL;
        return newElement;
    }
}

/* Add an element to the beginging of the list, like normal prepend.
 * Additionally fills-in the type field. */
GLISS_INTERNAL glissInternalList*
glissInternalListPrependWithType (glissInternalList *list,
                                  glissInternalSlice *slice,
                                  GLint type,
                                  GLvoid *data)
{
    glissInternalList *newElement = glissInternalSliceNewElement (slice);

    newElement->next = list;
    newElement->prev = NULL;
    newElement->type = type;
    newElement->data = data;

    if (list)
        list->prev = newElement;

    return newElement;
}

/* Add an element to the begining of the list, but only
 * if the element is not part of it already. Uses pointer comparison. */
GLISS_INTERNAL glissInternalList*
glissInternalListPrependUnique (glissInternalList *list,
                                glissInternalSlice *slice,
                                GLvoid *data)
{
    glissInternalList *iterator = list;
    while (iterator) {
        if (iterator->data == data)
            return list;

        iterator = iterator->next;
    }

    return glissInternalListPrepend (list, slice, data);
}

/* Reverse the list. Make the last element first. */
GLISS_INTERNAL glissInternalList*
glissInternalListReverse (glissInternalList *list)
{
    glissInternalList *iterator = list;
    glissInternalList *prev_iterator = list;
    glissInternalList *temp;

    while (iterator) {

        /* Swap next and prev */
        temp = iterator->next;
        iterator->next = iterator->prev;
        iterator->prev = temp;

        prev_iterator = iterator;
        iterator = temp;
    }

    return prev_iterator;
}

/* Get the last element of the list */
GLISS_INTERNAL glissInternalList*
glissInternalListLast (glissInternalList *list)
{
    if (list == NULL)
        return NULL;

    glissInternalList *iterator = list;

    while (iterator->next != NULL)
        iterator = iterator->next;

    return iterator;
}

/* Removes an element (a list entry) from the given list */
GLISS_INTERNAL glissInternalList*
glissInternalListRemoveLink (glissInternalList *list,
                             glissInternalList *link)
{
    if (link == list) {
        if (link->next)
            link->next->prev = NULL;
        return link->next;
    }

    link->prev->next = link->next;
    if (link->next)
        link->next->prev = link->prev;

    return list;
}

/* Returns the number of elements in the list */
GLISS_INTERNAL GLint
glissInternalListCount (glissInternalList *list)
{
    GLint count = 0;

    glissInternalList *iterator = list;
    while (iterator != NULL) {
        count++;
        iterator = iterator->next;
    }

    return count;
}

GLISS_INTERNAL glissInternalList*
glissInternalListMerge (glissInternalList *listA,
                        glissInternalList *listB)
{
    if (listB == NULL)
        return listA;

    if (listA == NULL)
        return listB;

    glissInternalList *last = glissInternalListLast (listA);
    last->next = listB;
    listB->prev = last;

    return listA;
}

GLISS_INTERNAL glissInternalList*
glissInternalListMergeWithoutDestroy (glissInternalList *listA,
                                      glissInternalList *listB,
                                      glissInternalSlice *listSlice)
{
    glissInternalList *iterator = listB;

    while (iterator) {
        listA = glissInternalListPrepend (listA, listSlice, iterator->data);
        iterator = iterator->next;
    }

    return listA;
}

