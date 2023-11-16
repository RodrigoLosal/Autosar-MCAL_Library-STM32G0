#---gdb settings
set auto-load safe-path /
set pagination off
set confirm off
set verbose off
set height 0
set width 0

#---connect and load program
target remote localhost:3333
mon arm semihosting enable
load
mon reset
break main
continue
