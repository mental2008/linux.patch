# linux.patch

Implement a system call in linux kernel - Print out the information about given process pid



Detailed information of this system call

| System Call Name | System Call Number |                Function Parameters                 | Return Type |
| :--------------: | :----------------: | :------------------------------------------------: | ----------- |
|  print_pid_info  |        335         | (pid_t **pid**, char* **buffer**, size_t **size**) | long        |

Syscall ``print_pid_info`` will recursively print out the information about descendant processes of given process ``pid`` and store it in the ``buffer``.

The information format - (pid, status, running_time, ppid, sid)

- pid - type ``int`` 
- status - type ``char``
- running_time - type ``unsigned long``

- ppid - type ``int``, process id of parent process
- sid - type ``int``, process id of the first child process



## Prerequisites

- Ubuntu 18.04 (64-bit)
- Source code of linux kernel 5.5.5

You can download source code of linux kernel from [here](https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.5.5.tar.xz) and feel free to try another version of kernel.



## File Description

Three files to change in linux kernel

- ``kernel/sys.c``
- ``include/linux/syscalls.h``
- ``arch/x86/entry/syscalls/syscall_64.tbl``



``linux.patch`` is generated by this command

```bash
diff -uprN <linux-old-version> <linux-new-version> > linux.patch
```



You can load ``linux.patch`` in your own linux kernel

```bash
patch -p0 > linux.patch
```



## Kernel Installation

```bash
sudo make clean
sudo make oldconfig # use default settings
sudo make
sudo make modules_install
sudo make install
sudo reboot # reboot to make it work
```



## Test

Test file is defined in ``test.c``

```bash
gcc test.c -o test.o && ./test.o
```



Sample Output - Given process id **1913**

```bash
System call, status = 0
1913 S 14773 1794 1950
1950 S 14772 1913 1954
1954 S 14772 1950 -1
2158 S 14771 1950 -1
```



Kernel Output - By Using Command ``dmesg``

```bash
[14913.792236] PRINT_pid_info: This is new system call to print out the information about descendant processes of given process 1913.
[14913.796060] Successfully open /proc/uptime.
[14913.796067] Boot_time: 14913, start_time: 35190, HZ: 250.
[14913.796068] Given process: 1913, status: S, running time: 14773s
[14913.796068] PID of parent process: 1794
[14913.796068] PID of the first child process: 1950
[14913.796069] Successfully get the information of given process 1913 in buffer.
[14913.803560] Successfully open /proc/uptime.
[14913.803567] Boot_time: 14913, start_time: 35379, HZ: 250.
[14913.803567] Given process: 1950, status: S, running time: 14772s
[14913.803568] PID of parent process: 1913
[14913.803568] PID of the first child process: 1954
[14913.803569] Successfully get the information of given process 1950 in buffer.
[14913.810627] Successfully open /proc/uptime.
[14913.810634] Boot_time: 14913, start_time: 35383, HZ: 250.
[14913.810635] Given process: 1954, status: S, running time: 14772s
[14913.810635] PID of parent process: 1950
[14913.810635] There doesn't exist any child process of given process 1954.
[14913.810637] Successfully get the information of given process 1954 in buffer.
[14913.818230] Successfully open /proc/uptime.
[14913.818237] Boot_time: 14913, start_time: 35654, HZ: 250.
[14913.818237] Given process: 2158, status: S, running time: 14771s
[14913.818238] PID of parent process: 1950
[14913.818238] There doesn't exist any child process of given process 2158.
[14913.818240] Successfully get the information of given process 2158 in buffer.
```



## License

Copyright © 2020, [mental2008](https://github.com/mental2008).
