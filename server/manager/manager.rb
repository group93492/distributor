require './config/application.rb'
gem 'activerecord'

class User < ActiveRecord::Base
end

puts User.count
