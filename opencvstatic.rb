require "formula"
class Opencvstatic < Formula
  version "2.4.8"
  url 'https://github.com/drtaglia/homebrew/raw/master/opencv_static.tar.gz'
  homepage 'http://opencv.org/opencv-2-4-8.html'
  sha1 '4e95df02e3bd77cc65fbb75d58620548a529638a'

  def install
    lib.install Dir["lib/*"]
    include.install Dir["include/*"]
    bin.install Dir["bin/*"]
    share.install Dir["share/*"]
  end
end
