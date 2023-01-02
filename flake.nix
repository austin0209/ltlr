{
  description = "a 2D action platformer";

  inputs.nixpkgs.url = "github:nixos/nixpkgs";

  outputs = { self, nixpkgs }:
    let
      pname = "ltlr";
      version = "2023-01-02";
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
    in
    {
      packages."${system}" = {
        ltlr = derivation {
          name = "${pname}-${version}";
          inherit pname;
          inherit version;
          src = ./.;
          inherit system;
          builder = "${pkgs.nushell}/bin/nu";
          args = [ ./builder.nu ];
          buildInputs = with pkgs; [
            xorg.libX11.dev
            xorg.libXcursor.dev
            xorg.libXext.dev
            xorg.libXfixes.dev
            xorg.libXi.dev
            xorg.libXinerama.dev
            xorg.libXrandr.dev
            xorg.libXrender.dev
            xorg.xorgproto
            libGL.dev
            coreutils
            binutils-unwrapped
            nushell
            pkg-config
            gcc
            patchelf
            gnumake
          ];
        };
        default = self.packages."${system}".ltlr;
      };

      devShells."${system}" = {
        minimal = pkgs.mkShell {
          inputsFrom = [ self.packages."${system}".default ];
          packages = with pkgs; [
            astyle
          ];
        };
        extra = pkgs.mkShell {
          inputsFrom = [ self.devShells."${system}".minimal ];
          packages = with pkgs; [
            emscripten
          ];
        };
        default = self.devShells."${system}".minimal;
      };
    };
}
