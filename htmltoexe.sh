exec ./parcser

for file in *; do
  if [ -f "$file" ]; then # Check if it's a regular file (not a directory)
    echo "Processing file: $file"
    # Perform operations on "$file" here
  fi
done
gcc ./rtest