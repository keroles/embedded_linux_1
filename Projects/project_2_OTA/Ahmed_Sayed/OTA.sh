
#Author: A_Napster_H

qemu-system-arm -M vexpress-a9 -m 512M \
-kernel u-boot \
-no-reboot \
-monitor telnet:127.0.0.1:1234,server,nowait \
-serial stdio \
-nographic \
-sd NAP_SD_2M.img 2> /dev/null
