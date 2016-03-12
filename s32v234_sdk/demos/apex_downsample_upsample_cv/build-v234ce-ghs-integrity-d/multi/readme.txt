This demo uses HostIO to retrieve the input image files and write the
generated output files:
  - The default location is "/tmp/apex_demos" on the Linux build host.
  - You must copy the input data files before running the demo. For example,
    by running "cp $__VISION_S32V234_SDK/demos/data/* /tmp/apex_demos".
  - After execultion, the input file (in_grey_256x256.png) can be compared
    to the ouput files (downsampled.png and upsampled.png).

