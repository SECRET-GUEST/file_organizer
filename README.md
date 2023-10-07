Supported : 🇫🇷 🇺🇸 🇬🇧 🇨🇦 🇦🇺 
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

Files Organizer is a versatile and efficient software solution, designed to seamlessly sort files within a folder and its subdirectories by moving them into folders named after their respective extensions. Developed in C, this user-friendly program, complete with a customizable Graphical User Interface (GUI), supports various platforms including Linux and MacOS, and is currently in its alpha stage of development.

This software is particularly invaluable when used in conjunction with data recovery processes on hard drives, enabling users to effortlessly locate and organize their recovered data. It brings structure and order to the often chaotic landscape of unsorted recovered files, providing a streamlined post-recovery experience.

I primarily utilize it as a supplementary tool for disk recovery, with plans for a more comprehensive software solution on this subject in the future. For users who prefer a simpler, GUI-free experience, a concise script is also available at [tiny file organizer script](https://github.com/SECRET-GUEST/tiny-scripts/tree/ALL/C/Files%20handlers/File%20organizer).

![image](https://github.com/SECRET-GUEST/file_organizer/assets/92639080/2c9358f4-fc2c-4f70-b32c-0ed01ee53ee1)
Supported : 🇫🇷 🇺🇸 🇬🇧 🇨🇦 🇦🇺 

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

- Supports Multiple Languages
- Efficient File Sorting Algorithm
- User-friendly Error Handling

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

### ![LINUX](https://img.shields.io/badge/LINUX-orange)

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



