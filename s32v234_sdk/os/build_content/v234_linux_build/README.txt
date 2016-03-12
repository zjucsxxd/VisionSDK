Preparation of the SD card for S32V234 EVB
==========================================

1) Format the card
------------------

  - Load the card into the reader
  - get the name of sdcard by using "cat /proc/partitions" 
    - in this example, the device is called /dev/sdb. Please change the name in all lines below accordingly.
    
  - sudo fdisk /dev/sdb
      
      d [repeat this until no partition is reported by the 'p' command ] 
      
      n [create a new partition] 
      p [create a primary partition] 
      1 [the first partition] 
      <enter> [using the default value will create a partition that starts at offset 2048] 
      +255M [size of the actual partition = 255 MB] 
      
      n [create a new partition] 
      p [create a primary partition] 
      2 [the second partition] 
      <enter> [using the default value will create a partition that starts at offset 67584] 
      <enter> [using the default value will create a partition that uses the remaining space on the card] 
      
      t [set partition type] 
      1 [partition #1] 
      c [FAT32] 
      t [set partition type] 
      2 [partition #2] 
      83 [Linux] 
      
      w [ this writes the partition table to the medium and fdisk exits]
      
  - Remove the SD card from the slot and put it back again
  - sudo mkfs.vfat -n boot /dev/sdb1
  - sudo mkfs.ext3 -L rootfs /dev/sdb2
  
  - Remove the SD card from the slot and put it back again
  
2) Load the content onto the card
---------------------------------

  - cd s32v234_sdk/os/build_content/v234_linux_build
  - sudo dd if=u-boot.s32 of=/dev/sdb bs=512 seek=8 conv=fsync
  - sudo cp uImage /media/boot
  - sudo cp s32v234-evb.dtb /media/boot
  - cd /media/rootfs
  - sudo tar xvf s32v234_sdk/os/build_content/v234_linux_build/rootfs.tar
  - sync
  
3) Copy the user built content ontho the card
---------------------------------------------

  - User can copy anything to the /media/rootfs - this is the root file system of the board and the files will be visible
  
4) Boot the board
-----------------

  - Insert the SD card into the EVB and turn it on. The UART is running on 115200 baud.
  - The Linux will boot into command line and automatically loads OAL and APEX drivers.
  
