cd build

if ! make -v > /dev/null; then
    echo "make not installed."
    echo "To install it please run:"
    echo "sudo apt install make"
    return 1;
fi

make

cd ..

./bin/main