#!/bin/bash
make APEX_PREBUILD=1 allsub && scp isp_csi_dcu.elf root@128.95.116.88:/s32v234/demos

