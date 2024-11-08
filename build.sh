set -xe

echo "CompileFlags:
    Add:
        - \"-std=c++23\"
        - \"-I$(pwd)\"" > .clangd

CXX=$(which g++-14) cmake -B artifacts -GNinja .
cmake --build artifacts -j8
mv debug/gui .
rm -rf debug

