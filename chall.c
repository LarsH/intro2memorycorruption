#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define msg_assert(msg, x) assert(msg && (x));
#define prompt(msg, dst) do{printf(msg);gets(dst);}while(0)

extern void gets(char*);
typedef void (*fptr_t)(void);


/* Example 1 */

void test1(void) {
	struct {
		char buf[16];
		void *value;
	} locals;

	locals.value = (void*) 0x1234;
	printf("Value is %p\n", locals.value);

	prompt("Enter your data:", locals.buf);
	printf("You entered %s\n", locals.buf);

	printf("Value is %p\n", locals.value);
}


/* Example 2 */

void printMessage() { printf("Hello there!\n"); }
void executeShell() { system("/bin/sh"); }

void test2(void) {
	struct {
		char buf[16];
		fptr_t func;
	} locals;

	locals.func = printMessage;
	printf("Func is %p\n", (void*) locals.func);

	prompt("Enter your data:", locals.buf);
	printf("You entered %s\n", locals.buf);

	locals.func();
}


/* Example 3 */

void test3(void) {
	char buf[16];
	printf("executeShell is %p\n", (void*) executeShell);
	prompt("Enter your data:", buf);
}



/* Main function */
fptr_t functions[] = {test1, test2, test3};
#define NUM_FUNCTIONS (sizeof(functions)/sizeof(*functions))

int main(int argc, char **argv) {
	/* Make sure input/output are unbuffered */
	setvbuf(stdin, 0, _IONBF, 0);
	setvbuf(stdout, 0, _IONBF, 0);

	msg_assert("Should be given a (numeric) argument", argc == 2);

	unsigned int choice = (atoi(argv[1])-1);
	msg_assert("Choice must be within range", choice < NUM_FUNCTIONS);

	functions[choice]();

	return EXIT_SUCCESS;
}
