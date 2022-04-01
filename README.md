<<<<<<< HEAD
<h1 align="center">math++</h1>

<div align="center">
 <p>... is a command-line tool which aims to be able to solve mathematics, from addition to square roots.</p>
  <a href="https://github.com/avighnac/math_new/releases">
    <img src="https://img.shields.io/github/v/release/avighnac/math_new?include_prereleases&label=Latest%20Release" />
  </a>
  <a href="https://github.com/avighnac/math_new/actions/workflows/mathpp-tests.yml">
    <img src="https://github.com/avighnac/math_new/actions/workflows/mathpp-tests.yml/badge.svg?branch=main" />
  </a>
  <a href="https://github.com/avighnac/math_new/actions/workflows/codeql-analysis.yml">
    <img src="https://github.com/avighnac/math_new/actions/workflows/codeql-analysis.yml/badge.svg" />
  </a>
 <a href="https://github.com/avighnac/math_new/actions/workflows/linter.yml">
  <img src="https://github.com/avighnac/math_new/workflows/Lint%20Code%20Base/badge.svg" />
 </a>
</div>

## Features

- Add
- Subtract
- Multiply
- Square Root
- Factorial!
- Fraction Simplifier
- Simple Interest Solver
- Factorize ax^2 + bx + c
- Evaluate a mathematical expression (beta)
- Convert any rational number to a fraction.

## Installation

* Linux
  * To install math++ on Linux, simply run this command in a terminal shell: `sudo wget -O /usr/bin/math++ https://github.com/avighnac/math_new/releases/download/v1.0.2.3/math++_linux-1_0_2_3.out --no-check-certificate; sudo chmod +x /usr/bin/math++`
  * Type 'math++' in any Linux CLI to run the program.
* Windows
  * Download the latest release, rename the .exe to "math++.exe" and move it to the System32 folder.
  * Type 'math++' in any Windows CLI to run the program.

## Compliation

* Linux
  * To compile this program, you will need to include one additional compiler parameter, namely `-lcurl` since this program uses libcurl for the `check_update` command. If you get the error `curl.h not found`, execute this command.
    * Debian: `sudo apt-get install libcurl4-openssl-dev`
    * OpenSUSE/RedHat: `sudo dnf (or yum) install curl-devel`
  * Or, you could build using CMake. Go to the directory which contains 'math++.cpp', and type `cmake build/`, and `cmake --build build/`.
* Windows:
  * Open the file 'math++.vcxproj' using Visual Studio. Press on the green button at the top of the screen.
=======
<h1 align="center">math++</h1>

<div align="center">
 <p>... is a command-line tool which aims to be able to solve mathematics, from addition to square roots.</p>
  <a href="https://github.com/avighnac/math_new/releases">
    <img src="https://img.shields.io/github/v/release/avighnac/math_new?include_prereleases&label=Latest%20Release" />
  </a>
  <a href="https://github.com/avighnac/math_new/actions/workflows/mathpp-tests.yml">
    <img src="https://github.com/avighnac/math_new/actions/workflows/mathpp-tests.yml/badge.svg?branch=main" />
  </a>
  <a href="https://github.com/avighnac/math_new/actions/workflows/codeql-analysis.yml">
    <img src="https://github.com/avighnac/math_new/actions/workflows/codeql-analysis.yml/badge.svg" />
  </a>
 <a href="https://github.com/avighnac/math_new/actions/workflows/linter.yml">
  <img src="https://github.com/avighnac/math_new/workflows/Lint%20Code%20Base/badge.svg" />
 </a>
</div>

## Features

- Add
- Subtract
- Multiply
- Square Root
- Factorial!
- Fraction Simplifier
- Simple Interest Solver
- Factorize ax^2 + bx + c
- Evaluate a mathematical expression (beta)
- Convert any rational number to a fraction.

## Installation

* Linux
  * To install math++ on Linux, simply run this command in a terminal shell: `sudo wget -O /usr/bin/math++ https://github.com/avighnac/math_new/releases/download/v1.0.2.3/math++_linux-1_0_2_3.out --no-check-certificate; sudo chmod +x /usr/bin/math++`
  * Type 'math++' in any Linux CLI to run the program.
* Windows
  * Download the latest release, rename the .exe to "math++.exe" and move it to the System32 folder.
  * Type 'math++' in any Windows CLI to run the program.

## Compliation

* Linux
  * To compile this program, you will need to include one additional compiler parameter, namely `-lcurl` since this program uses libcurl for the `check_update` command. If you get the error `curl.h not found`, execute this command.
    * Debian: `sudo apt-get install libcurl4-openssl-dev`
    * OpenSUSE/RedHat: `sudo dnf (or yum) install curl-devel`
  * Or, you could build using CMake. Go to the directory which contains 'math++.cpp', and type `cmake build/`, and `cmake --build build/`.
* Windows:
  * Open the file 'math++.vcxproj' using Visual Studio. Press on the green button at the top of the screen.
>>>>>>> e1a906d3926ebe91fd5caeb6c248028b0fea0548
