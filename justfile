set shell := ["bash", "-cu"]

cxxflags := "-std=c++20 -O2 -pipe -Wall -Wextra -Wshadow -Wconversion -Wformat=2 -Wpedantic -Wcast-qual -Wundef -Wduplicated-cond -Wfloat-equal -Wno-sign-conversion -DLOCAL"

default: run

build:
  #!/usr/bin/env bash
  set -euo pipefail

  src="main.cpp"
  bin="main"
  stamp=".build.flags"
  flags="{{cxxflags}}"
  needs_build=0

  [[ ! -x "$bin" ]] && needs_build=1
  [[ ! -f "$stamp" || "$(cat "$stamp")" != "$flags" ]] && needs_build=1

  if [[ -x "$bin" ]] && find . -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' -o -name '*.hpp' -o -name '*.hh' -o -name '*.h' \) -newer "$bin" -print -quit | grep -q .; then
    needs_build=1
  fi

  if [[ $needs_build -eq 1 ]]; then
    g++ $flags -o "$bin" "$src"
    printf '%s\n' "$flags" > "$stamp"
  fi

run: build
  ./main
