require './config/application.rb'

class User < ActiveRecord::Base
end

# User.create!(:name => 'lol')

p User.all
