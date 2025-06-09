# Building and Using with the `cpp-atom` Project Example

This section describes how to set up and run the `cpp-atom` example project, which uses this version of GLFW. These instructions assume your project is structured with a root `cpp-atom` directory, which contains this `glfw-3.4` source directory alongside the main `cpp-atom` project files.

## 1. Prerequisites

Ensure you have the following installed:

- CMake (version **4.0** or later for GLFW; the `cpp-atom` project's `CMakeLists.txt` specifies 4.0)
- A C++ compiler (e.g., GCC, Clang, MSVC)
- Make (or your chosen build system generator for CMake, like Ninja or Visual Studio)
- An `unzip` utility (or equivalent for `.zip` files)

## 2. Setting up GLFW Source Code from `glfw-3.4.zip`

The `cpp-atom` project expects the GLFW source code to be in a subdirectory named `glfw-3.4` within the main project folder (e.g., `/home/huybui/Coding/cpp-atom/glfw-3.4`).

1.  Place the `glfw-3.4.zip` file in your `cpp-atom` project's root directory.
2.  Navigate to the `cpp-atom` project directory in your terminal.
3.  Extract the `glfw-3.4.zip` file.
    ```bash
    unzip glfw-3.4.zip
    ```
4.  This will likely create a directory such as `glfw-3.4.0` or `glfw-3.4` (the exact name depends on how the zip archive was created).
    - If a directory named exactly `glfw-3.4` is created, and it's directly under your `cpp-atom/` project root (e.g., `cpp-atom/glfw-3.4/`), you are set.
    - If a differently named directory is created (e.g., `glfw-3.4.0/`), you must rename it to `glfw-3.4`.
    ```bash
    # Example: if 'glfw-3.4.0' was created from the zip
    mv glfw-3.4.0 glfw-3.4
    ```
    The final structure should be `cpp-atom/glfw-3.4/`, where this `glfw-3.4/` directory contains the GLFW source files (like its own `CMakeLists.txt`, `src/`, `include/`, etc.).

## 3. Installing GLFW (Optional System-Wide Install)

The `cpp-atom` project, as configured by its main `CMakeLists.txt`, builds GLFW from the local `glfw-3.4` subdirectory. Therefore, a separate system-wide installation of GLFW is not strictly necessary for the `cpp-atom` project itself. However, if you wish to install GLFW system-wide (or to a custom prefix) for use with other projects or for general availability, follow these steps:

1.  Navigate to the GLFW source directory (this directory, `glfw-3.4`):
    ```bash
    cd glfw-3.4
    ```
    (If you are in the `cpp-atom` root, this would be `cd glfw-3.4`).
2.  Build the GLFW source to `build` folder:
    ```bash
    cmake -S . -B build
    ```
3.  Compile GLFW:
    ```bash
    cd build
    make
    ```
4.  Install GLFW. This step may require administrator privileges (e.g., `sudo`) if installing to default system directories.
    ```bash
    sudo make install
    # Alternatively, to install to a custom location (prefix), configure CMake with:
    # cmake .. -DCMAKE_INSTALL_PREFIX=/your/custom/path
    # Then run 'make' and 'make install' (sudo might not be needed for a custom path).
    ```
5.  After installation, navigate back to the `cpp-atom` project's root directory

**Note:** As mentioned, the `cpp-atom` project's current `CMakeLists.txt` uses `add_subdirectory(glfw-3.4)`. This means it will compile GLFW from the local source code found in `cpp-atom/glfw-3.4/` during its own build process, regardless of whether a system-wide version of GLFW is installed. The installation steps above are for making GLFW available more broadly.

## 4. Installing GLAD

1.  **Go to the GLAD Website:**

    - Open your web browser and navigate to [https://glad.dav1d.de/](https://glad.dav1d.de/).

2.  **Configure GLAD Generation:**

    - **Language:** Set to `C/C++`.
    - **Specification:** Select `OpenGL`.
    - **API:**
      - `gl`: Choose `4.6` (latest stable modern OpenGL) or `3.3` (a common baseline if your hardware is older). For a new project, `4.6` is recommended.
    - **Profile:** Select `Core`.
    - **Options:** Check `Generate a loader`. Optionally, check `Debug` for better error messages during development.
    - Click the `GENERATE` button.

3.  **Download GLAD Files:**

    - After generation, click the `DOWNLOAD` button. This will download a `.zip` archive.

4.  **Extract and Place Files in Your Project:**

    - Unzip the downloaded archive. You will find:
      - An `include/` folder (containing `KHR/` and `glad/` subfolders).
      - A `src/` folder (containing `glad.c`).
    - **Copy these into your project's directory structure:**
      - Place the `include/` folder (with `KHR/` and `glad/` inside it) into your project's main `include/` directory (e.g., `your_project/include/`).
      - Place the `glad.c` file into your project's `src/` directory (e.g., `your_project/src/`).

5.  **Configure CMake to Compile and Link GLAD:**

    - Open your `CMakeLists.txt` file.
    - **Find OpenGL:** Add `find_package(OpenGL REQUIRED)` to tell CMake to locate the OpenGL development files on your system.
    - **Add `glad.c` to Sources:** Ensure `glad.c` is listed as a source file for your executable.
    - **Link with OpenGL:** Link your executable against the `OpenGL::GL` target.

    Here's a minimal example for your `CMakeLists.txt`:

    ```cmake
    cmake_minimum_required(VERSION 3.16)
    project(AtomicSimulation LANGUAGES CXX)

    # Set C++ standard (important for C++23)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Find necessary packages
    find_package(OpenGL REQUIRED) # Finds OpenGL
    find_package(glfw3 3.3 REQUIRED) # Finds GLFW (assuming you've installed libglfw3-dev)

    # Add project-specific include directories (where your glad/KHR headers are)
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/include # Points to your_project/include/
    )

    # Define your executable and its source files
    # Make sure glad.c is included here!
    add_executable(${PROJECT_NAME}
        src/main.cpp
        src/glad.c # Crucial: Compile GLAD's source file
        # Add any other .cpp files for your project here
    )

    # Link libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL # Link against OpenGL
        glfw # Link against GLFW
    )
    ```

After these steps, when you build your project using CMake (e.g., `cmake -B build && cmake --build build`), CMake will compile `glad.c` along with your other source files and link everything correctly.

## 5. Building and Running the `cpp-atom` Project

The `cpp-atom` project is set up to build GLFW as part of its own compilation process, using the sources located in the `cpp-atom/glfw-3.4/` directory.

1.  Ensure you are in the root directory of the `cpp-atom` project. This directory should contain the `build-and-run.sh` script, the main `CMakeLists.txt` for `cpp-atom`, `main.cpp`, and the `glfw-3.4` subdirectory.
2.  Run the provided build script:
    ```bash
    ./build-and-run.sh
    ```
    This script typically performs the following actions:

- `cmake .`: Configures the `cpp-atom` project using CMake. This command processes the `cpp-atom/CMakeLists.txt`, which in turn includes and configures the GLFW build from the `glfw-3.4` subdirectory. Build files are usually generated in the current directory or a `build` subdirectory depending on CMake's behavior and local configuration.
- `make`: Compiles both the `cpp-atom` application and the local GLFW library as configured by CMake.
- `./cpp-atom.output`: Executes the compiled `cpp-atom.output` application.

If you encounter issues, double-check that the `glfw-3.4` directory is correctly named and placed within the `cpp-atom` project structure as described in Step 2, and that all prerequisites from Step 1 are met.
