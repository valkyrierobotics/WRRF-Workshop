# Setting up your Valkyrie Development Environment

*Installing Debian Jessie x64 will make your life easier and make deploying to
the robot easier. It's hard to dual-boot, but it's up to you to decide if it's
worth it. We will always help with the process.*

**If you get an error involving filesystems, run `vagrant plugin install vagrant-vbguest'`. If that fails, ask for assistance.**

**If you have AMD, VT-x is probably already on**

## Table of Contents

* [Windows](#windows)
    * [Notes](#notes)
* [Debian/Ubuntu](#debianubuntu)
    * [Notes](#notes-1)
* [Mac OS X](#mac-os-x)
    * [Notes](#notes-2)

## Windows

### Notes
* We assume that you already have git.
* You need to turn on VT-x which could also be called Intel Virtualization Technology or Virtualization Extensions in BIOS. Try [this guide](http://www.howtogeek.com/213795/how-to-enable-intel-vt-x-in-your-computers-bios-or-uefi-firmware/)

1. Install the following software:
    - [Virtual Box](https://www.virtualbox.org/wiki/Downloads)
    - [Vagrant](http://www.vagrantup.com/)
    - [PuTTY and PuTTYGen](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html) *If you already have Cygwin (or git on your PATH), don't install these.*

2. Clone the following git repository: `https://github.com/valkyrierobotics/dev-environment`
3. Move into the cloned directory, i.e `cd dev-environment`
4. Run `vagrant up` and wait for the bootstrapping process to complete.
5. At this point, `vagrant ssh` should allow you to access the VirtualBox. If not, run `vagrant ssh-config` and then
use PuTTY to connect to that IP and port with the username "vagrant" and password "vagrant."
6. You can now use PuTTYGen to convert the OpenSSH key used by vagrant into a PPK and save it and then access the VirtualBox instance through pubkey.

## Debian/Ubuntu

### Notes
* We assume you've already installed git and other basic Linux tools
* You need to turn on VT-x which could also be called Intel Virtualization Technology or Virtualization Extensions in BIOS. Try [this guide](http://www.howtogeek.com/213795/how-to-enable-intel-vt-x-in-your-computers-bios-or-uefi-firmware/)
* You can install .deb files using `sudo dpkg -i blahblahblah.deb`

1. Install the following software:
    - [Virtual Box](https://www.virtualbox.org/wiki/Downloads)
    - [Vagrant](http://www.vagrantup.com/)
2. Clone the following git repository: `https://github.com/valkyrierobotics/dev-environment`
3. Move into the cloned directory, i.e `cd dev-environment`
4. Run `vagrant up` and wait for the bootstrapping process to complete.
5. At this point, `vagrant ssh` should allow you to access the VirtualBox.

## Mac OS X

### Notes
* We assume you've already installed git and other basic tools
* Unless you have a really old Mac, VT-x is probably already turned on. You can use `sysctl -a | grep machdep.cpu.features`. If you see **VMX** in the output, then you're fine.

1. Install the following software:
    - [Virtual Box](https://www.virtualbox.org/wiki/Downloads)
    - [Vagrant](http://www.vagrantup.com/)
2. Clone the following git repository: `https://github.com/valkyrierobotics/dev-environment`
3. Move into the cloned directory, i.e `cd dev-environment`
4. Run `vagrant up` and wait for the bootstrapping process to complete.
5. At this point, `vagrant ssh` should allow you to access the VirtualBox.
