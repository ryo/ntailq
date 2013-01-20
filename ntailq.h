/*-
 * Copyright (c) 2013 SHIMIZU Ryo <ryo@nerv.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _NTAILQ_H_
#define _NTAILQ_H_

#include <sys/queue.h>

#define _NTAILQ_HEAD(name, type, qual)				\
struct name {							\
	_TAILQ_HEAD(name ## _tailq_head, type, ) ntq;		\
	unsigned long n;					\
}
#define NTAILQ_HEAD(name, type)					\
	_NTAILQ_HEAD(name, struct type, )

#define NTAILQ_HEAD_INITIALIZER(head)				\
	{ TAILQ_HEAD_INITIALIZER((head).ntq), 0 }

#define NTAILQ_INIT(head) do {					\
	TAILQ_INIT(&(head)->ntq);				\
	(head)->n = 0;						\
} while (/*CONSTCOND*/0)

#define NTAILQ_N(head)						\
	(head)->n

#define NTAILQ_ENTRY(type)					\
	TAILQ_ENTRY(type)

#define NTAILQ_INSERT_HEAD(head, elm, field) do {		\
	TAILQ_INSERT_HEAD(&(head)->ntq, elm, field);		\
	(head)->n++;						\
} while (/*CONSTCOND*/0)

#define NTAILQ_INSERT_TAIL(head, elm, field) do {		\
	TAILQ_INSERT_TAIL(&(head)->ntq, elm, field);		\
	(head)->n++;						\
} while (/*CONSTCOND*/0)

#define NTAILQ_INSERT_AFTER(head, listelm, elm, field) do {	\
	TAILQ_INSERT_AFTER(&(head)->ntq, listelm, elm, field);	\
	(head)->n++;						\
} while (/*CONSTCOND*/0)

#define NTAILQ_INSERT_BEFORE(head, listelm, elm, field) do {	\
	TAILQ_INSERT_BEFORE(listelm, elm, field);		\
	(head)->n++;						\
} while (/*CONSTCOND*/0)

#define NTAILQ_REMOVE(head, elm, field) do {			\
	TAILQ_REMOVE(&(head)->ntq, elm, field);			\
	(head)->n--;						\
} while (/*CONSTCOND*/0)

#define NTAILQ_FOREACH(var, head, field)			\
	TAILQ_FOREACH(var, &(head)->ntq, field)

#define NTAILQ_EMPTY(head)					\
	TAILQ_EMPTY(&(head)->ntq)

#define NTAILQ_FIRST(head)					\
	TAILQ_FIRST(&(head)->ntq)

#define NTAILQ_NEXT(elm, field)					\
	TAILQ_NEXT(elm, field)

#define NTAILQ_LAST(head, headname)				\
	TAILQ_LAST(&(head)->ntq, headname ## _tailq_head)

#define NTAILQ_PREV(elm, headname)				\
	TAILQ_PREV(elm, headname)

#endif /* _NTAILQ_H_ */
