require './config/application.rb'
gem 'activerecord'

class User < ActiveRecord::Base
end

# User.create!(:name => 'lol')

p User.all
