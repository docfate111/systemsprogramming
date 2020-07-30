#include <dirent.h>
#include <sys/types.h>
struct direct{
	ino_t d_ino;
	char* d_name;
}
