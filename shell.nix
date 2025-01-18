{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  packages = with pkgs; [
    gnumake
    cmake
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    glm
    fmt
  ];
}
