{
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
        let pkgs = nixpkgs.legacyPackages.${system}; in {
            packages = rec {
              fec = pkgs.stdenv.mkDerivation {
                  name = "fec";
                  src = ./.;
                  nativeBuildInputs = with pkgs; [ cmake ];
                  installPhase = ''
                    mkdir -p $out/bin
                    cp fec $out/bin
                  '';
              };
              default = fec;
            };
          }
    );
}
