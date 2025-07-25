#include <stdio.h>
#ifdef _WIN32 
__declspec(dllexport) void myputs(const char* str)
#else
void myputs(const char* str)
#endif
{
    printf("%s\n", str);
}