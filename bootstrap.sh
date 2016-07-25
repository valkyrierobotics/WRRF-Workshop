#!/usr/bin/env bash

oldHome=$HOME
su -m vagrant
HOME=/home/vagrant

sudo sh -c 'echo "deb http://http.debian.net/debian jessie-backports main" >> /etc/apt/sources.list.d/valkyrie.list'
sudo sh -c 'echo "deb http://llvm.org/apt/jessie/ llvm-toolchain-jessie-3.6 main" >> /etc/apt/sources.list.d/valkyrie.list'
sudo sh -c 'echo "deb-src http://llvm.org/apt/jessie/ llvm-toolchain-jessie-3.6 main" >> /etc/apt/sources.list.d/valkyrie.list'
sudo sh -c 'echo "deb http://llvm.org/apt/jessie/ llvm-toolchain-jessie-3.7 main" >> /etc/apt/sources.list.d/valkyrie.list'
sudo sh -c 'echo "deb-src http://llvm.org/apt/jessie/ llvm-toolchain-jessie-3.7 main" >> /etc/apt/sources.list.d/valkyrie.list'

sudo sh -c 'echo "deb http://ppa.launchpad.net/webupd8team/java/ubuntu trusty main" >> /etc/apt/sources.list.d/java-8.list'
sudo sh -c 'echo "deb-src http://ppa.launchpad.net/webupd8team/java/ubuntu trusty main" >> /etc/apt/sources.list.d/java-8.list'

sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys EEA14886

sudo sed -i 's/jessie main/jessie main contrib non-free/g' /etc/apt/sources.list

wget -qO - http://llvm.org/apt/llvm-snapshot.gpg.key | sudo apt-key add -

sudo apt-get update -yq

##############################
######= Terminal & Vim =######
##############################

wget -q https://valkyrierobotics.com/debian/vimrc -O ~/.vimrc
sudo chmod 664 ~/.vimrc
sudo chown vagrant ~/.vimrc

sudo apt-get install -y vim-gtk curl zsh git

sh -c "$(curl -fsSL https://raw.githubusercontent.com/valkyrierobotics/oh-my-zsh/master/tools/install.sh)"

wget -q https://valkyrierobotics.com/debian/zshrc -O ~/.zshrc
sudo chmod 644 ~/.zshrc
sudo chown vagrant ~/.zshrc

sed -i 's/lee/vagrant/g' ~/.zshrc

sed -i 's/haribo/flazz/g' ~/.zshrc

chsh -s $(which zsh)

curl -fLo /home/vagrant/.vim/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim

vim +PlugInstall +q

######################
######= Java 8 =######
######################

echo oracle-java8-installer shared/accepted-oracle-license-v1-1 select true | sudo /usr/bin/debconf-set-selections

sudo apt-get install oracle-java8-installer oracle-java8-set-default

#######################
#####= Terminals =#####
#######################

sudo apt-get install powerline
mkdir ~/Build; cd ~/Build
git clone https://github.com/powerline/fonts; cd fonts
./install.sh

wget -q https://raw.githubusercontent.com/rupa/z/master/z.sh -O /home/vagrant/z.sh
sudo chmod +x /home/vagrant/z.sh

sudo apt-get install python libpython-dev ruby clang-format-3.5 clang-3.6 gfortran libblas-dev liblapack-dev python-scipy python-matplotlib -yq

sudo chown -R vagrant:vagrant /home/vagrant

######################
######= Ricing =######
######################

# sudo apt-get install libgtk-3-dev gtk2-engines-murrine autoconf autotool pkg-config

# cd ~/Build
# git clone https://github.com/horst3180/arc-theme --depth 1 && cd arc-theme
# ./autogen.sh --prefix=/usr
# sudo make install
#
# sudo apt-get install terminator
# wget -q https://valkyrierobotics.com/debian/.config/terminator -O ~/.config/terminator
#
# xfconf-query -c xsettings -p /Net/ThemeName -s "Arc-Dark"
#
# wget -q https://valkyrierobotics.com/debian/background.png -O ~/backgrond.png
# xfconf-query -c xfce4-desktop -p /backdrop/screen0/monitor0/image-path -s /home/vagrant/background.png
#
# cd ~/Build
# git clone https://github.com/0rAX0/uniform-icon-theme; cd uniform-icon-theme
# mv Uniform /usr/share/icons/
# cd ~/Build
# git clone https://github.com/numixproject/numix-icon-theme-circle
# cd numix-icon-theme-circle
# mv Numix-Circle /usr/share/icons
# sudo sed -i 's/Inherits=hicolor/Inherits=Numix-Circle,Humanity,gnome,hicolor/g' /usr/share/icons/Uniform/index.theme
# xfconf-query -c xsettings -p /Net/IconThemeName -s "Uniform"
# xfconf-query -c xfce4-desktop -p /desktop-icons/style -s 0 -t int
# rm -r ~/.config/xfce4/xfconf/xfce4-panel
# rm -r ~/.config/xfce4/panel
