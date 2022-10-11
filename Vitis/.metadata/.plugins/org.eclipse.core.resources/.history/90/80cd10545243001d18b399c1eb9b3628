# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/dylan/workspace/phased_array_platform/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/dylan/workspace/phased_array_platform/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {phased_array_platform}\
-hw {/home/dylan/Documents/FPGA/phased_array/design_1_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {/home/dylan/workspace}

platform write
platform generate -domains 
platform active {phased_array_platform}
platform generate
platform generate
