require 'formula'
class Openmprtl < Formula
  version "13.05.2014"
  url 'http://lgg.epfl.ch/SHARE/openmprtl.tar.gz'
  homepage 'https://www.openmprtl.org/'
  sha1 'b560171a8f4e474d13a2ecf49c47cd64d0b330a5'

  def install
    lib.install Dir["lib/*"]
    include.install Dir["include/*"]
  end
end