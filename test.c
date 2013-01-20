#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "ntailq.h"

struct geom {
	int x;
	NTAILQ_ENTRY(geom) list;
	int y;
};

NTAILQ_HEAD(ntqhead, geom) ntq_head = NTAILQ_HEAD_INITIALIZER(ntq_head);

int anyerror = 0;

void
t(int result, int lineno)
{
	static int testno = 0;
	if (result) {
		printf("%d: ok\n", testno++);
	} else {
		printf("%d: ng (line %d)\n", testno++, lineno);
		anyerror++;
	}
}

#define T(result)	t(result, __LINE__)


struct geom *
geom_new(int x, int y)
{
	struct geom *g;

	g = malloc(sizeof(struct geom));
	g->x = x;
	g->y = y;

	return g;
}

#define TEST_NUMBER1	1000
#define TEST_NUMBER2	100
#define TEST_NUMBER3	400
#define TEST_NUMBER4	600

#define TEST_MAGIC2	99999
#define TEST_MAGIC3	99998
#define TEST_MAGIC4	99997

int
main(int argc, char *argv[])
{
	int i, j;
	struct geom *g, *g2;

	/* test INITIALIZER */
	T(NTAILQ_N(&ntq_head) == 0);

	/* test INIT */
	NTAILQ_INIT(&ntq_head);
	T(NTAILQ_N(&ntq_head) == 0);

	/* test INSERT_TAIL, etc */
	for (i = 0; i < TEST_NUMBER1; i++) {
		g = geom_new(i, i * 2);
		NTAILQ_INSERT_TAIL(&ntq_head, g, list);
	}
	T(NTAILQ_FIRST(&ntq_head)->x == 0);
	T(NTAILQ_LAST(&ntq_head, ntqhead)->x == TEST_NUMBER1 - 1);
	T(NTAILQ_N(&ntq_head) == TEST_NUMBER1);

	/* test REMOVE, etc */
	NTAILQ_REMOVE(&ntq_head, g, list);
	T(NTAILQ_FIRST(&ntq_head)->x == 0);
	T(NTAILQ_LAST(&ntq_head, ntqhead)->x == TEST_NUMBER1 - 2);
	T(NTAILQ_N(&ntq_head) == TEST_NUMBER1 - 1);

	g = NTAILQ_FIRST(&ntq_head);
	for (i = 0; i < TEST_NUMBER2; i++)
		g = NTAILQ_NEXT(g, list);
	T(g->x == 100);
	NTAILQ_REMOVE(&ntq_head, g, list);
	T(NTAILQ_N(&ntq_head) == TEST_NUMBER1 - 2);

	g = NTAILQ_FIRST(&ntq_head);
	for (i = 0; i < TEST_NUMBER2 - 1; i++)
	g = NTAILQ_NEXT(g, list);
	T(g->x == TEST_NUMBER2 - 1);
	g = NTAILQ_NEXT(g, list);
	T(g->x == TEST_NUMBER2 + 1);

	/* test INSERT_HEAD */
	g2 = geom_new(TEST_MAGIC2, TEST_MAGIC2* 2);
	NTAILQ_INSERT_HEAD(&ntq_head, g2, list);
	T(NTAILQ_N(&ntq_head) == TEST_NUMBER1 - 1);
	T(NTAILQ_FIRST(&ntq_head)->x == TEST_MAGIC2);
	T(NTAILQ_LAST(&ntq_head, ntqhead)->x == TEST_NUMBER1 - 2);

	/*
	 * test NTAILQ_INSERT_BEFORE
	 */
	g = NTAILQ_FIRST(&ntq_head);
	for (i = 0; i < TEST_NUMBER3; i++)
		g = NTAILQ_NEXT(g, list);
	g2 = geom_new(TEST_MAGIC3, TEST_MAGIC3 * 2);
	NTAILQ_INSERT_BEFORE(&ntq_head, g, g2, list);

	/* verify */
	g = NTAILQ_FIRST(&ntq_head);
	for (i = 0; i < TEST_NUMBER3; i++)
		g = NTAILQ_NEXT(g, list);
	T(g->x == TEST_MAGIC3);


	/*
	 * test NTAILQ_INSERT_AFTER
	 */
	g = NTAILQ_FIRST(&ntq_head);
	for (i = 0; i < TEST_NUMBER4; i++)
		g = NTAILQ_NEXT(g, list);
	g2 = geom_new(TEST_MAGIC4, TEST_MAGIC4 * 2);
	NTAILQ_INSERT_AFTER(&ntq_head, g, g2, list);

	/* verify */
	g = NTAILQ_FIRST(&ntq_head);
	for (i = 0; i < TEST_NUMBER4; i++)
		g = NTAILQ_NEXT(g, list);
	g = NTAILQ_NEXT(g, list);
	T(g->x == TEST_MAGIC4);

	T(NTAILQ_N(&ntq_head) ==  TEST_NUMBER1 + 1);

	/* test FOREACH */
	j = 0;
	NTAILQ_FOREACH(g, &ntq_head, list) {
		j++;
	}
	T(NTAILQ_N(&ntq_head) ==  j);


	if (anyerror)
		return EXIT_FAILURE;
	return 0;
}
