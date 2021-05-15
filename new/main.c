#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <dlfcn.h>


void (*hello_msg)(const char *mame);

bool init_library() 
{
	void *hdl = dlopen("./libHello.so", RTLD_LAZY);
	
	if( hdl == NULL)
	{
		return false;
	}

	hello_msg = (void (*)(const char*))dlsym(hdl, "hello_message");

	if ( hello_msg == NULL )
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main()
{
	if( init_library())
		hello_msg("Gary");
	else
		printf(" Library was not load \n");
	
	return 0;
}