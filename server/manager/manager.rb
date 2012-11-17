require 'rubygems'
require './config/application.rb'
gem 'activerecord'
require 'active_record'

class User < ActiveRecord::Base
end

puts User.count
