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

# Remove existing entries
sed -i "/\b\(LD_LIBRARY_PATH\)\b/d" ~/.bashrc

# Append to LD_LIBRARY_PATH
echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/:/usr/local/./lib64/' >> ~/.bashrc