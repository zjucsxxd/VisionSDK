#include <INTEGRITY.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/authtable.h>
#include <unistd.h>



UserEntry users[] = {
	{"nobody","",__nobody,NULLObject,__nogroup,NULL,0,NULLObject,{0},"/"},
};
int num_users = sizeof(users)/sizeof(UserEntry);



GroupEntry groups[] = {
	{"nogroup",__nogroup,NULLObject},
};
int num_groups = sizeof(groups)/sizeof(GroupEntry);



#ifdef PSS_MAIN
int main() {
	void InitPosixSysServer(void);

	InitPosixSysServer();
	Exit(0);
};
#endif
