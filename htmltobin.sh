#!/bin/bash
# cp -r ./build/* ./.catch/build/
# cp -r ./output/* ./.catch/output/

rm -r ./output/*
rm -r ./build/*

gcc ./parser.c -o ./parser && ./parser

shopt -s globstar

# Define the target directory
target_dir="output" # Replace with your actual directory
build_dir="build"

# Check if the target is a valid directory
if [ ! -d "$target_dir" ]; then
    echo "Error: Directory '$target_dir' not found."
    exit 1
fi

# Loop through all files recursively within the target directory
for file in "$target_dir"/**; do
    if [[ -f "$file" ]]; then
        echo "Processing file: $file"
        echo '#include "engine.h"

void render() {
    #include "'$file'"
}

int main() {
    render();
    return 0;
}' | gcc -xc -o "$build_dir${file:6: -7}" -
        # Add your desired operations on the file here
        # Example: cat "$file"
    fi
  done

rm /var/www/cgi-bin/*
rm ./parser
cp -r ./build/* /var/www/cgi-bin/
# chmod 755 /var/www/cgi-bin/
