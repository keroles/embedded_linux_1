#@Copyright www.learn-in-depth.com
#Author: Keroles Shenouda 
# Learn In Depth 
qemu-system-arm -M vexpress-a9 -m 512M \
-kernel $1 \
-no-reboot \
-monitor telnet:127.0.0.1:1234,server,nowait \
-serial stdio \
-nographic \
-sd $2 
#-S -gdb tcp::1212 \

