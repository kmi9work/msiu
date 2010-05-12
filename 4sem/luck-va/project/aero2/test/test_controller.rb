$:.unshift File.join(File.dirname(__FILE__),'..','lib')

require 'test/unit'
require 'controllers/controller'

class TestController < Test::Unit::TestCase
  def test_lol
  end
end