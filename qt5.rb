require 'formula'

class Qt5 < Formula
  version "5.3.0"
  url 'https://github.com/drtaglia/homebrew/raw/master/qt5.tar.gz'
  homepage 'https://github.com/drtaglia/homebrew'
  sha1 '3ea993e58beaeb568def2f48028fe14c7e127c9b'

  def install
    bin.install Dir["bin/*"]
    doc.install Dir["doc/*"]
    include.install Dir["include/*"]
    lib.install Dir["lib/*"]
    libexec.install Dir["libexec/*"]
    # generic directory installs 
    prefix.install Dir["mkspecs"]
    prefix.install Dir["imports"]
    prefix.install Dir["phrasebooks"]
    prefix.install Dir["plugins"]
    prefix.install Dir["qml"]
    prefix.install Dir["translations"]
  end
end