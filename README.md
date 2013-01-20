ntailq
======

NTAILQ is macros of \*BSD's TAILQ *with counter*.


EXAMPLE
-------

	#include "ntailq.h"
	
	struct elem {
		int value1;
		int value2;
		//    :
		NTAILQ_ENTRY(elem) list;
	};
	
	NTAILQ_HEAD(ntqhead, elem) ntq_head;
	
	struct elem *
	elem_new(void)
	{
		struct elem *e;
		e = malloc(sizeof(struct elem));
		return e;
	}
	
	void
	example(void)
	{
		struct elem *e;
	
		/* initialize */
		NTAILQ_INIT(&ntq_head);
		printf("%d\n", NTAILQ_N(&ntq_head));	/* result 0 */
	
		/* add element */
		e = elem_new();
		NTAILQ_INSERT_TAIL(&ntq_head, e, list);
		printf("%d\n", NTAILQ_N(&ntq_head));	/* result 1 */
	
		/* add more element */
		e = elem_new();
		NTAILQ_INSERT_TAIL(&ntq_head, e, list);
		printf("%d\n", NTAILQ_N(&ntq_head));	/* result 2 */
	
		/* remove element */
		NTAILQ_REMOVE(&ntq_head, e, list);
		printf("%d\n", NTAILQ_N(&ntq_head));	/* result 1 */

