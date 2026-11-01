*This project has been created as part of the 42 curriculum by acano-kr.*

# Born2beRoot

<p align="center">
  <a href="https://github.com/XandaoKruger"><img src="https://img.shields.io/badge/GitHub-acano--kr-181717?style=for-the-badge&logo=github" alt="acano-kr"/></a>
</p>

## Description

Born2beRoot is a system administration project. The goal is to create and configure a
virtual machine (VM) following strict security rules, and to understand every
choice made along the way.

The result is a headless Debian server running in VirtualBox with an encrypted LVM
disk, a restricted SSH service, a firewall, a strong password policy, a hardened
`sudo` configuration, and a monitoring script that broadcasts system information
every 10 minutes.

**Summary of the final machine**

| Item | Value |
|---|---|
| Hypervisor | VirtualBox |
| Operating system | Debian 13 "trixie" (64-bit), no graphical environment |
| Hostname | `acano-kr42` |
| Main user | `acano-kr` (groups: `sudo`, `user42`) |
| Resources | 1 vCPU, 1 GB RAM, 8 GB virtual disk |
| SSH | port `4242`, root login disabled |
| Firewall | UFW active, only port `4242` open |
| Mandatory access control | AppArmor (enabled) |

## Instructions

1. In VirtualBox, create a Debian (64-bit) VM with 1024 MB of RAM and attach the
   `.vdi` disk (or import the machine with *Machine > Add* using the `.vbox` file).
2. Start the VM. At boot, type the encryption passphrase of the `sda5_crypt` volume.
3. Log in with the regular user (`acano-kr`). Root cannot log in over SSH.
4. To connect from the host, add a port-forwarding rule in
   *Settings > Network > Adapter 1 (NAT) > Advanced > Port Forwarding*:
   `TCP`, host port `4241`, guest port `4242`. Then run:

   ```
   ssh acano-kr@127.0.0.1 -p 4241
   ```

5. Useful verification commands:

   ```
   lsblk                                  # partitions and LVM
   sudo ufw status numbered               # firewall rules
   sudo systemctl status ssh              # SSH service
   sudo aa-status                         # AppArmor
   getent group sudo user42               # group membership
   sudo chage -l <user>                   # password expiry policy
   sudo cat /var/log/sudo/sudo.log        # sudo history
   sudo crontab -u root -l                # scheduled monitoring
   ```

The `signature.txt` file at the root of the repository contains the SHA-1 hash of the
VM `.vdi` disk. The VM must not be started after the signature is generated, because
every boot changes the disk file.

## Operating system choice: Debian

Debian was chosen because it is stable, well documented and, as the subject
recommends, friendlier for a first system administration project. Its `apt`
ecosystem is large and consistent, and AppArmor is enabled by default.

### Debian vs Rocky Linux

| | Debian | Rocky Linux |
|---|---|---|
| Origin | Independent, community-driven distribution | Community rebuild of Red Hat Enterprise Linux (RHEL) |
| Package manager | `apt` / `dpkg` (`.deb`) | `dnf` / `rpm` (`.rpm`) |
| Default MAC system | AppArmor | SELinux |
| Default firewall tool | none enforced (UFW is a common choice) | firewalld |
| Release model | Stable releases, large repositories | Long enterprise support cycles, RHEL compatibility |

**Pros of Debian:** very stable, huge package repository, excellent documentation,
simpler to learn, lighter default setup. **Cons:** older package versions in the
stable branch, and less common than RHEL-compatible systems in enterprise
environments. **Pros of Rocky:** RHEL compatibility, long support cycles, strong
SELinux integration. **Cons:** steeper learning curve (SELinux, firewalld) and
fewer beginner resources for this project.

### apt vs aptitude

Both manage packages on Debian. `apt` is the modern, simple command-line tool and
comes installed by default. `aptitude` is a higher-level front-end with an
interactive text interface and a more elaborate dependency resolver, but it is not
installed by default.

## Main design choices

### Virtual machine

A virtual machine is a software-emulated computer that runs on top of a real one,
managed by a hypervisor. It lets the system be isolated, snapshotted, copied and
destroyed without touching the host. VirtualBox is a type 2 hypervisor, meaning it
runs as a program on top of the host operating system.

### Partitioning

The installer used *Guided - use entire disk and set up encrypted LVM* with the
small-disk scheme (the virtual disk is 8 GB):

| Device | Size | Use |
|---|---|---|
| `sda1` | ~833 MB | `/boot` (ext4), not encrypted |
| `sda5` | ~7.6 GB | LUKS encrypted container (`sda5_crypt`) |
| `root` (LVM) | ~6.4 GB | `/` (ext4) |
| `swap_1` (LVM) | ~780 MB | swap |

