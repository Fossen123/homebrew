require "formula"
class Opencv < Formula
  version "2.4.8"
  url 'https://github.com/drtaglia/homebrew/raw/master/opencv.tar.gz'
  homepage 'http://opencv.org/opencv-2-4-8.html'
  sha1 '4e661cc03fcd72be9060026b07dfc26f129c8a45'

  def install
    lib.install Dir["lib/*"]
    include.install Dir["include/*"]
    bin.install Dir["bin/*"]
    share.install Dir["share/*"]
  end
end
