#with import <nixpkgs> {};

let 
  pkgs = import <nixpkgs> {};
in

with pkgs;
stdenv.mkDerivation {
  name = "env";
  buildInputs = [
  gcc
  ];
  src = ./.;
  buildPhase = ''
  gcc userman.c -o userman
  '';
  installPhase = ''
  mkdir -p $out/bin
  cp  userman $out/bin/userman
  '';
}
