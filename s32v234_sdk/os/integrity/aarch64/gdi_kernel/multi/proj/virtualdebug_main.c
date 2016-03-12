#include <INTEGRITY.h>

const char *DPAA_VDRVR_GetPartitionName(void)
{
    return "";
}

extern Error GipcTarget_Initialize(void);

int main(int argc, char *argv[])
{
#if !defined(INTEGRITY_SIMULATE)
    CheckSuccess(GipcTarget_Initialize());
#endif
    Exit(0);
}
