![Space-Wars Logo](https://github.com/austinmhorn/space-wars/blob/main/assets/png/logo/space-wars-banner.png)

---

# Building Space Wars

Space Wars requires **CMake** and **SFML 2.x**.

---

## macOS Setup (Homebrew)

### Install Dependencies

```bash
brew install cmake
brew install sfml@2
```

### Step 1: Generate Build System
##### *Be sure that you are inside the project source directory before running any commands*

```bash
cmake -S . -B build
```

### Step 2: Build Object Files

```bash
cmake --build build
```

> SFML 2 installed through Homebrew will be detected automatically.

---

## Windows Setup

### Install Dependencies

Install:

- Visual Studio with **Desktop development with C++**
- CMake → https://cmake.org/download/
- SFML 2.x → https://www.sfml-dev.org/download/sfml/2.6.2/

Extract SFML somewhere accessible, for example:

```txt
C:\Libraries\SFML
```

### Step 1: Generate Build System
##### *Be sure that you are inside the project source directory before running any commands*

```powershell
cmake -S . -B build -DSFML_DIR="C:/Libraries/SFML/lib/cmake/SFML"
```

### Step 2: Build Object Files

```powershell
cmake --build build
```

---

## Linux (Ubuntu)

### Install Dependencies

```bash
sudo apt update
sudo apt install cmake libsfml-dev
```

### Step 1: Generate Build System
##### *Be sure that you are inside the project source directory before running any commands*

```bash
cmake -S . -B build
```

### Step 2: Build Object Files

```bash
cmake --build build
```
