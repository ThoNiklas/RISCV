{ pkgs ? (import <nixpkgs> {})}:

pkgs.mkShell {
  nativeBuildInputs = with pkgs.buildPackages; [
    verilator
    gtkwave
    python3
    pkgsCross.riscv32-embedded.buildPackages.gcc
  ];
}

