let crossPkgs = import <nixpkgs> {
  crossSystem = {
    config = "i686-elf";
  };
};
    nativePkgs = import <nixpkgs> {};
in
  crossPkgs.mkShell {
    nativeBuildInputs = with nativePkgs; [ grub2 xorriso qemu ]; # you build dependencies here
    buildInputs = [ ]; # your dependencies here
  }
