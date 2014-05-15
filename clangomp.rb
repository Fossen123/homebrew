require 'formula'
class Clangomp < Formula
  version "3.4"
  url 'http://lgg.epfl.ch/SHARE/clangomp.tar.gz'
  homepage 'http://clang-omp.github.io'
  sha1 'ad9ced9f278edfaca25d1b4ca679be70f73a48a3'

  def install
    lib.install Dir["lib/*"]
    include.install Dir["include/*"]
    bin.install Dir["bin/*"]
    share.install Dir["share/*"]
  end
end