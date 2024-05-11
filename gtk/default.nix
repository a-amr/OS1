#with import <nixpkgs> {};

let 
  pkgs = import <nixpkgs> {};
in

with pkgs;
stdenv.mkDerivation {
  name = "env";
  buildInputs = [
  gcc gtk3 pkg-config
  ];
  src = ./.;
  buildPhase = ''
  gcc userman-gtk.c -o userman-gtk  `pkg-config --cflags --libs gtk+-3.0`
  '';
  installPhase = ''
  mkdir -p $out/bin
  cp  userman-gtk $out/bin/userman-gtk
  '';
}
