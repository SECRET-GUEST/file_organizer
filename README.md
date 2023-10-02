
```
███████╗██╗██╗     ███████╗███████╗     ██████╗ ██████╗  ██████╗  █████╗ ███╗   ██╗██╗███████╗███████╗██████╗ 
██╔════╝██║██║     ██╔════╝██╔════╝    ██╔═══██╗██╔══██╗██╔════╝ ██╔══██╗████╗  ██║██║╚══███╔╝██╔════╝██╔══██╗
█████╗  ██║██║     █████╗  ███████╗    ██║   ██║██████╔╝██║  ███╗███████║██╔██╗ ██║██║  ███╔╝ █████╗  ██████╔╝
██╔══╝  ██║██║     ██╔══╝  ╚════██║    ██║   ██║██╔══██╗██║   ██║██╔══██║██║╚██╗██║██║ ███╔╝  ██╔══╝  ██╔══██╗
██║     ██║███████╗███████╗███████║    ╚██████╔╝██║  ██║╚██████╔╝██║  ██║██║ ╚████║██║███████╗███████╗██║  ██║
╚═╝     ╚═╝╚══════╝╚══════╝╚══════╝     ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚══════╝╚═╝  ╚═╝
```
![C](https://img.shields.io/badge/C-GCC-purple)
![ALPHA](https://img.shields.io/badge/ALPHA-red) 


# Files Organizer 🗃️

Files Organizer is a versatile, efficient, and user-friendly program designed to facilitate file sorting tasks, making it an essential tool especially when complementing data recovery processes on hard drives, using a customizable Graphical User Interface (GUI). Written in C, it supports various platforms including Debian Linux and MacOS, and is currently in its alpha stage of development.

This software stands out by providing a structured way to organize recovered files, ensuring that users can easily locate their valuable data after a recovery process. It is ideal for anyone looking to add an extra layer of order to their file recovery endeavors, avoiding the chaos that often comes with unsorted recovered files.

For those who prefer a streamlined, GUI-free experience, a shorter, more concise script is also available at [Tiny Scripts](https://github.com/SECRET-GUEST/tiny-scripts), allowing users to discover user-friendly, straightforward solutions for their file organizing needs.

---
---
---

## 📋 Table of Contents

1. [Features](#-features)
2. [Prerequisites](#-prerequisites)
3. [To Do](#-todo)
4. [License](#-license)
5. [Support & Questions](#-support--questions)
6. [Recommendations](#-recommendations)
7. [Installation](#-installation)

## 🌟 Features

- User Interface
- Supports Multiple Languages
- Efficient File Sorting Algorithm
- User-friendly Error Handling
- Localizable through JSON files 

## 🔍 Prerequisites

Before you begin, ensure you have the following installed:

- GCC Compiler
- Make

## 🛠️ TODO

1. Windows Support
2. Optimize Sorting Algorithm
3. Expand Language Support


## 📜 License

This repository is released under the [MIT License](LICENSE). Please refer to the `LICENSE` file for more information.

## ❓ Support & Questions

If you have any questions or need support, please feel free to open an issue, a new discussion, or contact me on twitter.

## 💎 Recommendations

Looking for more? Explore the following user-friendly, efficient repositories:

- [LNK reader](https://github.com/SECRET-GUEST/windows_link_reader): Allows dual boot Linux users to work with Windows shortcuts.
- [Unreal installer](https://github.com/SECRET-GUEST/Unrealinux) : An installer in C++ for Unreal Engine on Linux without Epic Games launcher.

Looking for more? Discover user-friendly, GUI-free script here: 
- [Tiny Scripts](https://github.com/SECRET-GUEST/tiny-scripts)



## 📥 Installation 

### General Steps:

1. **Clone the Repository**
   ```sh
   git clone https://github.com/SECRET-GUEST/file_organizer
   ```

2. **Navigate to the Directory**
   ```sh
   cd file_organizer
   ```

### ![LINUX](https://img.shields.io/badge/Debian-LINUX-orange)

3. **Install the required dependencies:**
   ```sh
   sudo apt-get install gcc make libgtk-3-dev libjson-c-dev
   ```

4. **Compile the Program using Makefile**
   ```sh
   make
   ```

5. **Run the Program (as super user if necessary, but be careful !)**
   ```sh
   sudo ./File_organizer
   ```



### ![MACOS](https://img.shields.io/badge/MacOS-white) 

3. **Install the necessary build tools and libraries if not already present using Homebrew**
   ```sh
   brew install gcc make gtk+3 json-c
   ```

4. **Compile the Program using Makefile**
   ```sh
   make
   ```

5. **Run the Program (as super user if necessary)**
   ```sh
   sudo ./File_organizer
   ```

### ![WINDOWS](https://img.shields.io/badge/windows-blue)

Building for Windows using GTK is a more involved process. You'd likely need an environment like MSYS2 or Cygwin. It's recommended for now to focus on the Linux and MacOS builds unless you're willing to spend some time setting up a build system for Windows.



