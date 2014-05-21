require 'formula'
class OpenCV_static < Formula
  version "2.4.8"
  url 'https://github.com/drtaglia/homebrew/raw/master/opencv_static.tar.gz'
  homepage 'http://opencv.org/opencv-2-4-8.html'
  sha1 'ad9ced9f278edfaca25d1b4ca679be70f73a48a3'

  def install
    lib.install Dir["lib/*"]
    include.install Dir["include/*"]
    bin.install Dir["bin/*"]
    share.install Dir["share/*"]
  end
end
