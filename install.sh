rm -rf build
if ! cmake --version > /dev/null; then
    echo "Cmake not installed."
    echo "To install it please run:"
    echo "sudo apt install cmake"
    return 1;
fi

mkdir build && cd build

cmake ..

if ! make -v > /dev/null; then
    echo "make not installed."
    echo "To install it please run:"
    echo "sudo apt install make"
    return 1;
fi

make