**LVM (Logical Volume Manager)** adds a layer between the disk and the filesystems.
Physical partitions become physical volumes, grouped into a volume group, which is
split into logical volumes that can be resized without repartitioning. Encrypting the
LVM container protects all data at rest, and the passphrase is required at every boot.

### Security policies

**Password policy**

- Expiry (`/etc/login.defs`, applied to existing accounts with `chage`):
  maximum 30 days, minimum 2 days between changes, warning 7 days before expiry.
- Strength (`libpam-pwquality`, configured in `/etc/pam.d/common-password` and
  `/etc/security/pwquality.conf`): at least 10 characters, at least one uppercase,
  one lowercase and one digit, no more than 3 identical consecutive characters,
  must not contain the user name, at least 7 characters different from the previous
  password, and the policy is also enforced for root.

Advantages: it makes brute-force and dictionary attacks harder, limits the lifetime
of a leaked password and prevents small variations of old passwords. Disadvantage:
users may write complex passwords down or find frequent changes annoying.

**Sudo** (`/etc/sudoers.d/sudo_config`)

- 3 attempts on wrong password, with a custom error message.
- Every command is logged (input and output) in `/var/log/sudo/`.
- `requiretty` is enabled and `secure_path` restricts where commands are searched.

`sudo` lets an authorized user run commands with root privileges, with
accountability (logs) and without sharing the root password.

**SSH**

OpenSSH listens only on port `4242`, and `PermitRootLogin no` blocks direct root
access. SSH (Secure Shell) provides an encrypted remote shell, replacing insecure
protocols such as telnet.

**Firewall**

UFW is enabled at boot and only port `4242` is allowed.

**AppArmor** is active and confines programs with per-application profiles.

### User management

The main user `acano-kr` belongs to the `sudo` and `user42` groups. Passwords of all
accounts, including root, were changed after the policy was configured.

### Services

- `ssh` (OpenSSH server) on port 4242
- `ufw` firewall
- `cron` running the monitoring script as root every 10 minutes
- `apparmor`

### Monitoring script

`/usr/local/bin/monitoring.sh` is run by root's crontab (`*/10 * * * *`) and sends
its output to every terminal with `wall`. It reports:

- operating system architecture and kernel
- number of physical CPUs and virtual CPUs
- memory usage (used / total and percentage)
- disk usage (used / total and percentage)
- CPU load
- date of the last boot
- whether LVM is in use
- number of established TCP connections
- number of logged-in users
- IPv4 address and MAC address
- number of commands executed with `sudo`

`cron` is the Unix job scheduler. Its five time fields are minute, hour, day of the
month, month and day of the week, and `*/10` in the first field means every 10
minutes. To stop the script from running at boot without editing it, the cron
service can be disabled with `systemctl disable cron`.

## Comparisons

### AppArmor vs SELinux

Both are Linux Mandatory Access Control systems that restrict what programs can do,
even when they run as root. AppArmor is **path-based**: each program has a profile
listing the files and capabilities it may use, which makes it easier to learn and
write. SELinux is **label-based**: every file and process receives a security
context and a global policy decides what each context can do, which is more
granular but more complex. Debian ships with AppArmor and Rocky/RHEL with SELinux.

### UFW vs firewalld

Both manage the kernel packet filter. **UFW** (Uncomplicated Firewall) is a simple
front-end with short commands such as `ufw allow 4242`, popular on Debian/Ubuntu.
**firewalld** works with *zones* and services, can change rules at runtime without
dropping connections and is the default on Rocky/RHEL. UFW was chosen because it
is simpler and enough for a single-port policy.

### VirtualBox vs UTM

**VirtualBox** is a free, open-source type 2 hypervisor from Oracle that runs on
Windows, Linux and Intel-based macOS, and uses the `.vdi` disk format. **UTM** is a
virtualization app for macOS (and iOS) built on QEMU and Apple's virtualization
framework, and is the practical option on Apple Silicon Macs, where VirtualBox
does not run x86 guests. VirtualBox was used because it is the tool required by the
subject for the available machines.

## Resources

- Debian documentation and manual pages (`man sudoers`, `man pwquality.conf`,
  `man sshd_config`, `man crontab`)
- The Born2beRoot subject and evaluation sheet (42 intranet)
- Debian Administrator's Handbook, Ubuntu/Debian UFW documentation
- Community Born2beRoot guides, used as a reference for the setup order

**AI usage:** Claude was used as a study assistant to explain concepts,
review configuration files and troubleshoot errors. The machine was installed,
configured and tested by the author (acano-kr), who is able to explain each step.
