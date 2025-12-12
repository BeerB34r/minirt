LIBDIR="lib"
TARGET="$LIBDIR/mlx42"
BUILD_DIR="$TARGET/build"
UPDATED=1

if [ ! -d "$TARGET" ]; then
    echo "Cloning MLX42..."
    git clone https://github.com/codam-coding-college/MLX42.git "$TARGET"

else
    echo "MLX42 already exists, pulling latest changes..."
    cd "$TARGET"
    PULL_OUTPUT=$(git pull)
    echo "$PULL_OUTPUT"
    if echo "$PULL_OUTPUT" | grep -q "Already up to date."; then
        UPDATED=0
    fi
    cd - > /dev/null
fi

if [ "$UPDATED" -eq 1 ]; then
    echo "Building MLX42..."
    rm -rf "$BUILD_DIR"
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake ..
    make -j
else
    echo "MLX42 is already up to date, skipping rebuild."
fi