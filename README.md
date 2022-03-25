# math_new
Math++ is a command-line tool which aims to be able to solve mathematics, from addition to square roots.

[![GitHub Super-Linter](https://github.com/avighnac/math_new/workflows/Lint%20Code%20Base/badge.svg)](https://github.com/marketplace/actions/super-linter) [![Math++ Tests](https://github.com/avighnac/math_new/actions/workflows/mathpp-tests.yml/badge.svg?branch=main)](https://github.com/avighnac/math_new/actions/workflows/mathpp-tests.yml) [![CodeQL](https://github.com/avighnac/math_new/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/avighnac/math_new/actions/workflows/codeql-analysis.yml)

Features:
- Add
- Subtract
- Multiply
- Square Root
- Factorial!
- Fraction Simplifier
- Simple Interest Solver

Beta Features:
- Exponent Features
- Divide

Other not-fully optimized/out of date features:
- Prime Factor Finder
- Prime Number Finder

**Installation**
 Linux: To install math++ on linux, simply run this command in a terminal shell.
 `sudo wget -O /usr/bin/math++ https://github.com/avighnac/math_new/releases/download/v1.0.2/math++_linux-1_0_2.out; sudo chmod +x /usr/bin/math++`

**Compilation**
 Linux:
  To compile this program, you will need to include one additional compiler parameter, namely `-lcurl` since this program uses libcurl for the `check_update` command. If you get the error `curl.h not found`, execute this command.
  Debian:
   `sudo apt-get install libcurl4-openssl-dev`
  OpenSUSE/RedHat:
   `sudo dnf (or yum) install curl-devel`
 Windows:
  Windows does not use libcurl, because I can't figure out how to get it to work. Instead, the check_update function uses curl.exe, which is pre-installed in the System32 folder.
