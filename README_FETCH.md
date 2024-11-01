## Installation and Build Instructions

1. Clone the repository:
    ```bash
    git clone https://github.com/agerber/asteroids_cpp.git
    cd asteroids_cpp
    ```

2. Make build scripts executable:
    ```bash
    chmod +x build.sh
    chmod +x build_mac.sh  # for mac
    chmod +x build_linux.sh  # for linux
    ```
3. Clean the build dir.
```bash
# Check if the build directory exists
if [ -d "build" ]; then
  echo "Deleting the build directory..."
  rm -rf build
  echo "Build directory deleted."
else
  echo "Build directory does not exist."
fi

```


4. Run the build script:
    - **macOS:**
      ```bash
      ./build_mac.sh
      ```
    - **Linux:**
      ```bash
      ./build_linux.sh
      ```
5. Execute the executable:
   ```bash
      build/asteroid
   ```