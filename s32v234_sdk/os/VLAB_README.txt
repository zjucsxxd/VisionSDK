VLAB: Quick Start Guide
=======================

A) Running Linux on the Virtual Platform
----------------------------------------

1) Copy files
-------------

    from:
  
    build_content/vlab_content/examples
    build_content/vlab_content/s32v234_scripts
    
    to:
  
    C:\Program Files\VLAB Works\VLAB 1.11.3\toolbox\i.mxvs4-0.4.1\
    
    (Version numbers or installation directories can differ)
    
    
2) Add Linux to VLAB menu
-------------------------
    
  - Copy or alter:
  
    build_content/vlab_content/__descriptor__.py 
    
    to 
  
    C:\Program Files\VLAB Works\VLAB 1.11.3\toolbox\i.mxvs4-0.4.1\__descriptor__.py 


VLAB : Rebuilding the environment
=================================

 - Every file provided with this package can be rebuilt. Please see following readmes:
 
   boot/aarch64/README.txt     // For u-boot rebuild
   linux/aarch64/README.txt    // For Linux kernel, devicetree.dtb and ramdisk root file system rebuild

   
B) Running Linux on the Virtual Platform
----------------------------------------

1) Open VLAB and run S32V234 simulation
--------------------------------------- 
  - In VLAB command prompt run:
    vlab.load("s32v234.sim", args=["--debugger", "--terminal=platform.linflex0"])
  - after successfully loading the simulation VLAB should be paused
    
2. Connect CADI Daemon
----------------------
(included in GHS Compiler distribution)
  - Execute cadid.exe -list  
  
3. Debug the kernel monolith from MULTI
---------------------------------------  
  - open MULTI debuger 
  - create new connection:
    - set Target setup script to:
      INTEGRITY_ROOT_PATH/treerunner/ve-fvp/treerunner.mbs.
    - ser Server to: cadiserv 
  - download the kernel

4. Run the kernel monolith from MULTI
-------------------------------------
  - Enter run() command in VLAB to continue the simulation.
  - Run the kernel image from MULTI debugger.
  - The Integrity kernel will boot up in a few moments and display kernel banner
    in the VLAB terminal.
  

      
  
