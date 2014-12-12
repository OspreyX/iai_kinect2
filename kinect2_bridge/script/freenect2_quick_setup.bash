# Pull freenect2 dependencies
sudo apt-get install -y ros-indigo-perception
sudo apt-get install -y nvidia-331-dev
sudo apt-get install -y ocl-icd-opencl-dev
sudo apt-get install -y libtool automake libudev-dev

# Pull known-working freenect2 fork
cd ~
git clone https://github.com/clearpathrobotics/libfreenect2.git
cd libfreenect2/depends
sh install_ubuntu.sh

# Fix turbonect
sudo ln -s /usr/lib/x86_64-linux-gnu/libturbojpeg.so.0.0.0 /usr/lib/x86_64-linux-gnu/libturbojpeg.so

# Compile freenect2 prototype
cd ../examples/protonect
cmake CMakeLists.txt
make
sudo make install

# Link to shared libs
sudo ln -sf /usr/local/lib64/* /usr/local/lib/