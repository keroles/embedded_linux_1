#Author: A_Napster_H
#Project 2 Embedded_Linux Over the Air simple concept

------------------------------------------The below code is simple concept for implementation of OTA app--------------------------------------

The code will be doing the following:-

	- Prepare the TFTP server
	- Load file from TFTP server to memory
	- Create variable to store the tftp size
	- Load file from sd card to memory
	- Create variable to store the sd card size
	- check if tftp file size is equal the sd card size 
		the file will load from sd card 
	Otherwise 
		change the name of the file to testbackup.elf
		copy the tftp file to sd card and load it 

-------------------------------------------------copy the below code in u boot command window------------------------------------------------

setenv tftp_load 'echo "=======>TFTP LOAD";dhcp;setenv serverip 192.168.1.10;tftp 0x70000000 test.elf;setenv tftp_size $filesize'
setenv sd_load 'echo "=======>SD CARD LOAD";fatload mmc 0:1 0x72000000 test.elf;setenv sd_size $filesize'
setenv cmp_backup 'echo "======>Start backup";fatwrite mmc 0:1 0x72000000 testbackup.elf $sd_size;fatrm mmc 0:1 test.elf;fatwrite mmc 0:1 0x70000000 test.elf $tftp_size'
setenv ota_cmp 'echo "=======>Start Checking";if test "${tftp_size}" = "${sd_size}";then echo "======>SAME SIZE";bootelf 0x72000000;else echo "======>DIFFERENT SIZE";run cmp_backup;bootelf 0x70000000;fi'
setenv OTA 'run tftp_load ;run sd_load; run ota_cmp'
setenv bootcmd 'echo "A_napster_H OTA";run OTA'

-------------------------------------------------The following is details of the above code----------------------------------------------------

-dhcp     // Prepare the TFTP server
-setenv serverip <your TFTP server IP> // Set the IP server
-tftp 0x70000000 test.elf  // Load file from TFTP server to memory
-setenv tftp_file_size $filesize // Create variable to store the tftp size
-fatload mmc 0:1 0x72000000 test.elf // Load file from sd card to memory
-setenv sd_file_size $filesize // Create variable to store the sd card size
-if test "${tftp_file_size}" = "${sd_file_size}"; // check if tftp file size is equal the sd card size
	then
		bootelf 0x72000000 // load the file from sd_card
	else
		fatwrite mmc 0:1 0x72000000 testbackup.elf $sd_card_size // copy test.elf to testbackup.elf "sd_card copy"
		fatrm mmc 0:1 test.elf // remove test.elf
		fatwrite mmc 0:1 0x70000000 test.elf $tftp_file_size // copy from memory to sd_card "sd_card copy"
		bootelf 0x70000000 // boot from memory 
-fi


--------------------------------------------- To run this APP you should do the following -----------------------------------------------------

open terminal to run TFTP server 
	- tftp <server ip address> // server ip address come from ifconfig if it will be localhost 
	- get test.elf //test.elf is the filename
open terminal 
-./OTA.sh
-press anykey to stop auto uboot

-setenv tftp_load 'echo "=======>TFTP LOAD";dhcp;setenv serverip 192.168.1.10;tftp 0x70000000 test.elf;setenv tftp_size $filesize'
-setenv sd_load 'echo "=======>SD CARD LOAD";fatload mmc 0:1 0x72000000 test.elf;setenv sd_size $filesize'
-setenv cmp_backup 'echo "======>Start backup";fatwrite mmc 0:1 0x72000000 testbackup.elf $sd_size;fatrm mmc 0:1 test.elf;fatwrite mmc 0:1 0x70000000 test.elf $tftp_size'
-setenv ota_cmp 'echo "=======>Start Checking";if test "${tftp_size}" = "${sd_size}";then echo "======>SAME SIZE";bootelf 0x72000000;else echo "======>DIFFERENT SIZE";run cmp_backup;bootelf 0x70000000;fi'
-setenv OTA 'run tftp_load ;run sd_load; run ota_cmp'
-setenv bootcmd 'echo "A_napster_H OTA";run OTA'
-saveenv
-ctrl+C to kill the process
-./OTA.sh

