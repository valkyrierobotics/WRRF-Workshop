# -*- mode: ruby -*-
# vi: set ft=ruby

# Don't change this line unless you know what you're doing
Vagrant.configure("2") do |config|
  # Common configuration is documented and set up below.
  # For a complete reference, see online documentation at
  # https://docs.vagrantup.com

  # To start off, we specify a box, which are indexed at
  # https://atlas.hashicorp.com/search
  config.vm.box = "debian/jessie64"
  # Set the location of the script we use to provision the box properly for
  # our uses.
  config.vm.provision :shell, path: "bootstrap.sh"

  # Create a forwarded port so that port 80 in the box appears as port 8080 in
  # the host. Edit this if you need more forwarded ports.
  #
  # This is useful for web who might want to test with gulp or jekyll serve.
  config.vm.network "forwarded_port", guest: 80, host: 8080

  # Sync the folder "Valkyrie" in this directory (on host) to the folder
  # /home/valkyrie/Valkyrie in the guest.
  config.vm.synced_folder "Valkyrie", "/home/vagrant/Valkyrie"

  # Configuration specific to virtualbox. These exist for other providers
  # as well.
  config.vm.provider "virtualbox" do |vb|
    vb.gui = false

    vb.memory = "4096"
  end

  config.ssh.forward_x11 = true
end
