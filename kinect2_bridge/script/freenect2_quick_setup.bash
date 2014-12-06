#dependencies
sudo apt-get install -y ros-indigo-perception
sudo apt-get install -y nvidia-331-dev
sudo apt-get install -y ocl-icd-opencl-dev
sudo apt-get install -y libtool automake libudev-dev

cd ~
git clone https://github.com/clearpathrobotics/libfreenect2.git
cd libfreenect2/depends
sh install_ubuntu.sh

sudo ln -s /usr/lib/x86_64-linux-gnu/libturbojpeg.so.0.0.0 /usr/lib/x86_64-linux-gnu/libturbojpeg.so

cd ../examples/protonect
cmake CMakeLists.txt
make
sudo make install

echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/:/usr/local/./lib64/' >> ~/.bashrc