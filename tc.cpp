#define INCL_DOSPROCESS
#include <os2.h>

#include <stdio.h>

volatile int done=0;	//nemmere end en semafor

class A;
struct parameterBlok {
	A *thisPtr;
	int i1;
	char c1;
};

class A {
	int p_int;
public:
	A(int i) { p_int=i; }

	void foo(int i1, char c1);
	static VOID APIENTRY _foo(ULONG p)
	{
		parameterBlok *pbp=(parameterBlok *)p;
		pbp->thisPtr->foo(pbp->i1,pbp->c1);
	}
};

void A::foo(int i1, char c1) {
	printf("hej fra foo():\n");
	printf(" p_int=%d, i1 = %d, c1 = %c\n",p_int,i1,c1);
	done = 1;
}


void main(void) {
	A *a = new A(26);
	parameterBlok pb;
	TID tid;
	pb.thisPtr=a;
	pb.i1=27;
	pb.c1='D';
	printf("main(): laver foo() thread\n");
	DosCreateThread(&tid, A::_foo, (ULONG)(PVOID)&pb, 0, 4096);

	while(!done);

	printf("main(): foo() f‘rdig\n");
}

